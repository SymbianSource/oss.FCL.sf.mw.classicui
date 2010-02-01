/*************************************************************************
 *                                                                       *
 * Open Dynamics Engine, Copyright (C) 2001-2003 Russell L. Smith.       *
 * All rights reserved.  Email: russ@q12.org   Web: www.q12.org          *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of EITHER:                                  *
 *   (1) The GNU Lesser General Public License as published by the Free  *
 *       Software Foundation; either version 2.1 of the License, or (at  *
 *       your option) any later version. The text of the GNU Lesser      *
 *       General Public License is included with this library in the     *
 *       file LICENSE.TXT.                                               *
 *   (2) The BSD-style license that is included with this library in     *
 *       the file LICENSE-BSD.TXT.                                       *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files    *
 * LICENSE.TXT and LICENSE-BSD.TXT for more details.                     *
 *                                                                       *
 *************************************************************************/

#include "object.h"
#include "joint.h"
#include <ode/config.h>
#include <ode/odemath.h>
#include <ode/rotation.h>
#include <ode/timer.h>
#include <ode/error.h>
#include <ode/matrix.h>
#include <ode/misc.h>
#include "lcp.h"
#include "util.h"

//#define ALLOCA dALLOCA16

typedef const dReal *dRealPtr;
typedef dReal *dRealMutablePtr;
#define dRealArray(name,n) dReal name[n];
#define dRealAllocaArray(name,n) dReal *name = (dReal*) malloc ((n)*sizeof(dReal));

//***************************************************************************
// configuration

// for the SOR method:
// uncomment the following line to randomly reorder constraint rows
// during the solution. depending on the situation, this can help a lot
// or hardly at all, but it doesn't seem to hurt.

#define RANDOMLY_REORDER_CONSTRAINTS 1

//****************************************************************************
// special matrix multipliers

// multiply block of B matrix (q x 6) with 12 dReal per row with C vektor (q)
static void Multiply1_12q1 (dReal *A, dReal *B, dReal *C, int q)
{
  int k;
  dReal sum;

  sum = 0;
  for (k=0; k<q; k++) sum += dMUL(B[k*12],C[k]);
  A[0] = sum;
  sum = 0;
  for (k=0; k<q; k++) sum += dMUL(B[1+k*12],C[k]);
  A[1] = sum;
  sum = 0;
  for (k=0; k<q; k++) sum += dMUL(B[2+k*12],C[k]);
  A[2] = sum;
  sum = 0;
  for (k=0; k<q; k++) sum += dMUL(B[3+k*12],C[k]);
  A[3] = sum;
  sum = 0;
  for (k=0; k<q; k++) sum += dMUL(B[4+k*12],C[k]);
  A[4] = sum;
  sum = 0;
  for (k=0; k<q; k++) sum += dMUL(B[5+k*12],C[k]);
  A[5] = sum;
}

//***************************************************************************
// testing stuff

#ifdef TIMING
#define IFTIMING(x) x
#else
#define IFTIMING(x) /* */
#endif

//***************************************************************************
// various common computations involving the matrix J

// compute iMJ = inv(M)*J'

static void compute_invM_JT (int m, dRealMutablePtr J, dRealMutablePtr iMJ, int *jb,
	dxBody * const *body, dRealPtr invI)
{
	int i,j;
	dRealMutablePtr iMJ_ptr = iMJ;
	dRealMutablePtr J_ptr = J;
	for (i=0; i<m; i++) {
		int b1 = jb[i*2];
		int b2 = jb[i*2+1];
		dReal k = body[b1]->invMass;
		for (j=0; j<3; j++) iMJ_ptr[j] = dMUL(k,J_ptr[j]);
		dMULTIPLY0_331 (iMJ_ptr + 3, invI + 12*b1, J_ptr + 3);
		if (b2 >= 0) {
			k = body[b2]->invMass;
			for (j=0; j<3; j++) iMJ_ptr[j+6] = dMUL(k,J_ptr[j+6]);
			dMULTIPLY0_331 (iMJ_ptr + 9, invI + 12*b2, J_ptr + 9);
		}
		J_ptr += 12;
		iMJ_ptr += 12;
	}
}

