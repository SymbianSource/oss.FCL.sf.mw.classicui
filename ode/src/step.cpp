/*************************************************************************
 *                                                                       *
 * Open Dynamics Engine, Copyright (C) 2001,2002 Russell L. Smith.       *
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
#include "lcp.h"
#include "util.h"

//****************************************************************************
// misc defines

// memory allocation system
#ifdef dUSE_MALLOC_FOR_ALLOCA
unsigned int dMemoryFlag;
#define REPORT_OUT_OF_MEMORY fprintf(stderr, "Insufficient memory to complete rigid body simulation.  Results will not be accurate.\n")

#define ALLOCA(t,v,s) t* v=(t*)malloc(s)
#define UNALLOCA(t)  free(t)

#else
#define ALLOCA(t,v,s) t* v=(t*)dALLOCA16(s)
#define UNALLOCA(t)  /* nothing */
#endif


// undef to use the fast decomposition
#define DIRECT_CHOLESKY

//****************************************************************************
// special matrix multipliers

// this assumes the 4th and 8th rows of B and C are zero.

static void Multiply2_p8r (dReal *A, dReal *B, dReal *C,
			   int p, int r, int Askip)
{
  int i,j;
  dReal sum,*bb,*cc;

  bb = B;
  for (i=p; i; i--) {
    cc = C;
    for (j=r; j; j--) {
      sum = dMUL(bb[0],cc[0]);
      sum += dMUL(bb[1],cc[1]);
      sum += dMUL(bb[2],cc[2]);
      sum += dMUL(bb[4],cc[4]);
      sum += dMUL(bb[5],cc[5]);
      sum += dMUL(bb[6],cc[6]);
      *(A++) = sum; 
      cc += 8;
    }
    A += Askip - r;
    bb += 8;
  }
}


// this assumes the 4th and 8th rows of B and C are zero.

static void MultiplyAdd2_p8r (dReal *A, dReal *B, dReal *C,
			      int p, int r, int Askip)
{
  int i,j;
  dReal sum,*bb,*cc;

  bb = B;
  for (i=p; i; i--) {
    cc = C;
    for (j=r; j; j--) {
      sum = dMUL(bb[0],cc[0]);
      sum += dMUL(bb[1],cc[1]);
      sum += dMUL(bb[2],cc[2]);
      sum += dMUL(bb[4],cc[4]);
      sum += dMUL(bb[5],cc[5]);
      sum += dMUL(bb[6],cc[6]);
      *(A++) += sum; 
      cc += 8;
    }
    A += Askip - r;
    bb += 8;
  }
}


// this assumes the 4th and 8th rows of B are zero.

static void Multiply0_p81 (dReal *A, dReal *B, dReal *C, int p)
{
  int i;

  dReal sum;
  for (i=p; i; i--) {
    sum =  dMUL(B[0],C[0]);
    sum += dMUL(B[1],C[1]);
    sum += dMUL(B[2],C[2]);
    sum += dMUL(B[4],C[4]);
    sum += dMUL(B[5],C[5]);
    sum += dMUL(B[6],C[6]);
    *(A++) = sum;
    B += 8;
  }
}


// this assumes the 4th and 8th rows of B are zero.

static void MultiplyAdd0_p81 (dReal *A, dReal *B, dReal *C, int p)
{
  int i;

  dReal sum;
  for (i=p; i; i--) {
    sum =  dMUL(B[0],C[0]);
    sum += dMUL(B[1],C[1]);
    sum += dMUL(B[2],C[2]);
    sum += dMUL(B[4],C[4]);
    sum += dMUL(B[5],C[5]);
    sum += dMUL(B[6],C[6]);
    *(A++) += sum;
    B += 8;
  }
}


// this assumes the 4th and 8th rows of B are zero.

static void MultiplyAdd1_8q1 (dReal *A, dReal *B, dReal *C, int q)
{
  int k;
  dReal sum;

  sum = 0;
  for (k=0; k<q; k++) sum += dMUL(B[k*8],C[k]);
  A[0] += sum;
  sum = 0;
  for (k=0; k<q; k++) sum += dMUL(B[1+k*8],C[k]);
  A[1] += sum;
  sum = 0;
  for (k=0; k<q; k++) sum += dMUL(B[2+k*8],C[k]);
  A[2] += sum;
  sum = 0;
  for (k=0; k<q; k++) sum += dMUL(B[4+k*8],C[k]);
  A[4] += sum;
  sum = 0;
  for (k=0; k<q; k++) sum += dMUL(B[5+k*8],C[k]);
  A[5] += sum;
  sum = 0;
  for (k=0; k<q; k++) sum += dMUL(B[6+k*8],C[k]);
  A[6] += sum;
}


// this assumes the 4th and 8th rows of B are zero.

static void Multiply1_8q1 (dReal *A, dReal *B, dReal *C, int q)
{
  int k;
  dReal sum;

  sum = 0;
  for (k=0; k<q; k++) sum += dMUL(B[k*8],C[k]);
  A[0] = sum;
  sum = 0;
  for (k=0; k<q; k++) sum += dMUL(B[1+k*8],C[k]);
  A[1] = sum;
  sum = 0;
  for (k=0; k<q; k++) sum += dMUL(B[2+k*8],C[k]);
  A[2] = sum;
  sum = 0;
  for (k=0; k<q; k++) sum += dMUL(B[4+k*8],C[k]);
  A[4] = sum;
  sum = 0;
  for (k=0; k<q; k++) sum += dMUL(B[5+k*8],C[k]);
  A[5] = sum;
  sum = 0;
  for (k=0; k<q; k++) sum += dMUL(B[6+k*8],C[k]);
  A[6] = sum;
}

