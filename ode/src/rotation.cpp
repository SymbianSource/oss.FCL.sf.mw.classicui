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

/*

quaternions have the format: (s,vx,vy,vz) where (vx,vy,vz) is the
"rotation axis" and s is the "rotation angle".

*/

#include <ode/rotation.h>
#include <ode/odemath.h>

#include <ode/lookup_tables.h>


#define _R(i,j) R[(i)*4+(j)]

#define SET_3x3_IDENTITY \
  _R(0,0) = REAL(1.0); \
  _R(0,1) = REAL(0.0); \
  _R(0,2) = REAL(0.0); \
  _R(0,3) = REAL(0.0); \
  _R(1,0) = REAL(0.0); \
  _R(1,1) = REAL(1.0); \
  _R(1,2) = REAL(0.0); \
  _R(1,3) = REAL(0.0); \
  _R(2,0) = REAL(0.0); \
  _R(2,1) = REAL(0.0); \
  _R(2,2) = REAL(1.0); \
  _R(2,3) = REAL(0.0);


EXPORT_C void dRSetIdentity (dMatrix3 R)
{
  SET_3x3_IDENTITY;
}


EXPORT_C void dRFromAxisAndAngle (dMatrix3 R, dReal ax, dReal ay, dReal az,
			 dReal angle)
{
  dQuaternion q;
  dQFromAxisAndAngle (q,ax,ay,az,angle);
  dQtoR (q,R);
}


EXPORT_C void dRFromEulerAngles (dMatrix3 R, dReal phi, dReal theta, dReal psi)
{
  dReal sphi,cphi,stheta,ctheta,spsi,cpsi;

  sphi = dSin(phi);
  cphi = dCos(phi);
  stheta = dSin(theta);
  ctheta = dCos(theta);
  spsi = dSin(psi);
  cpsi = dCos(psi);
  _R(0,0) = dMUL(cpsi,ctheta);
  _R(0,1) = dMUL(spsi,ctheta);
  _R(0,2) =-stheta;
  _R(0,3) = REAL(0.0);
  _R(1,0) = dMUL(cpsi,dMUL(stheta,sphi)) - dMUL(spsi,cphi);
  _R(1,1) = dMUL(spsi,dMUL(stheta,sphi)) + dMUL(cpsi,cphi);
  _R(1,2) = dMUL(ctheta,sphi);
  _R(1,3) = REAL(0.0);
  _R(2,0) = dMUL(cpsi,dMUL(stheta,cphi)) + dMUL(spsi,sphi);
  _R(2,1) = dMUL(spsi,dMUL(stheta,cphi)) - dMUL(cpsi,sphi);
  _R(2,2) = dMUL(ctheta,cphi);
  _R(2,3) = REAL(0.0);
}


EXPORT_C void dRFrom2Axes (dMatrix3 R, dReal ax, dReal ay, dReal az,
		  dReal bx, dReal by, dReal bz)
{
  dReal l,k;

  l = dSqrt (dMUL(ax,ax) + dMUL(ay,ay) + dMUL(az,az));
  if (l <= REAL(0.0)) {
    return;
  }
  l = dRecip(l);
  ax = dMUL(ax,l);
  ay = dMUL(ay,l);
  az = dMUL(az,l);
  k = dMUL(ax,bx) + dMUL(ay,by) + dMUL(az,bz);
  bx -= dMUL(k,ax);
  by -= dMUL(k,ay);
  bz -= dMUL(k,az);
  l = dSqrt (dMUL(bx,bx) + dMUL(by,by) + dMUL(bz,bz));
  if (l <= REAL(0.0)) {
    return;
  }
  l = dRecip(l);
  bx = dMUL(bx,l);
  by = dMUL(by,l);
  bz = dMUL(bz,l);
  _R(0,0) = ax;
  _R(1,0) = ay;
  _R(2,0) = az;
  _R(0,1) = bx;
  _R(1,1) = by;
  _R(2,1) = bz;
  _R(0,2) = - dMUL(by,az) + dMUL(ay,bz);
  _R(1,2) = - dMUL(bz,ax) + dMUL(az,bx);
  _R(2,2) = - dMUL(bx,ay) + dMUL(ax,by);
  _R(0,3) = REAL(0.0);
  _R(1,3) = REAL(0.0);
  _R(2,3) = REAL(0.0);
}


EXPORT_C void dRFromZAxis (dMatrix3 R, dReal ax, dReal ay, dReal az)
{
  dVector3 n,p,q;
  n[0] = ax;
  n[1] = ay;
  n[2] = az;
  dNormalize3 (n);
  dPlaneSpace (n,p,q);
  _R(0,0) = p[0];
  _R(1,0) = p[1];
  _R(2,0) = p[2];
  _R(0,1) = q[0];
  _R(1,1) = q[1];
  _R(2,1) = q[2];
  _R(0,2) = n[0];
  _R(1,2) = n[1];
  _R(2,2) = n[2];
  _R(0,3) = REAL(0.0);
  _R(1,3) = REAL(0.0);
  _R(2,3) = REAL(0.0);
}