// compute out = J*in.

static void multiply_J (int m, dRealMutablePtr J, int *jb,
	dRealMutablePtr in, dRealMutablePtr out)
{
	int i,j;
	dRealPtr J_ptr = J;
	for (i=0; i<m; i++) {
		int b1 = jb[i*2];
		int b2 = jb[i*2+1];
		dReal sum = 0;
		dRealMutablePtr in_ptr = in + b1*6;
		for (j=0; j<6; j++) sum += dMUL(J_ptr[j],in_ptr[j]);
		J_ptr += 6;
		if (b2 >= 0) {
			in_ptr = in + b2*6;
			for (j=0; j<6; j++) sum += dMUL(J_ptr[j],in_ptr[j]);
		}
		J_ptr += 6;
		out[i] = sum;
	}
}


//***************************************************************************
// SOR-LCP method

// nb is the number of bodies in the body array.
// J is an m*12 matrix of constraint rows
// jb is an array of first and second body numbers for each constraint row
// invI is the global frame inverse inertia for each body (stacked 3x3 matrices)
//
// this returns lambda and fc (the constraint force).
// note: fc is returned as inv(M)*J'*lambda, the constraint force is actually J'*lambda
//
// b, lo and hi are modified on exit


struct IndexError {
	dReal error;		// error to sort on
	int findex;
	int index;		// row index
};