//****************************************************************************
// the slow, but sure way
// note that this does not do any joint feedback!

// given lists of bodies and joints that form an island, perform a first
// order timestep.
//
// `body' is the body array, `nb' is the size of the array.
// `_joint' is the body array, `nj' is the size of the array.

void dInternalStepIsland_x1 (dxWorld *world, dxBody * const *body, int nb,
			     dxJoint * const *_joint, int nj, dReal stepsize)
{
  int i,j,k;
  int n6 = 6*nb;


  // number all bodies in the body list - set their tag values
  for (i=0; i<nb; i++) body[i]->tag = i;

  // make a local copy of the joint array, because we might want to modify it.
  // (the "dxJoint *const*" declaration says we're allowed to modify the joints
  // but not the joint array, because the caller might need it unchanged).
  ALLOCA(dxJoint*,joint,nj*sizeof(dxJoint*));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (joint == NULL) {
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
  memcpy (joint,_joint,nj * sizeof(dxJoint*));

  // for all bodies, compute the inertia tensor and its inverse in the global
  // frame, and compute the rotational force and add it to the torque
  // accumulator.
  // @@@ check computation of rotational force.
  ALLOCA(dReal,I,3*nb*4*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (I == NULL) {
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
  ALLOCA(dReal,invI,3*nb*4*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (invI == NULL) {
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif

  //dSetZero (I,3*nb*4);
  //dSetZero (invI,3*nb*4);
  for (i=0; i<nb; i++) {
    dReal tmp[12];
    // compute inertia tensor in global frame
    dMULTIPLY2_333 (tmp,body[i]->mass.I,body[i]->posr.R);
    dMULTIPLY0_333 (I+i*12,body[i]->posr.R,tmp);
    // compute inverse inertia tensor in global frame
    dMULTIPLY2_333 (tmp,body[i]->invI,body[i]->posr.R);
    dMULTIPLY0_333 (invI+i*12,body[i]->posr.R,tmp);
    // compute rotational force
    dMULTIPLY0_331 (tmp,I+i*12,body[i]->avel);
    dCROSS (body[i]->tacc,-=,body[i]->avel,tmp);
  }

  // add the gravity force to all bodies
  for (i=0; i<nb; i++) {
    if ((body[i]->flags & dxBodyNoGravity)==0) {
      body[i]->facc[0] += dMUL(body[i]->mass.mass,world->gravity[0]);
      body[i]->facc[1] += dMUL(body[i]->mass.mass,world->gravity[1]);
      body[i]->facc[2] += dMUL(body[i]->mass.mass,world->gravity[2]);
    }
  }

  // get m = total constraint dimension, nub = number of unbounded variables.
  // create constraint offset array and number-of-rows array for all joints.
  // the constraints are re-ordered as follows: the purely unbounded
  // constraints, the mixed unbounded + LCP constraints, and last the purely
  // LCP constraints.
  //
  // joints with m=0 are inactive and are removed from the joints array
  // entirely, so that the code that follows does not consider them.
  int m = 0;
  ALLOCA(dxJoint::Info1,info,nj*sizeof(dxJoint::Info1));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (info == NULL) {
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif

  ALLOCA(int,ofs,nj*sizeof(int));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (ofs == NULL) {
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif

  for (i=0, j=0; j<nj; j++) {	// i=dest, j=src
    joint[j]->vtable->getInfo1 (joint[j],info+i);

    if (info[i].m > 0) {
      joint[i] = joint[j];
      i++;
    }
  }
  nj = i;

  // the purely unbounded constraints
  for (i=0; i<nj; i++) if (info[i].nub == info[i].m) {
    ofs[i] = m;
    m += info[i].m;
  }
  // the mixed unbounded + LCP constraints
  for (i=0; i<nj; i++) if (info[i].nub > 0 && info[i].nub < info[i].m) {
    ofs[i] = m;
    m += info[i].m;
  }
  // the purely LCP constraints
  for (i=0; i<nj; i++) if (info[i].nub == 0) {
    ofs[i] = m;
    m += info[i].m;
  }

  // create (6*nb,6*nb) inverse mass matrix `invM', and fill it with mass
  // parameters
  int nskip = dPAD (n6);
  ALLOCA(dReal, invM, n6*nskip*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (invM == NULL) {
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif

  dSetZero (invM,n6*nskip);
  for (i=0; i<nb; i++) {
    dReal *MM = invM+(i*6)*nskip+(i*6);
    MM[0] = body[i]->invMass;
    MM[nskip+1] = body[i]->invMass;
    MM[2*nskip+2] = body[i]->invMass;
    MM += 3*nskip+3;
    for (j=0; j<3; j++) for (k=0; k<3; k++) {
      MM[j*nskip+k] = invI[i*12+j*4+k];
    }
  }

  // assemble some body vectors: fe = external forces, v = velocities
  ALLOCA(dReal,fe,n6*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (fe == NULL) {
      UNALLOCA(invM);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif

  ALLOCA(dReal,v,n6*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (v == NULL) {
      UNALLOCA(fe);
      UNALLOCA(invM);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif

  //dSetZero (fe,n6);
  //dSetZero (v,n6);
  for (i=0; i<nb; i++) {
    for (j=0; j<3; j++) fe[i*6+j] = body[i]->facc[j];
    for (j=0; j<3; j++) fe[i*6+3+j] = body[i]->tacc[j];
    for (j=0; j<3; j++) v[i*6+j] = body[i]->lvel[j];
    for (j=0; j<3; j++) v[i*6+3+j] = body[i]->avel[j];
  }

  // this will be set to the velocity update
  ALLOCA(dReal,vnew,n6*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (vnew == NULL) {
      UNALLOCA(v);
      UNALLOCA(fe);
      UNALLOCA(invM);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
  dSetZero (vnew,n6);

  // if there are constraints, compute cforce
  if (m > 0) {
    // create a constraint equation right hand side vector `c', a constraint
    // force mixing vector `cfm', and LCP low and high bound vectors, and an
    // 'findex' vector.
    ALLOCA(dReal,c,m*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (c == NULL) {
      UNALLOCA(vnew);
      UNALLOCA(v);
      UNALLOCA(fe);
      UNALLOCA(invM);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    ALLOCA(dReal,cfm,m*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (cfm == NULL) {
      UNALLOCA(c);
      UNALLOCA(vnew);
      UNALLOCA(v);
      UNALLOCA(fe);
      UNALLOCA(invM);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    ALLOCA(dReal,lo,m*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (lo == NULL) {
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(vnew);
      UNALLOCA(v);
      UNALLOCA(fe);
      UNALLOCA(invM);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    ALLOCA(dReal,hi,m*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (hi == NULL) {
      UNALLOCA(lo);
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(vnew);
      UNALLOCA(v);
      UNALLOCA(fe);
      UNALLOCA(invM);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    ALLOCA(int,findex,m*sizeof(int));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (findex == NULL) {
      UNALLOCA(hi);
      UNALLOCA(lo);
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(vnew);
      UNALLOCA(v);
      UNALLOCA(fe);
      UNALLOCA(invM);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    dSetZero (c,m);
    dSetValue (cfm,m,world->global_cfm);
    dSetValue (lo,m,-dInfinity);
    dSetValue (hi,m, dInfinity);
    for (i=0; i<m; i++) findex[i] = -1;

    // create (m,6*nb) jacobian mass matrix `J', and fill it with constraint
    // data. also fill the c vector.

    ALLOCA(dReal,J,m*nskip*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (J == NULL) {
      UNALLOCA(findex);
      UNALLOCA(hi);
      UNALLOCA(lo);
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(vnew);
      UNALLOCA(v);
      UNALLOCA(fe);
      UNALLOCA(invM);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    dSetZero (J,m*nskip);
    dxJoint::Info2 Jinfo;
    Jinfo.rowskip = nskip;
    Jinfo.fps = dRecip(stepsize);
    Jinfo.erp = world->global_erp;
    for (i=0; i<nj; i++) {
      Jinfo.J1l = J + nskip*ofs[i] + 6*joint[i]->node[0].body->tag;
      Jinfo.J1a = Jinfo.J1l + 3;
      if (joint[i]->node[1].body) {
	Jinfo.J2l = J + nskip*ofs[i] + 6*joint[i]->node[1].body->tag;
	Jinfo.J2a = Jinfo.J2l + 3;
      }
      else {
	Jinfo.J2l = 0;
	Jinfo.J2a = 0;
      }
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
    }

    // compute A = J*invM*J'

    ALLOCA(dReal,JinvM,m*nskip*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (JinvM == NULL) {
      UNALLOCA(J);
      UNALLOCA(findex);
      UNALLOCA(hi);
      UNALLOCA(lo);
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(vnew);
      UNALLOCA(v);
      UNALLOCA(fe);
      UNALLOCA(invM);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    //dSetZero (JinvM,m*nskip);
    dMultiply0 (JinvM,J,invM,m,n6,n6);
    int mskip = dPAD(m);
    ALLOCA(dReal,A,m*mskip*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (A == NULL) {
      UNALLOCA(JinvM);
      UNALLOCA(J);
      UNALLOCA(findex);
      UNALLOCA(hi);
      UNALLOCA(lo);
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(vnew);
      UNALLOCA(v);
      UNALLOCA(fe);
      UNALLOCA(invM);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    //dSetZero (A,m*mskip);
    dMultiply2 (A,JinvM,J,m,n6,m);

    // add cfm to the diagonal of A
    for (i=0; i<m; i++) A[i*mskip+i] += dMUL(cfm[i],Jinfo.fps);

    // compute `rhs', the right hand side of the equation J*a=c
    ALLOCA(dReal,tmp1,n6*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (tmp1 == NULL) {
      UNALLOCA(A);
      UNALLOCA(JinvM);
      UNALLOCA(J);
      UNALLOCA(findex);
      UNALLOCA(hi);
      UNALLOCA(lo);
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(vnew);
      UNALLOCA(v);
      UNALLOCA(fe);
      UNALLOCA(invM);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    //dSetZero (tmp1,n6);
    dMultiply0 (tmp1,invM,fe,n6,n6,1);
    for (i=0; i<n6; i++) tmp1[i] += dDIV(v[i],stepsize);
    ALLOCA(dReal,rhs,m*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (rhs == NULL) {
      UNALLOCA(tmp1);
      UNALLOCA(A);
      UNALLOCA(JinvM);
      UNALLOCA(J);
      UNALLOCA(findex);
      UNALLOCA(hi);
      UNALLOCA(lo);
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(vnew);
      UNALLOCA(v);
      UNALLOCA(fe);
      UNALLOCA(invM);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    //dSetZero (rhs,m);
    dMultiply0 (rhs,J,tmp1,m,n6,1);
    for (i=0; i<m; i++) rhs[i] = dDIV(c[i],stepsize) - rhs[i];




#ifndef DIRECT_CHOLESKY
    // solve the LCP problem and get lambda.
    // this will destroy A but that's okay
    ALLOCA(dReal,lambda,m*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (lambda == NULL) {
      UNALLOCA(rhs);
      UNALLOCA(tmp1);
      UNALLOCA(A);
      UNALLOCA(JinvM);
      UNALLOCA(J);
      UNALLOCA(findex);
      UNALLOCA(hi);
      UNALLOCA(lo);
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(vnew);
      UNALLOCA(v);
      UNALLOCA(fe);
      UNALLOCA(invM);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    ALLOCA(dReal,residual,m*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (residual == NULL) {
      UNALLOCA(lambda);
      UNALLOCA(rhs);
      UNALLOCA(tmp1);
      UNALLOCA(A);
      UNALLOCA(JinvM);
      UNALLOCA(J);
      UNALLOCA(findex);
      UNALLOCA(hi);
      UNALLOCA(lo);
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(vnew);
      UNALLOCA(v);
      UNALLOCA(fe);
      UNALLOCA(invM);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    dSolveLCP (m,A,lambda,rhs,residual,nub,lo,hi,findex);
    UNALLOCA(residual);
    UNALLOCA(lambda);

#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (dMemoryFlag == d_MEMORY_OUT_OF_MEMORY)
      return;
#endif


#else

    // OLD WAY - direct factor and solve

    // factorize A (L*L'=A)

    ALLOCA(dReal,L,m*mskip*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (L == NULL) {
      UNALLOCA(rhs);
      UNALLOCA(tmp1);
      UNALLOCA(A);
      UNALLOCA(JinvM);
      UNALLOCA(J);
      UNALLOCA(findex);
      UNALLOCA(hi);
      UNALLOCA(lo);
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(vnew);
      UNALLOCA(v);
      UNALLOCA(fe);
      UNALLOCA(invM);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    memcpy (L,A,m*mskip*sizeof(dReal));

    // compute lambda

    ALLOCA(dReal,lambda,m*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (lambda == NULL) {
      UNALLOCA(L);
      UNALLOCA(rhs);
      UNALLOCA(tmp1);
      UNALLOCA(A);
      UNALLOCA(JinvM);
      UNALLOCA(J);
      UNALLOCA(findex);
      UNALLOCA(hi);
      UNALLOCA(lo);
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(vnew);
      UNALLOCA(v);
      UNALLOCA(fe);
      UNALLOCA(invM);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    memcpy (lambda,rhs,m * sizeof(dReal));
    dSolveCholesky (L,lambda,m);
#endif


    // compute the velocity update `vnew'
    dMultiply1 (tmp1,J,lambda,n6,m,1);
    for (i=0; i<n6; i++) tmp1[i] += fe[i];
    dMultiply0 (vnew,invM,tmp1,n6,n6,1);
    for (i=0; i<n6; i++) vnew[i] = v[i] + dMUL(stepsize,vnew[i]);


    UNALLOCA(c);
    UNALLOCA(cfm);
    UNALLOCA(lo);
    UNALLOCA(hi);
    UNALLOCA(findex);
    UNALLOCA(J);
    UNALLOCA(JinvM);
    UNALLOCA(A);
    UNALLOCA(tmp1);
    UNALLOCA(rhs);
    UNALLOCA(lambda); 
    UNALLOCA(L);
  }
  else {
    // no constraints
    dMultiply0 (vnew,invM,fe,n6,n6,1);
    for (i=0; i<n6; i++) vnew[i] = v[i] + dMUL(stepsize,vnew[i]);
  }

  // apply the velocity update to the bodies
  for (i=0; i<nb; i++) {
    for (j=0; j<3; j++) body[i]->lvel[j] = vnew[i*6+j];
    for (j=0; j<3; j++) body[i]->avel[j] = vnew[i*6+3+j];
  }

  // update the position and orientation from the new linear/angular velocity
  // (over the given timestep)

  for (i=0; i<nb; i++) dxStepBody (body[i],stepsize);

  // zero all force accumulators
  for (i=0; i<nb; i++) {
    body[i]->facc[0] = 0;
    body[i]->facc[1] = 0;
    body[i]->facc[2] = 0;
    body[i]->facc[3] = 0;
    body[i]->tacc[0] = 0;
    body[i]->tacc[1] = 0;
    body[i]->tacc[2] = 0;
    body[i]->tacc[3] = 0;
  }


  UNALLOCA(joint);
  UNALLOCA(I);
  UNALLOCA(invI);
  UNALLOCA(info);
  UNALLOCA(ofs);
  UNALLOCA(invM);
  UNALLOCA(fe);
  UNALLOCA(v);
  UNALLOCA(vnew);
}

//****************************************************************************
// an optimized version of dInternalStepIsland1()

void dInternalStepIsland_x2 (dxWorld *world, dxBody * const *body, int nb,
			     dxJoint * const *_joint, int nj, dReal stepsize)
{
  int i,j,k;
  dReal stepsize1 = dRecip(stepsize);

  // number all bodies in the body list - set their tag values
  for (i=0; i<nb; i++) body[i]->tag = i;

  // make a local copy of the joint array, because we might want to modify it.
  // (the "dxJoint *const*" declaration says we're allowed to modify the joints
  // but not the joint array, because the caller might need it unchanged).
  ALLOCA(dxJoint*,joint,nj*sizeof(dxJoint*));
#ifdef dUSE_MALLOC_FOR_ALLOCA
  if (joint == NULL) {
    dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
    return;
  }
#endif
  memcpy (joint,_joint,nj * sizeof(dxJoint*));

  // for all bodies, compute the inertia tensor and its inverse in the global
  // frame, and compute the rotational force and add it to the torque
  // accumulator. I and invI are vertically stacked 3x4 matrices, one per body.
  // @@@ check computation of rotational force.

  dReal *I = NULL;

  ALLOCA(dReal,invI,3*nb*4*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
  if (invI == NULL) {
    UNALLOCA(I);
    UNALLOCA(joint);
    dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
    return;
  }
#endif

  //dSetZero (I,3*nb*4);
  //dSetZero (invI,3*nb*4);
  for (i=0; i<nb; i++) {
    dReal tmp[12];

    // compute inverse inertia tensor in global frame
    dMULTIPLY2_333 (tmp,body[i]->invI,body[i]->posr.R);
    dMULTIPLY0_333 (invI+i*12,body[i]->posr.R,tmp);
  }

  // add the gravity force to all bodies
  for (i=0; i<nb; i++) {
    if ((body[i]->flags & dxBodyNoGravity)==0) {
      body[i]->facc[0] += dMUL(body[i]->mass.mass,world->gravity[0]);
      body[i]->facc[1] += dMUL(body[i]->mass.mass,world->gravity[1]);
      body[i]->facc[2] += dMUL(body[i]->mass.mass,world->gravity[2]);
    }
  }

  // get m = total constraint dimension, nub = number of unbounded variables.
  // create constraint offset array and number-of-rows array for all joints.
  // the constraints are re-ordered as follows: the purely unbounded
  // constraints, the mixed unbounded + LCP constraints, and last the purely
  // LCP constraints. this assists the LCP solver to put all unbounded
  // variables at the start for a quick factorization.
  //
  // joints with m=0 are inactive and are removed from the joints array
  // entirely, so that the code that follows does not consider them.
  // also number all active joints in the joint list (set their tag values).
  // inactive joints receive a tag value of -1.

  int m = 0;
  ALLOCA(dxJoint::Info1,info,nj*sizeof(dxJoint::Info1));
#ifdef dUSE_MALLOC_FOR_ALLOCA
  if (info == NULL) {
    UNALLOCA(invI);
    UNALLOCA(I);
    UNALLOCA(joint);
    dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
    return;
  }
#endif
  ALLOCA(int,ofs,nj*sizeof(int));
#ifdef dUSE_MALLOC_FOR_ALLOCA
  if (ofs == NULL) {
    UNALLOCA(info);
    UNALLOCA(invI);
    UNALLOCA(I);
    UNALLOCA(joint);
    dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
    return;
  }
#endif
  for (i=0, j=0; j<nj; j++) {	// i=dest, j=src
    joint[j]->vtable->getInfo1 (joint[j],info+i);

    if (info[i].m > 0) {
      joint[i] = joint[j];
      joint[i]->tag = i;
      i++;
    }
    else {
      joint[j]->tag = -1;
    }
  }
  nj = i;

  // the purely unbounded constraints
  for (i=0; i<nj; i++) if (info[i].nub == info[i].m) {
    ofs[i] = m;
    m += info[i].m;
  }
  int nub = m;
  // the mixed unbounded + LCP constraints
  for (i=0; i<nj; i++) if (info[i].nub > 0 && info[i].nub < info[i].m) {
    ofs[i] = m;
    m += info[i].m;
  }
  // the purely LCP constraints
  for (i=0; i<nj; i++) if (info[i].nub == 0) {
    ofs[i] = m;
    m += info[i].m;
  }

  // this will be set to the force due to the constraints
  ALLOCA(dReal,cforce,nb*8*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
  if (cforce == NULL) {
    UNALLOCA(ofs);
    UNALLOCA(info);
    UNALLOCA(invI);
    UNALLOCA(I);
    UNALLOCA(joint);
    dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
    return;
  }
#endif
  dSetZero (cforce,nb*8);

  // if there are constraints, compute cforce
  if (m > 0) {
    // create a constraint equation right hand side vector `c', a constraint
    // force mixing vector `cfm', and LCP low and high bound vectors, and an
    // 'findex' vector.
    ALLOCA(dReal,c,m*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (c == NULL) {
      UNALLOCA(cforce);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    ALLOCA(dReal,cfm,m*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (cfm == NULL) {
      UNALLOCA(c);
      UNALLOCA(cforce);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    ALLOCA(dReal,lo,m*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (lo == NULL) {
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(cforce);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    ALLOCA(dReal,hi,m*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (hi == NULL) {
      UNALLOCA(lo);
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(cforce);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    ALLOCA(int,findex,m*sizeof(int));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (findex == NULL) {
      UNALLOCA(hi);
      UNALLOCA(lo);
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(cforce);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    dSetZero (c,m);
    dSetValue (cfm,m,world->global_cfm);
    dSetValue (lo,m,-dInfinity);
    dSetValue (hi,m, dInfinity);
    for (i=0; i<m; i++) findex[i] = -1;

    // get jacobian data from constraints. a (2*m)x8 matrix will be created
    // to store the two jacobian blocks from each constraint. it has this
    // format:
    //
    //   l l l 0 a a a 0  \    .
    //   l l l 0 a a a 0   }-- jacobian body 1 block for joint 0 (3 rows)
    //   l l l 0 a a a 0  /
    //   l l l 0 a a a 0  \    .
    //   l l l 0 a a a 0   }-- jacobian body 2 block for joint 0 (3 rows)
    //   l l l 0 a a a 0  /
    //   l l l 0 a a a 0  }--- jacobian body 1 block for joint 1 (1 row)
    //   l l l 0 a a a 0  }--- jacobian body 2 block for joint 1 (1 row)
    //   etc...
    //
    //   (lll) = linear jacobian data
    //   (aaa) = angular jacobian data
    //
    ALLOCA(dReal,J,2*m*8*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (J == NULL) {
      UNALLOCA(findex);
      UNALLOCA(hi);
      UNALLOCA(lo);
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(cforce);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    dSetZero (J,2*m*8);
    dxJoint::Info2 Jinfo;
    Jinfo.rowskip = 8;
    Jinfo.fps = stepsize1;
    Jinfo.erp = world->global_erp;
    for (i=0; i<nj; i++) {
      Jinfo.J1l = J + 2*8*ofs[i];
      Jinfo.J1a = Jinfo.J1l + 4;
      Jinfo.J2l = Jinfo.J1l + 8*info[i].m;
      Jinfo.J2a = Jinfo.J2l + 4;
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
    }

    // compute A = J*invM*J'. first compute JinvM = J*invM. this has the same
    // format as J so we just go through the constraints in J multiplying by
    // the appropriate scalars and matrices.

    ALLOCA(dReal,JinvM,2*m*8*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (JinvM == NULL) {
      UNALLOCA(J);
      UNALLOCA(findex);
      UNALLOCA(hi);
      UNALLOCA(lo);
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(cforce);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    dSetZero (JinvM,2*m*8);
    for (i=0; i<nj; i++) {
      int b = joint[i]->node[0].body->tag;
      dReal body_invMass = body[b]->invMass;
      dReal *body_invI = invI + b*12;
      dReal *Jsrc = J + 2*8*ofs[i];
      dReal *Jdst = JinvM + 2*8*ofs[i];
      for (j=info[i].m-1; j>=0; j--) {
	for (k=0; k<3; k++) Jdst[k] = dMUL(Jsrc[k],body_invMass);
	dMULTIPLY0_133 (Jdst+4,Jsrc+4,body_invI);
	Jsrc += 8;
	Jdst += 8;
      }
      if (joint[i]->node[1].body) {
	b = joint[i]->node[1].body->tag;
	body_invMass = body[b]->invMass;
	body_invI = invI + b*12;
	for (j=info[i].m-1; j>=0; j--) {
	  for (k=0; k<3; k++) Jdst[k] = dMUL(Jsrc[k],body_invMass);
	  dMULTIPLY0_133 (Jdst+4,Jsrc+4,body_invI);
	  Jsrc += 8;
	  Jdst += 8;
	}
      }
    }

    // now compute A = JinvM * J'. A's rows and columns are grouped by joint,
    // i.e. in the same way as the rows of J. block (i,j) of A is only nonzero
    // if joints i and j have at least one body in common. this fact suggests
    // the algorithm used to fill A:
    //
    //    for b = all bodies
    //      n = number of joints attached to body b
    //      for i = 1..n
    //        for j = i+1..n
    //          ii = actual joint number for i
    //          jj = actual joint number for j
    //          // (ii,jj) will be set to all pairs of joints around body b
    //          compute blockwise: A(ii,jj) += JinvM(ii) * J(jj)'
    //
    // this algorithm catches all pairs of joints that have at least one body
    // in common. it does not compute the diagonal blocks of A however -
    // another similar algorithm does that.

    int mskip = dPAD(m);
    ALLOCA(dReal,A,m*mskip*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (A == NULL) {
      UNALLOCA(JinvM);
      UNALLOCA(J);
      UNALLOCA(findex);
      UNALLOCA(hi);
      UNALLOCA(lo);
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(cforce);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    dSetZero (A,m*mskip);
    for (i=0; i<nb; i++) {
      for (dxJointNode *n1=body[i]->firstjoint; n1; n1=n1->next) {
	for (dxJointNode *n2=n1->next; n2; n2=n2->next) {
	  // get joint numbers and ensure ofs[j1] >= ofs[j2]
	  int j1 = n1->joint->tag;
	  int j2 = n2->joint->tag;
	  if (ofs[j1] < ofs[j2]) {
	    int tmp = j1;
	    j1 = j2;
	    j2 = tmp;
	  }

	  // if either joint was tagged as -1 then it is an inactive (m=0)
	  // joint that should not be considered
	  if (j1==-1 || j2==-1) continue;

	  // determine if body i is the 1st or 2nd body of joints j1 and j2
	  int jb1 = (joint[j1]->node[1].body == body[i]);
	  int jb2 = (joint[j2]->node[1].body == body[i]);
	  // jb1/jb2 must be 0 for joints with only one body


	  // set block of A
	  MultiplyAdd2_p8r (A + ofs[j1]*mskip + ofs[j2],
			    JinvM + 2*8*ofs[j1] + jb1*8*info[j1].m,
			    J     + 2*8*ofs[j2] + jb2*8*info[j2].m,
			    info[j1].m,info[j2].m, mskip);
	}
      }
    }
    // compute diagonal blocks of A
    for (i=0; i<nj; i++) {
      Multiply2_p8r (A + ofs[i]*(mskip+1),
		     JinvM + 2*8*ofs[i],
		     J + 2*8*ofs[i],
		     info[i].m,info[i].m, mskip);
      if (joint[i]->node[1].body) {
	MultiplyAdd2_p8r (A + ofs[i]*(mskip+1),
			  JinvM + 2*8*ofs[i] + 8*info[i].m,
			  J + 2*8*ofs[i] + 8*info[i].m,
			  info[i].m,info[i].m, mskip);
      }
    }

    // add cfm to the diagonal of A
    for (i=0; i<m; i++) A[i*mskip+i] += dMUL(cfm[i],stepsize1);

    // compute the right hand side `rhs'
    ALLOCA(dReal,tmp1,nb*8*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (tmp1 == NULL) {
      UNALLOCA(A);
      UNALLOCA(JinvM);
      UNALLOCA(J);
      UNALLOCA(findex);
      UNALLOCA(hi);
      UNALLOCA(lo);
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(cforce);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    //dSetZero (tmp1,nb*8);
    // put v/h + invM*fe into tmp1
    for (i=0; i<nb; i++) {
      dReal body_invMass = body[i]->invMass;
      dReal *body_invI = invI + i*12;
      for (j=0; j<3; j++) tmp1[i*8+j] = dMUL(body[i]->facc[j],body_invMass) +
			    dMUL(body[i]->lvel[j],stepsize1);
      dMULTIPLY0_331 (tmp1 + i*8 + 4,body_invI,body[i]->tacc);
      for (j=0; j<3; j++) tmp1[i*8+4+j] += dMUL(body[i]->avel[j],stepsize1);
    }
    // put J*tmp1 into rhs
    ALLOCA(dReal,rhs,m*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (rhs == NULL) {
      UNALLOCA(tmp1);
      UNALLOCA(A);
      UNALLOCA(JinvM);
      UNALLOCA(J);
      UNALLOCA(findex);
      UNALLOCA(hi);
      UNALLOCA(lo);
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(cforce);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    //dSetZero (rhs,m);
    for (i=0; i<nj; i++) {
      dReal *JJ = J + 2*8*ofs[i];
      Multiply0_p81 (rhs+ofs[i],JJ,
		     tmp1 + 8*joint[i]->node[0].body->tag, info[i].m);
      if (joint[i]->node[1].body) {
	MultiplyAdd0_p81 (rhs+ofs[i],JJ + 8*info[i].m,
			  tmp1 + 8*joint[i]->node[1].body->tag, info[i].m);
      }
    }
    // complete rhs
    for (i=0; i<m; i++) rhs[i] = dMUL(c[i],stepsize1) - rhs[i];

    // solve the LCP problem and get lambda.
    // this will destroy A but that's okay
    ALLOCA(dReal,lambda,m*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (lambda == NULL) {
      UNALLOCA(rhs);
      UNALLOCA(tmp1);
      UNALLOCA(A);
      UNALLOCA(JinvM);
      UNALLOCA(J);
      UNALLOCA(findex);
      UNALLOCA(hi);
      UNALLOCA(lo);
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(cforce);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    ALLOCA(dReal,residual,m*sizeof(dReal));
#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (residual == NULL) {
      UNALLOCA(lambda);
      UNALLOCA(rhs);
      UNALLOCA(tmp1);
      UNALLOCA(A);
      UNALLOCA(JinvM);
      UNALLOCA(J);
      UNALLOCA(findex);
      UNALLOCA(hi);
      UNALLOCA(lo);
      UNALLOCA(cfm);
      UNALLOCA(c);
      UNALLOCA(cforce);
      UNALLOCA(ofs);
      UNALLOCA(info);
      UNALLOCA(invI);
      UNALLOCA(I);
      UNALLOCA(joint);
      dMemoryFlag = d_MEMORY_OUT_OF_MEMORY;
      return;
    }
#endif
    dSolveLCP (m,A,lambda,rhs,residual,nub,lo,hi,findex);

#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (dMemoryFlag == d_MEMORY_OUT_OF_MEMORY)
      return;
#endif


//  OLD WAY - direct factor and solve
//
//    // factorize A (L*L'=A)
//#   ifdef TIMING
//    dTimerNow ("factorize A");
//#   endif
//    dReal *L = (dReal*) ALLOCA (m*mskip*sizeof(dReal));
//    memcpy (L,A,m*mskip*sizeof(dReal));
//#   ifdef FAST_FACTOR
//    dFastFactorCholesky (L,m);  // does not report non positive definiteness
//#   else
//    if (dFactorCholesky (L,m)==0) dDebug (0,"A is not positive definite");
//#   endif
//
//    // compute lambda
//#   ifdef TIMING
//    dTimerNow ("compute lambda");
//#   endif
//    dReal *lambda = (dReal*) ALLOCA (m * sizeof(dReal));
//    memcpy (lambda,rhs,m * sizeof(dReal));
//    dSolveCholesky (L,lambda,m);


    // compute the constraint force `cforce'
    // compute cforce = J'*lambda
    for (i=0; i<nj; i++) {
      dReal *JJ = J + 2*8*ofs[i];
      dxBody* b1 = joint[i]->node[0].body;
      dxBody* b2 = joint[i]->node[1].body;
      dJointFeedback *fb = joint[i]->feedback;

      if (fb) {
	// the user has requested feedback on the amount of force that this
	// joint is applying to the bodies. we use a slightly slower
	// computation that splits out the force components and puts them
	// in the feedback structure.
	dReal data1[8],data2[8];
	Multiply1_8q1 (data1, JJ, lambda+ofs[i], info[i].m);
	dReal *cf1 = cforce + 8*b1->tag;
	cf1[0] += (fb->f1[0] = data1[0]);
	cf1[1] += (fb->f1[1] = data1[1]);
	cf1[2] += (fb->f1[2] = data1[2]);
	cf1[4] += (fb->t1[0] = data1[4]);
	cf1[5] += (fb->t1[1] = data1[5]);
	cf1[6] += (fb->t1[2] = data1[6]);
	if (b2){
	  Multiply1_8q1 (data2, JJ + 8*info[i].m, lambda+ofs[i], info[i].m);
	  dReal *cf2 = cforce + 8*b2->tag;
	  cf2[0] += (fb->f2[0] = data2[0]);
	  cf2[1] += (fb->f2[1] = data2[1]);
	  cf2[2] += (fb->f2[2] = data2[2]);
	  cf2[4] += (fb->t2[0] = data2[4]);
	  cf2[5] += (fb->t2[1] = data2[5]);
	  cf2[6] += (fb->t2[2] = data2[6]);
	}
      }
      else {
	// no feedback is required, let's compute cforce the faster way
	MultiplyAdd1_8q1 (cforce + 8*b1->tag,JJ, lambda+ofs[i], info[i].m);
	if (b2) {
	  MultiplyAdd1_8q1 (cforce + 8*b2->tag,
			    JJ + 8*info[i].m, lambda+ofs[i], info[i].m);
	}
      }
    }
    UNALLOCA(c);
    UNALLOCA(cfm);
    UNALLOCA(lo);
    UNALLOCA(hi);
    UNALLOCA(findex);
    UNALLOCA(J);
    UNALLOCA(JinvM);
    UNALLOCA(A);
    UNALLOCA(tmp1);
    UNALLOCA(rhs);
    UNALLOCA(lambda);
    UNALLOCA(residual);
  }

  // compute the velocity update
  // add fe to cforce
  for (i=0; i<nb; i++) {
    for (j=0; j<3; j++) cforce[i*8+j] += body[i]->facc[j];
    for (j=0; j<3; j++) cforce[i*8+4+j] += body[i]->tacc[j];
  }
  // multiply cforce by stepsize
  for (i=0; i < nb*8; i++) cforce[i] = dMUL(cforce[i],stepsize);
  // add invM * cforce to the body velocity
  for (i=0; i<nb; i++) {
    dReal body_invMass = body[i]->invMass;
    dReal *body_invI = invI + i*12;
    for (j=0; j<3; j++) body[i]->lvel[j] += dMUL(body_invMass,cforce[i*8+j]);
    dMULTIPLYADD0_331 (body[i]->avel,body_invI,cforce+i*8+4);
  }

  // update the position and orientation from the new linear/angular velocity
  // (over the given timestep)
  for (i=0; i<nb; i++) dxStepBody (body[i],stepsize);

  // zero all force accumulators
  for (i=0; i<nb; i++) {
    body[i]->facc[0] = 0;
    body[i]->facc[1] = 0;
    body[i]->facc[2] = 0;
    body[i]->facc[3] = 0;
    body[i]->tacc[0] = 0;
    body[i]->tacc[1] = 0;
    body[i]->tacc[2] = 0;
    body[i]->tacc[3] = 0;
  }

  UNALLOCA(joint);
  UNALLOCA(I);
  UNALLOCA(invI);
  UNALLOCA(info);
  UNALLOCA(ofs);
  UNALLOCA(cforce);
}

//****************************************************************************

void dInternalStepIsland (dxWorld *world, dxBody * const *body, int nb,
			  dxJoint * const *joint, int nj, dReal stepsize)
{

#ifdef dUSE_MALLOC_FOR_ALLOCA
  dMemoryFlag = d_MEMORY_OK;
#endif

#ifndef COMPARE_METHODS
  dInternalStepIsland_x2 (world,body,nb,joint,nj,stepsize);

#ifdef dUSE_MALLOC_FOR_ALLOCA
    if (dMemoryFlag == d_MEMORY_OUT_OF_MEMORY) {
      REPORT_OUT_OF_MEMORY;
      return;
    }
#endif

#endif

}