EXPORT_C void dQSetIdentity (dQuaternion q)
{
  q[0] = REAL(1.0);
  q[1] = 0;
  q[2] = 0;
  q[3] = 0;
}


EXPORT_C void dQFromAxisAndAngle (dQuaternion q, dReal ax, dReal ay, dReal az,
			 dReal angle)
{
  dReal l = dMUL(ax,ax) + dMUL(ay,ay) + dMUL(az,az);
  if (l > REAL(0.0)) {
    angle = dMUL(angle,REAL(0.5));
    q[0] = dCos (angle);
    l = dMUL(dReal(dSin(angle)),dRecipSqrt(l));
    q[1] = dMUL(ax,l);
    q[2] = dMUL(ay,l);
    q[3] = dMUL(az,l);
  }
  else {
    q[0] = REAL(1.0);
    q[1] = 0;
    q[2] = 0;
    q[3] = 0;
  }
}


EXPORT_C void dQMultiply0 (dQuaternion qa, const dQuaternion qb, const dQuaternion qc)
{
  qa[0] = dMUL(qb[0],qc[0]) - dMUL(qb[1],qc[1]) - dMUL(qb[2],qc[2]) - dMUL(qb[3],qc[3]);
  qa[1] = dMUL(qb[0],qc[1]) + dMUL(qb[1],qc[0]) + dMUL(qb[2],qc[3]) - dMUL(qb[3],qc[2]);
  qa[2] = dMUL(qb[0],qc[2]) + dMUL(qb[2],qc[0]) + dMUL(qb[3],qc[1]) - dMUL(qb[1],qc[3]);
  qa[3] = dMUL(qb[0],qc[3]) + dMUL(qb[3],qc[0]) + dMUL(qb[1],qc[2]) - dMUL(qb[2],qc[1]);
}


EXPORT_C void dQMultiply1 (dQuaternion qa, const dQuaternion qb, const dQuaternion qc)
{
  qa[0] = dMUL(qb[0],qc[0]) + dMUL(qb[1],qc[1]) + dMUL(qb[2],qc[2]) + dMUL(qb[3],qc[3]);
  qa[1] = dMUL(qb[0],qc[1]) - dMUL(qb[1],qc[0]) - dMUL(qb[2],qc[3]) + dMUL(qb[3],qc[2]);
  qa[2] = dMUL(qb[0],qc[2]) - dMUL(qb[2],qc[0]) - dMUL(qb[3],qc[1]) + dMUL(qb[1],qc[3]);
  qa[3] = dMUL(qb[0],qc[3]) - dMUL(qb[3],qc[0]) - dMUL(qb[1],qc[2]) + dMUL(qb[2],qc[1]);
}


EXPORT_C void dQMultiply2 (dQuaternion qa, const dQuaternion qb, const dQuaternion qc)
{
  qa[0] =  dMUL(qb[0],qc[0]) + dMUL(qb[1],qc[1]) + dMUL(qb[2],qc[2]) + dMUL(qb[3],qc[3]);
  qa[1] = -dMUL(qb[0],qc[1]) + dMUL(qb[1],qc[0]) - dMUL(qb[2],qc[3]) + dMUL(qb[3],qc[2]);
  qa[2] = -dMUL(qb[0],qc[2]) + dMUL(qb[2],qc[0]) - dMUL(qb[3],qc[1]) + dMUL(qb[1],qc[3]);
  qa[3] = -dMUL(qb[0],qc[3]) + dMUL(qb[3],qc[0]) - dMUL(qb[1],qc[2]) + dMUL(qb[2],qc[1]);
}


EXPORT_C void dQMultiply3 (dQuaternion qa, const dQuaternion qb, const dQuaternion qc)
{
  qa[0] =  dMUL(qb[0],qc[0]) - dMUL(qb[1],qc[1]) - dMUL(qb[2],qc[2]) - dMUL(qb[3],qc[3]);
  qa[1] = -dMUL(qb[0],qc[1]) - dMUL(qb[1],qc[0]) + dMUL(qb[2],qc[3]) - dMUL(qb[3],qc[2]);
  qa[2] = -dMUL(qb[0],qc[2]) - dMUL(qb[2],qc[0]) + dMUL(qb[3],qc[1]) - dMUL(qb[1],qc[3]);
  qa[3] = -dMUL(qb[0],qc[3]) - dMUL(qb[3],qc[0]) + dMUL(qb[1],qc[2]) - dMUL(qb[2],qc[1]);
}