static void SOR_LCP (int m, int nb, dRealMutablePtr J, int *jb, dxBody * const *body,
	dRealPtr invI, dRealMutablePtr lambda, dRealMutablePtr fc, dRealMutablePtr b,
	dRealMutablePtr lo, dRealMutablePtr hi, dRealPtr cfm, int *findex,
	dxQuickStepParameters *qs)
{
	const int num_iterations = qs->num_iterations;
	const dReal sor_w = qs->w;		// SOR over-relaxation parameter

	int i,j;

	dSetZero (lambda,m);

	// a copy of the 'hi' vector in case findex[] is being used
	dRealAllocaArray (hicopy,m);
	if(hicopy == NULL) {
		return;
	}
	memcpy (hicopy,hi,m*sizeof(dReal));

	// precompute iMJ = inv(M)*J'
	dRealAllocaArray (iMJ,m*12);
	if(iMJ == NULL) {
		free(hicopy);
		return;
	}
	compute_invM_JT (m,J,iMJ,jb,body,invI);

	// compute fc=(inv(M)*J')*lambda. we will incrementally maintain fc
	// as we change lambda.

	dSetZero (fc,nb*6);

	// precompute 1 / diagonals of A
	dRealAllocaArray (Ad,m);
	if(Ad == NULL) {
		free(hicopy);
		free(iMJ);
		return;
	}
	dRealPtr iMJ_ptr = iMJ;
	dRealMutablePtr J_ptr = J;
	for (i=0; i<m; i++) {
		dReal sum = 0;
		for (j=0; j<6; j++) sum += dMUL(iMJ_ptr[j],J_ptr[j]);
		if (jb[i*2+1] >= 0) {
			for (j=6; j<12; j++) sum += dMUL(iMJ_ptr[j],J_ptr[j]);
		}
		iMJ_ptr += 12;
		J_ptr += 12;
		Ad[i] = dDIV(sor_w,(sum + cfm[i]));
	}

	// scale J and b by Ad
	J_ptr = J;
	for (i=0; i<m; i++) {
		for (j=0; j<12; j++) {
			J_ptr[0] = dMUL(J_ptr[0],Ad[i]);
			J_ptr++;
		}
		b[i] = dMUL(b[i],Ad[i]);

		// scale Ad by CFM. N.B. this should be done last since it is used above
		Ad[i]= dMUL(Ad[i],cfm[i]);
	}

	// order to solve constraint rows in
	IndexError *order = (IndexError*) malloc (m*sizeof(IndexError));
	if(order == NULL) {
		free(hicopy);
		free(iMJ);
		free(Ad);
		return;
	}

#ifndef REORDER_CONSTRAINTS
	// make sure constraints with findex < 0 come first.
	j=0;
	int k=1;

	// Fill the array from both ends
	for (i=0; i<m; i++)
		if (findex[i] < 0)
			order[j++].index = i; // Place them at the front
		else
			order[m-k++].index = i; // Place them at the end


#endif

	for (int iteration=0; iteration < num_iterations; iteration++) {


#ifdef RANDOMLY_REORDER_CONSTRAINTS
		if ((iteration & 7) == 0) {
			for (i=1; i<m; ++i) {
				IndexError tmp = order[i];
				int swapi = dRandInt(i+1);
				order[i] = order[swapi];
				order[swapi] = tmp;
			}
		}
#endif

		for (int i=0; i<m; i++) {
			// @@@ potential optimization: we could pre-sort J and iMJ, thereby
			//     linearizing access to those arrays. hmmm, this does not seem
			//     like a win, but we should think carefully about our memory
			//     access pattern.

			int index = order[i].index;
			J_ptr = J + index*12;
			iMJ_ptr = iMJ + index*12;

			// set the limits for this constraint. note that 'hicopy' is used.
			// this is the place where the QuickStep method differs from the
			// direct LCP solving method, since that method only performs this
			// limit adjustment once per time step, whereas this method performs
			// once per iteration per constraint row.
			// the constraints are ordered so that all lambda[] values needed have
			// already been computed.
			if (findex[index] >= 0) {
				hi[index] = dFabs (dMUL(hicopy[index],lambda[findex[index]]));
				lo[index] = -hi[index];
			}

			int b1 = jb[index*2];
			int b2 = jb[index*2+1];
			dReal delta = b[index] - dMUL(lambda[index],Ad[index]);
			dRealMutablePtr fc_ptr = fc + 6*b1;

			// @@@ potential optimization: SIMD-ize this and the b2 >= 0 case
			delta -=dMUL(fc_ptr[0],J_ptr[0]) + dMUL(fc_ptr[1],J_ptr[1]) +
				dMUL(fc_ptr[2],J_ptr[2]) + dMUL(fc_ptr[3],J_ptr[3]) +
				dMUL(fc_ptr[4],J_ptr[4]) + dMUL(fc_ptr[5],J_ptr[5]);
			// @@@ potential optimization: handle 1-body constraints in a separate
			//     loop to avoid the cost of test & jump?
			if (b2 >= 0) {
				fc_ptr = fc + 6*b2;
				delta -=dMUL(fc_ptr[0],J_ptr[6]) + dMUL(fc_ptr[1],J_ptr[7]) +
					dMUL(fc_ptr[2],J_ptr[8]) + dMUL(fc_ptr[3],J_ptr[9]) +
					dMUL(fc_ptr[4],J_ptr[10]) + dMUL(fc_ptr[5],J_ptr[11]);
			}

			// compute lambda and clamp it to [lo,hi].
			// @@@ potential optimization: does SSE have clamping instructions
			//     to save test+jump penalties here?
			dReal new_lambda = lambda[index] + delta;
			if (new_lambda < lo[index]) {
				delta = lo[index]-lambda[index];
				lambda[index] = lo[index];
			}
			else if (new_lambda > hi[index]) {
				delta = hi[index]-lambda[index];
				lambda[index] = hi[index];
			}
			else {
				lambda[index] = new_lambda;
			}

			//@@@ a trick that may or may not help
			//dReal ramp = (1-((dReal)(iteration+1)/(dReal)num_iterations));
			//delta *= ramp;

			// update fc.
			// @@@ potential optimization: SIMD for this and the b2 >= 0 case
			fc_ptr = fc + 6*b1;
			fc_ptr[0] += dMUL(delta,iMJ_ptr[0]);
			fc_ptr[1] += dMUL(delta,iMJ_ptr[1]);
			fc_ptr[2] += dMUL(delta,iMJ_ptr[2]);
			fc_ptr[3] += dMUL(delta,iMJ_ptr[3]);
			fc_ptr[4] += dMUL(delta,iMJ_ptr[4]);
			fc_ptr[5] += dMUL(delta,iMJ_ptr[5]);
			// @@@ potential optimization: handle 1-body constraints in a separate
			//     loop to avoid the cost of test & jump?
			if (b2 >= 0) {
				fc_ptr = fc + 6*b2;
				fc_ptr[0] += dMUL(delta,iMJ_ptr[6]);
				fc_ptr[1] += dMUL(delta,iMJ_ptr[7]);
				fc_ptr[2] += dMUL(delta,iMJ_ptr[8]);
				fc_ptr[3] += dMUL(delta,iMJ_ptr[9]);
				fc_ptr[4] += dMUL(delta,iMJ_ptr[10]);
				fc_ptr[5] += dMUL(delta,iMJ_ptr[11]);
			}
		}
	}
	
	free(hicopy);
	free(iMJ);
	free(Ad);
	free(order);

}


