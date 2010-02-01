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

#include <ode/common.h>
#include <ode/odemath.h>


// this may be called for vectors `a' with extremely small magnitude, for
// example the result of a cross product on two nearly perpendicular vectors.
// we must be robust to these small vectors. to prevent numerical error,
// first find the component a[i] with the largest magnitude and then scale
// all the components by 1/a[i]. then we can compute the length of `a' and
// scale the components by 1/l. this has been verified to work with vectors
// containing the smallest representable numbers.

EXPORT_C void dNormalize3 (dVector3 a)
{
  dReal a0,a1,a2,aa0,aa1,aa2,l;
  a0 = a[0];
  a1 = a[1];
  a2 = a[2];
  aa0 = dFabs(a0);
  aa1 = dFabs(a1);
  aa2 = dFabs(a2);
  if (aa1 > aa0) {
    if (aa2 > aa1) {
      goto aa2_largest;
    }
    else {		// aa1 is largest
      a0 = dDIV(a0,aa1);
      a2 = dDIV(a2,aa1);
      l = dRecipSqrt (dMUL(a0,a0) + dMUL(a2,a2) + REAL(1.0));
      a[0] = dMUL(a0,l);
      a[1] = dCopySign(l,a1);
      a[2] = dMUL(a2,l);
    }
  }
  else {
    if (aa2 > aa0) {
      aa2_largest:	// aa2 is largest
      a0 = dDIV(a0,aa2);
      a1 = dDIV(a1,aa2);
      l = dRecipSqrt (dMUL(a0,a0) + dMUL(a1,a1) + REAL(1.0));
      a[0] = dMUL(a0,l);
      a[1] = dMUL(a1,l);
      a[2] = dCopySign(l,a2);
    }
    else {		// aa0 is largest
      if (aa0 <= 0) {
	a[0] = REAL(1.0);	// if all a's are zero, this is where we'll end up.
	a[1] = 0;	// return a default unit length vector.
	a[2] = 0;
	return;
      }
      a1 = dDIV(a1,aa0);
      a2 = dDIV(a2,aa0);
      l = dRecipSqrt (dMUL(a1,a1) + dMUL(a2,a2) + REAL(1.0));
      a[0] = dCopySign(l,a0);
      a[1] = dMUL(a1,l);
      a[2] = dMUL(a2,l);
    }
  }
}


/* OLD VERSION */
/*
void dNormalize3 (dVector3 a)
{

  dReal l = dDOT(a,a);
  if (l > 0) {
    l = dRecipSqrt(l);
    a[0] *= l;
    a[1] *= l;
    a[2] *= l;
  }
  else {
    a[0] = 1;
    a[1] = 0;
    a[2] = 0;
  }
}
*/


EXPORT_C void dNormalize4 (dVector4 a)
{

  dReal l = dDOT(a,a)+dMUL(a[3],a[3]);
  if (l > 0) {
    l = dRecipSqrt(l);
    a[0] = dMUL(a[0],l);
    a[1] = dMUL(a[1],l);
    a[2] = dMUL(a[2],l);
    a[3] = dMUL(a[3],l);
  }
  else {
    a[0] = REAL(1.0);
    a[1] = 0;
    a[2] = 0;
    a[3] = 0;
  }
}


EXPORT_C void dPlaneSpace (const dVector3 n, dVector3 p, dVector3 q)
{
  if (dFabs(n[2]) > dSQRT1_2) {
    // choose p in y-z plane
    dReal a = dMUL(n[1],n[1]) + dMUL(n[2],n[2]);
    dReal k = dRecipSqrt (a);
    p[0] = 0;
    p[1] = -dMUL(n[2],k);
    p[2] = dMUL(n[1],k);
    // set q = n x p
    q[0] = dMUL(a,k);
    q[1] = -dMUL(n[0],p[2]);
    q[2] = dMUL(n[0],p[1]);
  }
  else {
    // choose p in x-y plane
    dReal a = dMUL(n[0],n[0]) + dMUL(n[1],n[1]);
    dReal k = dRecipSqrt (a);
    p[0] = -dMUL(n[1],k);
    p[1] = dMUL(n[0],k);
    p[2] = 0;
    // set q = n x p
    q[0] = -dMUL(n[2],p[1]);
    q[1] = dMUL(n[2],p[0]);
    q[2] = dMUL(a,k);
  }
}

EXPORT_C dReal dArcTan2(const dReal y, const dReal x)
{
	dReal coeff_1 = dPI/4;
  	dReal coeff_2 = 3*coeff_1;
	dReal abs_y = dFabs(y) + dEpsilon;      // kludge to prevent 0/0 condition
	dReal angle;
   if (x>=0)
   {
      dReal r = dDIV((x - abs_y),(x + abs_y));
      //angle = coeff_1 - dMUL(coeff_1,r);
      angle = dMUL(REAL(0.1963),dMUL(r,dMUL(r,r))) - dMUL(REAL(0.9817),r) + coeff_1;
   }
   else
   {
      dReal r = dDIV((x + abs_y),(abs_y - x));
      //angle = coeff_2 - dMUL(coeff_1,r);
      angle = dMUL(REAL(0.1963),dMUL(r,dMUL(r,r))) - dMUL(REAL(0.9817),r) + coeff_2;
   }
   if (y < 0)
   return(-angle);     // negate if in quad III or IV
   else
   return(angle);
}

EXPORT_C dReal dArcSin(dReal arg)
{
	dReal temp;
	int sign;

	sign = 0;
	if(arg < 0)
	{
		arg = -arg;
		sign++;
	}
	if(arg > REAL(1.0)) {
		arg = REAL(1.0);
		//return dInfinity;
	}
	temp = dSqrt(REAL(1.0) - dMUL(arg,arg));
	if(arg > REAL(0.7))
		temp = dPI/2 - dArcTan2(temp,arg);
	else
		temp = dArcTan2(arg,temp);
	if(sign > 0)
		temp = -temp;
	return temp;
}