// dRfromQ(), dQfromR() and dDQfromW() are derived from equations in "An Introduction
// to Physically Based Modeling: Rigid Body Simulation - 1: Unconstrained
// Rigid Body Dynamics" by David Baraff, Robotics Institute, Carnegie Mellon
// University, 1997.

EXPORT_C void dRfromQ (dMatrix3 R, const dQuaternion q)
{

  // q = (s,vx,vy,vz)
  dReal qq1 = 2*dMUL(q[1],q[1]);
  dReal qq2 = 2*dMUL(q[2],q[2]);
  dReal qq3 = 2*dMUL(q[3],q[3]);
  _R(0,0) = REAL(1.0) - qq2 - qq3;
  _R(0,1) = 2*(dMUL(q[1],q[2]) - dMUL(q[0],q[3]));
  _R(0,2) = 2*(dMUL(q[1],q[3]) + dMUL(q[0],q[2]));
  _R(0,3) = REAL(0.0);
  _R(1,0) = 2*(dMUL(q[1],q[2]) + dMUL(q[0],q[3]));
  _R(1,1) = REAL(1.0) - qq1 - qq3;
  _R(1,2) = 2*(dMUL(q[2],q[3]) - dMUL(q[0],q[1]));
  _R(1,3) = REAL(0.0);
  _R(2,0) = 2*(dMUL(q[1],q[3]) - dMUL(q[0],q[2]));
  _R(2,1) = 2*(dMUL(q[2],q[3]) + dMUL(q[0],q[1]));
  _R(2,2) = REAL(1.0) - qq1 - qq2;
  _R(2,3) = REAL(0.0);
}


EXPORT_C void dQfromR (dQuaternion q, const dMatrix3 R)
{

  dReal tr,s;
  tr = _R(0,0) + _R(1,1) + _R(2,2);
  if (tr >= 0) {
    s = dSqrt (tr + REAL(1.0));
    q[0] = dMUL(REAL(0.5),s);
    s = dMUL(REAL(0.5),dRecip(s));
    q[1] = dMUL((_R(2,1) - _R(1,2)),s);
    q[2] = dMUL((_R(0,2) - _R(2,0)),s);
    q[3] = dMUL((_R(1,0) - _R(0,1)),s);
  }
  else {
    // find the largest diagonal element and jump to the appropriate case
    if (_R(1,1) > _R(0,0)) {
      if (_R(2,2) > _R(1,1)) goto case_2;
      goto case_1;
    }
    if (_R(2,2) > _R(0,0)) goto case_2;
    goto case_0;

    case_0:
    s = dSqrt((_R(0,0) - (_R(1,1) + _R(2,2))) + REAL(1.0));
    q[1] = dMUL(REAL(0.5),s);
    s = dMUL(REAL(0.5),dRecip(s));
    q[2] = dMUL((_R(0,1) + _R(1,0)),s);
    q[3] = dMUL((_R(2,0) + _R(0,2)),s);
    q[0] = dMUL((_R(2,1) - _R(1,2)),s);
    return;

    case_1:
    s = dSqrt((_R(1,1) - (_R(2,2) + _R(0,0))) + REAL(1.0));
    q[2] = dMUL(REAL(0.5),s);
    s = dMUL(REAL(0.5),dRecip(s));
    q[3] = dMUL((_R(1,2) + _R(2,1)),s);
    q[1] = dMUL((_R(0,1) + _R(1,0)),s);
    q[0] = dMUL((_R(0,2) - _R(2,0)),s);
    return;

    case_2:
    s = dSqrt((_R(2,2) - (_R(0,0) + _R(1,1))) + REAL(1.0));
    q[3] = dMUL(REAL(0.5),s);
    s = dMUL(REAL(0.5),dRecip(s));
    q[1] = dMUL((_R(2,0) + _R(0,2)),s);
    q[2] = dMUL((_R(1,2) + _R(2,1)),s);
    q[0] = dMUL((_R(1,0) - _R(0,1)),s);
    return;
  }
}


EXPORT_C void dDQfromW (dReal dq[4], const dVector3 w, const dQuaternion q)
{

  dq[0] = dMUL(REAL(0.5),(- dMUL(w[0],q[1]) - dMUL(w[1],q[2]) - dMUL(w[2],q[3])));
  dq[1] = dMUL(REAL(0.5),(  dMUL(w[0],q[0]) + dMUL(w[1],q[3]) - dMUL(w[2],q[2])));
  dq[2] = dMUL(REAL(0.5),(- dMUL(w[0],q[3]) + dMUL(w[1],q[0]) + dMUL(w[2],q[1])));
  dq[3] = dMUL(REAL(0.5),(  dMUL(w[0],q[2]) - dMUL(w[1],q[1]) + dMUL(w[2],q[0])));
}