void dxQuickStepper (dxWorld *world, dxBody * const *body, int nb,
		     dxJoint * const *_joint, int nj, dReal stepsize)
{
	int i,j;
	IFTIMING(dTimerStart("preprocessing");)

	dReal stepsize1 = dRecip(stepsize);

	// number all bodies in the body list - set their tag values
	for (i=0; i<nb; i++) body[i]->tag = i;

	// make a local copy of the joint array, because we might want to modify it.
	// (the "dxJoint *const*" declaration says we're allowed to modify the joints
	// but not the joint array, because the caller might need it unchanged).
	//@@@ do we really need to do this? we'll be sorting constraint rows individually, not joints
	dxJoint **joint = (dxJoint**) malloc (nj * sizeof(dxJoint*));
	if(joint == NULL) {
		return;
	}
	memcpy (joint,_joint,nj * sizeof(dxJoint*));

	// for all bodies, compute the inertia tensor and its inverse in the global
	// frame, and compute the rotational force and add it to the torque
	// accumulator. I and invI are a vertical stack of 3x4 matrices, one per body.
	//dRealAllocaArray (I,3*4*nb);	// need to remember all I's for feedback purposes only
	dRealAllocaArray (invI,3*4*nb);
	if( invI == NULL) {
		free(joint);
		return;
	}
	for (i=0; i<nb; i++) {
		dMatrix3 tmp;

		// compute inverse inertia tensor in global frame
		dMULTIPLY2_333 (tmp,body[i]->invI,body[i]->posr.R);
		dMULTIPLY0_333 (invI+i*12,body[i]->posr.R,tmp);
	}

	// add the gravity force to all bodies
	for (i=0; i<nb; i++) {
		if ((body[i]->flags & dxBodyNoGravity)==0) {
			body[i]->facc[0] += dMUL( body[i]->mass.mass,world->gravity[0]);
			body[i]->facc[1] += dMUL(body[i]->mass.mass,world->gravity[1]);
			body[i]->facc[2] += dMUL(body[i]->mass.mass,world->gravity[2]);
		}
	}

	// get joint information (m = total constraint dimension, nub = number of unbounded variables).
	// joints with m=0 are inactive and are removed from the joints array
	// entirely, so that the code that follows does not consider them.
	//@@@ do we really need to save all the info1's
	dxJoint::Info1 *info = (dxJoint::Info1*) malloc (nj*sizeof(dxJoint::Info1));
	if( info == NULL) {
		free(joint);
		free(invI);
		return;
	}
	for (i=0, j=0; j<nj; j++) {	// i=dest, j=src
		joint[j]->vtable->getInfo1 (joint[j],info+i);

		if (info[i].m > 0) {
			joint[i] = joint[j];
			i++;
		}
	}
	nj = i;

	// create the row offset array
	int m = 0;
	int *ofs = (int*) malloc (nj*sizeof(int));
	if( ofs == NULL) {
		free(joint);
		free(invI);
		free(info);
		return;
	}
	for (i=0; i<nj; i++) {
		ofs[i] = m;
		m += info[i].m;
	}

	// if there are constraints, compute the constraint force
	dRealAllocaArray (J,m*12);
	if( J == NULL) {
		free(joint);
		free(invI);
		free(info);
		free(ofs);
		return;
	}
	int *jb = (int*) malloc (m*2*sizeof(int));
	if( jb == NULL) {
		free(joint);
		free(invI);
		free(info);
		free(ofs);
		free(J);
		return;
	}
	if (m > 0) {
		// create a constraint equation right hand side vector `c', a constraint
		// force mixing vector `cfm', and LCP low and high bound vectors, and an
		// 'findex' vector.
		dRealAllocaArray (c,m);
		if( c == NULL) {
			free(joint);
			free(invI);
			free(info);
			free(ofs);
			free(J);
			free(jb);
			return;
		}
		dRealAllocaArray (cfm,m);
		if( cfm == NULL) {
			free(joint);
			free(invI);
			free(info);
			free(ofs);
			free(J);
			free(jb);
			free(c);
			return;
		}
		dRealAllocaArray (lo,m);
		if( lo == NULL) {
			free(joint);
			free(invI);
			free(info);
			free(ofs);
			free(J);
			free(jb);
			free(c);
			free(cfm);
			return;
		}
		dRealAllocaArray (hi,m);
		if( hi == NULL) {
			free(joint);
			free(invI);
			free(info);
			free(ofs);
			free(J);
			free(jb);
			free(c);
			free(cfm);
			free(lo);
			return;
		}
		int *findex = (int*) malloc (m*sizeof(int));
		if( findex == NULL) {
			free(joint);
			free(invI);
			free(info);
			free(ofs);
			free(J);
			free(jb);
			free(c);
			free(cfm);
			free(lo);
			free(hi);
			return;
		}
		dSetZero (c,m);
		dSetValue (cfm,m,world->global_cfm);
		dSetValue (lo,m,-dInfinity);
		dSetValue (hi,m, dInfinity);
		for (i=0; i<m; i++) findex[i] = -1;

		// get jacobian data from constraints. an m*12 matrix will be created
		// to store the two jacobian blocks from each constraint. it has this
		// format:
		//
		//   l1 l1 l1 a1 a1 a1 l2 l2 l2 a2 a2 a2 \    .
		//   l1 l1 l1 a1 a1 a1 l2 l2 l2 a2 a2 a2  }-- jacobian for joint 0, body 1 and body 2 (3 rows)
		//   l1 l1 l1 a1 a1 a1 l2 l2 l2 a2 a2 a2 /
		//   l1 l1 l1 a1 a1 a1 l2 l2 l2 a2 a2 a2 }--- jacobian for joint 1, body 1 and body 2 (3 rows)
		//   etc...
		//
		//   (lll) = linear jacobian data
		//   (aaa) = angular jacobian data
		//
		IFTIMING (dTimerNow ("create J");)
		dSetZero (J,m*12);
		dxJoint::Info2 Jinfo;
		Jinfo.rowskip = 12;
		Jinfo.fps = stepsize1;
		Jinfo.erp = world->global_erp;
		int mfb = 0; // number of rows of Jacobian we will have to save for joint feedback
		for (i=0; i<nj; i++) {
			Jinfo.J1l = J + ofs[i]*12;
			Jinfo.J1a = Jinfo.J1l + 3;
			Jinfo.J2l = Jinfo.J1l + 6;
			Jinfo.J2a = Jinfo.J1l + 9;
			Jinfo.c = c + ofs[i];
			Jinfo.cfm = cfm + ofs[i];
			Jinfo.lo = lo + ofs[i];
			Jinfo.hi = hi + ofs[i];
			Jinfo.findex = findex + ofs[i];
			joint[i]->vtable->getInfo2 (joint[i],&Jinfo);
			// adjust returned findex values for global index numbering
			for (j=0; j<info[i].m; j++) {
				if (findex[ofs[i] + j] >= 0) findex[ofs[i] + j] += ofs[i];
			}
			if (joint[i]->feedback)
				mfb += info[i].m;
		}

		// we need a copy of Jacobian for joint feedbacks
		// because it gets destroyed by SOR solver
		// instead of saving all Jacobian, we can save just rows
		// for joints, that requested feedback (which is normaly much less)
		dRealAllocaArray (Jcopy,mfb*12);
		if( Jcopy == NULL) {
			free(joint);
			free(invI);
			free(info);
			free(ofs);
			free(J);
			free(jb);
			free(c);
			free(cfm);
			free(lo);
			free(hi);
			free(findex);
			return;
		}
		if (mfb > 0) {
			mfb = 0;
			for (i=0; i<nj; i++)
				if (joint[i]->feedback) {
					memcpy(Jcopy+mfb*12, J+ofs[i]*12, info[i].m*12*sizeof(dReal));
					mfb += info[i].m;
				}
		}


		// create an array of body numbers for each joint row
		int *jb_ptr = jb;
		for (i=0; i<nj; i++) {
			int b1 = (joint[i]->node[0].body) ? (joint[i]->node[0].body->tag) : -1;
			int b2 = (joint[i]->node[1].body) ? (joint[i]->node[1].body->tag) : -1;
			for (j=0; j<info[i].m; j++) {
				jb_ptr[0] = b1;
				jb_ptr[1] = b2;
				jb_ptr += 2;
			}
		}


		// compute the right hand side `rhs'
		IFTIMING (dTimerNow ("compute rhs");)
		dRealAllocaArray (tmp1,nb*6);
		if( tmp1 == NULL) {
			free(joint);
			free(invI);
			free(info);
			free(ofs);
			free(J);
			free(jb);
			free(c);
			free(cfm);
			free(lo);
			free(hi);
			free(findex);
			free(Jcopy);
			return;
		}
		// put v/h + invM*fe into tmp1
		for (i=0; i<nb; i++) {
			dReal body_invMass = body[i]->invMass;
			for (j=0; j<3; j++) tmp1[i*6+j] = dMUL(body[i]->facc[j],body_invMass) + dMUL(body[i]->lvel[j],stepsize1);
			dMULTIPLY0_331 (tmp1 + i*6 + 3,invI + i*12,body[i]->tacc);
			for (j=0; j<3; j++) tmp1[i*6+3+j] += dMUL(body[i]->avel[j],stepsize1);
		}

		// put J*tmp1 into rhs
		dRealAllocaArray (rhs,m);
		if( rhs == NULL) {
			free(joint);
			free(invI);
			free(info);
			free(ofs);
			free(J);
			free(jb);
			free(c);
			free(cfm);
			free(lo);
			free(hi);
			free(findex);
			free(Jcopy);
			free(tmp1);
			return;
		}
		multiply_J (m,J,jb,tmp1,rhs);

		// complete rhs
		for (i=0; i<m; i++) rhs[i] = dMUL(c[i],stepsize1) - rhs[i];

		// scale CFM
		for (i=0; i<m; i++) cfm[i] = dMUL(cfm[i],stepsize1);

		// load lambda from the value saved on the previous iteration
		dRealAllocaArray (lambda,m);
		if( lambda == NULL) {
			free(joint);
			free(invI);
			free(info);
			free(ofs);
			free(J);
			free(jb);
			free(c);
			free(cfm);
			free(lo);
			free(hi);
			free(findex);
			free(Jcopy);
			free(tmp1);
			free(rhs);
			return;
		}

		// solve the LCP problem and get lambda and invM*constraint_force
		IFTIMING (dTimerNow ("solving LCP problem");)
		dRealAllocaArray (cforce,nb*6);
		if( cforce == NULL) {
			free(joint);
			free(invI);
			free(info);
			free(ofs);
			free(J);
			free(jb);
			free(c);
			free(cfm);
			free(lo);
			free(hi);
			free(findex);
			free(Jcopy);
			free(tmp1);
			free(rhs);
			free(lambda);
			return;
		}
		SOR_LCP (m,nb,J,jb,body,invI,lambda,cforce,rhs,lo,hi,cfm,findex,&world->qs);


		// note that the SOR method overwrites rhs and J at this point, so
		// they should not be used again.

		// add stepsize * cforce to the body velocity
		for (i=0; i<nb; i++) {
			for (j=0; j<3; j++) body[i]->lvel[j] += dMUL(stepsize,cforce[i*6+j]);
			for (j=0; j<3; j++) body[i]->avel[j] += dMUL(stepsize,cforce[i*6+3+j]);
		}

		// if joint feedback is requested, compute the constraint force.
		// BUT: cforce is inv(M)*J'*lambda, whereas we want just J'*lambda,
		// so we must compute M*cforce.
		// @@@ if any joint has a feedback request we compute the entire
		//     adjusted cforce, which is not the most efficient way to do it.
		/*for (j=0; j<nj; j++) {
			if (joint[j]->feedback) {
				// compute adjusted cforce
				for (i=0; i<nb; i++) {
					dReal k = body[i]->mass.mass;
					cforce [i*6+0] *= k;
					cforce [i*6+1] *= k;
					cforce [i*6+2] *= k;
					dVector3 tmp;
					dMULTIPLY0_331 (tmp, I + 12*i, cforce + i*6 + 3);
					cforce [i*6+3] = tmp[0];
					cforce [i*6+4] = tmp[1];
					cforce [i*6+5] = tmp[2];
				}
				// compute feedback for this and all remaining joints
				for (; j<nj; j++) {
					dJointFeedback *fb = joint[j]->feedback;
					if (fb) {
						int b1 = joint[j]->node[0].body->tag;
						memcpy (fb->f1,cforce+b1*6,3*sizeof(dReal));
						memcpy (fb->t1,cforce+b1*6+3,3*sizeof(dReal));
						if (joint[j]->node[1].body) {
							int b2 = joint[j]->node[1].body->tag;
							memcpy (fb->f2,cforce+b2*6,3*sizeof(dReal));
							memcpy (fb->t2,cforce+b2*6+3,3*sizeof(dReal));
						}
					}
				}
			}
		}*/

		if (mfb > 0) {
			// straightforward computation of joint constraint forces:
			// multiply related lambdas with respective J' block for joints
			// where feedback was requested
			mfb = 0;
			for (i=0; i<nj; i++) {
				if (joint[i]->feedback) {
					dJointFeedback *fb = joint[i]->feedback;
					dReal data[6];
					Multiply1_12q1 (data, Jcopy+mfb*12, lambda+ofs[i], info[i].m);
					fb->f1[0] = data[0];
					fb->f1[1] = data[1];
					fb->f1[2] = data[2];
					fb->t1[0] = data[3];
					fb->t1[1] = data[4];
					fb->t1[2] = data[5];
					if (joint[i]->node[1].body)
					{
						Multiply1_12q1 (data, Jcopy+mfb*12+6, lambda+ofs[i], info[i].m);
						fb->f2[0] = data[0];
						fb->f2[1] = data[1];
						fb->f2[2] = data[2];
						fb->t2[0] = data[3];
						fb->t2[1] = data[4];
						fb->t2[2] = data[5];
					}
					mfb += info[i].m;
				}
			}
		}

		free(c);
		free(cfm);
		free(lo);
		free(hi);
		free(findex);
		free(Jcopy);
		free(tmp1);
		free(rhs);
		free(lambda);
		free(cforce);
		
	}

	// compute the velocity update:
	// add stepsize * invM * fe to the body velocity

	IFTIMING (dTimerNow ("compute velocity update");)
	for (i=0; i<nb; i++) {
		dReal body_invMass = body[i]->invMass;
		for (j=0; j<3; j++) body[i]->lvel[j] += dMUL(stepsize,dMUL(body_invMass,body[i]->facc[j]));
		for (j=0; j<3; j++) body[i]->tacc[j] = dMUL(body[i]->tacc[j],stepsize);
		dMULTIPLYADD0_331 (body[i]->avel,invI + i*12,body[i]->tacc);
	}


	// update the position and orientation from the new linear/angular velocity
	// (over the given timestep)
	IFTIMING (dTimerNow ("update position");)
	for (i=0; i<nb; i++) dxStepBody (body[i],stepsize);

	IFTIMING (dTimerNow ("tidy up");)

	// zero all force accumulators
	for (i=0; i<nb; i++) {
		dSetZero (body[i]->facc,3);
		dSetZero (body[i]->tacc,3);
	}

	IFTIMING (dTimerEnd();)
	IFTIMING (if (m > 0) dTimerReport (stdout,1);)
	

	free(joint);
	free(invI);
	free(info);
	free(ofs);
	free(J);
	free(jb);

}
