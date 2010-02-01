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

// this source file is mostly concerned with the data structures, not the
// numerics.

#include <e32std.h>
#include <pls.h>
#include "object.h"
#include <ode/ode.h>
#include "joint.h"
#include <ode/odemath.h>
#include <ode/matrix.h>
#include "step.h"
#include "quickstep.h"
#include "util.h"
#include <ode/memory.h>
#include <ode/error.h>

#ifdef __WINSCW__

TInt InitializeGlobaData( TOdeStaticData* aData )
    {
    Mem::FillZ( aData, sizeof( TOdeStaticData ) );
    aData->autoEnableDepth = 2;
    return KErrNone;
    }
    
struct TOdeStaticData* GetGlobalData()
    {
    return Pls<TOdeStaticData>( TUid::Uid( 0x2001CBE3 ), InitializeGlobaData );
    }

#else

static struct TOdeStaticData odeStaticData;

struct TOdeStaticData* GetGlobalData()
    {
    return &odeStaticData;
    }

#endif // __WINSCW__

// misc defines
//#define ALLOCA dALLOCA16

//****************************************************************************
// utility

static inline void initObject (dObject *obj, dxWorld *w)
{
  obj->world = w;
  obj->next = 0;
  obj->tome = 0;
  obj->userdata = 0;
  obj->tag = 0;
}


// add an object `obj' to the list who's head pointer is pointed to by `first'.

static inline void addObjectToList (dObject *obj, dObject **first)
{
  obj->next = *first;
  obj->tome = first;
  if (*first) (*first)->tome = &obj->next;
  (*first) = obj;
}


// remove the object from the linked list

static inline void removeObjectFromList (dObject *obj)
{
  if (obj->next) obj->next->tome = obj->tome;
  *(obj->tome) = obj->next;
  // safeguard
  obj->next = 0;
  obj->tome = 0;
}


// remove the joint from neighbour lists of all connected bodies

static void removeJointReferencesFromAttachedBodies (dxJoint *j)
{
  for (int i=0; i<2; i++) {
    dxBody *body = j->node[i].body;
    if (body) {
      dxJointNode *n = body->firstjoint;
      dxJointNode *last = 0;
      while (n) {
	if (n->joint == j) {
	  if (last) last->next = n->next;
	  else body->firstjoint = n->next;
	  break;
	}
	last = n;
	n = n->next;
      }
    }
  }
  j->node[0].body = 0;
  j->node[0].next = 0;
  j->node[1].body = 0;
  j->node[1].next = 0;
}

//****************************************************************************
// debugging


// check the validity of the world data structures

static void checkWorld (dxWorld */*w*/)
{
  //dxBody *b;
  //dxJoint *j;

 // TBD

}


void dWorldCheck (dxWorld *w)
{
  checkWorld (w);
}

//****************************************************************************
// body
EXPORT_C dxWorld* dBodyGetWorld (dxBody* b)
{

  return b->world;
}

EXPORT_C dxBody *dBodyCreate (dxWorld *w)
{

  dxBody *b = new dxBody;
  initObject (b,w);
  b->firstjoint = 0;
  b->flags = 0;
  b->geom = 0;
  b->average_lvel_buffer = 0;
  b->average_avel_buffer = 0;
  dMassSetParameters (&b->mass,REAL(1.0),0,0,0,REAL(1.0),REAL(1.0),REAL(1.0),0,0,0);
  dSetZero (b->invI,4*3);
  b->invI[0] = REAL(1.0);
  b->invI[5] = REAL(1.0);
  b->invI[10] = REAL(1.0);
  b->invMass = REAL(1.0);
  dSetZero (b->posr.pos,4);
  dSetZero (b->q,4);
  b->q[0] = REAL(1.0);
  dRSetIdentity (b->posr.R);
  dSetZero (b->lvel,4);
  dSetZero (b->avel,4);
  dSetZero (b->facc,4);
  dSetZero (b->tacc,4);
  dSetZero (b->finite_rot_axis,4);
  addObjectToList (b,(dObject **) &w->firstbody);
  w->nb++;

  // set auto-disable parameters
  b->average_avel_buffer = b->average_lvel_buffer = 0; // no buffer at beginnin
  dBodySetAutoDisableDefaults (b);	// must do this after adding to world
  b->adis_stepsleft = b->adis.idle_steps;
  b->adis_timeleft = b->adis.idle_time;
  b->average_counter = 0;
  b->average_ready = 0; // average buffer not filled on the beginning
  dBodySetAutoDisableAverageSamplesCount(b, b->adis.average_samples);

  return b;
}


EXPORT_C void dBodyDestroy (dxBody *b)
{


  // all geoms that link to this body must be notified that the body is about
  // to disappear. note that the call to dGeomSetBody(geom,0) will result in
  // dGeomGetBodyNext() returning 0 for the body, so we must get the next body
  // before setting the body to 0.
  dxGeom *next_geom = 0;
  for (dxGeom *geom = b->geom; geom; geom = next_geom) {
    next_geom = dGeomGetBodyNext (geom);
    dGeomSetBody (geom,0);
  }

  // detach all neighbouring joints, then delete this body.
  dxJointNode *n = b->firstjoint;
  while (n) {
    // sneaky trick to speed up removal of joint references (black magic)
    n->joint->node[(n == n->joint->node)].body = 0;

    dxJointNode *next = n->next;
    n->next = 0;
    removeJointReferencesFromAttachedBodies (n->joint);
    n = next;
  }
  removeObjectFromList (b);
  b->world->nb--;

  // delete the average buffers
  if(b->average_lvel_buffer)
  {
	  delete[] (b->average_lvel_buffer);
	  b->average_lvel_buffer = 0;
  }
  if(b->average_avel_buffer)
  {
	  delete[] (b->average_avel_buffer);
	  b->average_avel_buffer = 0;
  }

  delete b;
}


EXPORT_C void dBodySetData (dBodyID b, void *data)
{
  b->userdata = data;
}


EXPORT_C void *dBodyGetData (dBodyID b)
{
  return b->userdata;
}


EXPORT_C void dBodySetPosition (dBodyID b, dReal x, dReal y, dReal z)
{

  b->posr.pos[0] = x;
  b->posr.pos[1] = y;
  b->posr.pos[2] = z;

  // notify all attached geoms that this body has moved
  for (dxGeom *geom = b->geom; geom; geom = dGeomGetBodyNext (geom))
    dGeomMoved (geom);
}


EXPORT_C void dBodySetRotation (dBodyID b, const dMatrix3 R)
{
  dQuaternion q;
  dRtoQ (R,q);
  dNormalize4 (q);
  b->q[0] = q[0];
  b->q[1] = q[1];
  b->q[2] = q[2];
  b->q[3] = q[3];
  dQtoR (b->q,b->posr.R);

  // notify all attached geoms that this body has moved
  for (dxGeom *geom = b->geom; geom; geom = dGeomGetBodyNext (geom))
    dGeomMoved (geom);
}


EXPORT_C void dBodySetQuaternion (dBodyID b, const dQuaternion q)
{

  b->q[0] = q[0];
  b->q[1] = q[1];
  b->q[2] = q[2];
  b->q[3] = q[3];
  dNormalize4 (b->q);
  dQtoR (b->q,b->posr.R);

  // notify all attached geoms that this body has moved
  for (dxGeom *geom = b->geom; geom; geom = dGeomGetBodyNext (geom))
    dGeomMoved (geom);
}


EXPORT_C void dBodySetLinearVel  (dBodyID b, dReal x, dReal y, dReal z)
{
  b->lvel[0] = x;
  b->lvel[1] = y;
  b->lvel[2] = z;
}


EXPORT_C void dBodySetAngularVel (dBodyID b, dReal x, dReal y, dReal z)
{
  b->avel[0] = x;
  b->avel[1] = y;
  b->avel[2] = z;
}


EXPORT_C const dReal * dBodyGetPosition (dBodyID b)
{
  return b->posr.pos;
}


EXPORT_C void dBodyCopyPosition (dBodyID b, dVector3 pos)
{
	dReal* src = b->posr.pos;
	pos[0] = src[0];
	pos[1] = src[1];
	pos[2] = src[2];
}


EXPORT_C const dReal * dBodyGetRotation (dBodyID b)
{
  return b->posr.R;
}


EXPORT_C void dBodyCopyRotation (dBodyID b, dMatrix3 R)
{
	const dReal* src = b->posr.R;
	R[0] = src[0];
	R[1] = src[1];
	R[2] = src[2];
	R[3] = src[3];
	R[4] = src[4];
	R[5] = src[5];
	R[6] = src[6];
	R[7] = src[7];
	R[8] = src[8];
	R[9] = src[9];
	R[10] = src[10];
	R[11] = src[11];
}


EXPORT_C const dReal * dBodyGetQuaternion (dBodyID b)
{
  return b->q;
}


EXPORT_C void dBodyCopyQuaternion (dBodyID b, dQuaternion quat)
{
	dReal* src = b->q;
	quat[0] = src[0];
	quat[1] = src[1];
	quat[2] = src[2];
	quat[3] = src[3];
}


EXPORT_C const dReal * dBodyGetLinearVel (dBodyID b)
{
  return b->lvel;
}


EXPORT_C const dReal * dBodyGetAngularVel (dBodyID b)
{
  return b->avel;
}


EXPORT_C void dBodySetMass (dBodyID b, const dMass *mass)
{
  // The centre of mass must be at the origin.
  // Use dMassTranslate( mass, -mass->c[0], -mass->c[1], -mass->c[2] ) to correct it.

  memcpy (&b->mass,mass,sizeof(dMass));
  if (dInvertPDMatrix (b->mass.I,b->invI,3)==0) {
    dRSetIdentity (b->invI);
  }
  b->invMass = dRecip(b->mass.mass);
}


EXPORT_C void dBodyGetMass (dBodyID b, dMass *mass)
{
  memcpy (mass,&b->mass,sizeof(dMass));
}


EXPORT_C void dBodyAddForce (dBodyID b, dReal fx, dReal fy, dReal fz)
{
  b->facc[0] += fx;
  b->facc[1] += fy;
  b->facc[2] += fz;
}


EXPORT_C void dBodyAddTorque (dBodyID b, dReal fx, dReal fy, dReal fz)
{
  b->tacc[0] += fx;
  b->tacc[1] += fy;
  b->tacc[2] += fz;
}


EXPORT_C void dBodyAddRelForce (dBodyID b, dReal fx, dReal fy, dReal fz)
{
  dVector3 t1,t2;
  t1[0] = fx;
  t1[1] = fy;
  t1[2] = fz;
  t1[3] = 0;
  dMULTIPLY0_331 (t2,b->posr.R,t1);
  b->facc[0] += t2[0];
  b->facc[1] += t2[1];
  b->facc[2] += t2[2];
}


EXPORT_C void dBodyAddRelTorque (dBodyID b, dReal fx, dReal fy, dReal fz)
{
  dVector3 t1,t2;
  t1[0] = fx;
  t1[1] = fy;
  t1[2] = fz;
  t1[3] = 0;
  dMULTIPLY0_331 (t2,b->posr.R,t1);
  b->tacc[0] += t2[0];
  b->tacc[1] += t2[1];
  b->tacc[2] += t2[2];
}


EXPORT_C void dBodyAddForceAtPos (dBodyID b, dReal fx, dReal fy, dReal fz,
			 dReal px, dReal py, dReal pz)
{
  b->facc[0] += fx;
  b->facc[1] += fy;
  b->facc[2] += fz;
  dVector3 f,q;
  f[0] = fx;
  f[1] = fy;
  f[2] = fz;
  q[0] = px - b->posr.pos[0];
  q[1] = py - b->posr.pos[1];
  q[2] = pz - b->posr.pos[2];
  dCROSS (b->tacc,+=,q,f);
}


EXPORT_C void dBodyAddForceAtRelPos (dBodyID b, dReal fx, dReal fy, dReal fz,
			    dReal px, dReal py, dReal pz)
{
  dVector3 prel,f,p;
  f[0] = fx;
  f[1] = fy;
  f[2] = fz;
  f[3] = 0;
  prel[0] = px;
  prel[1] = py;
  prel[2] = pz;
  prel[3] = 0;
  dMULTIPLY0_331 (p,b->posr.R,prel);
  b->facc[0] += f[0];
  b->facc[1] += f[1];
  b->facc[2] += f[2];
  dCROSS (b->tacc,+=,p,f);
}


EXPORT_C void dBodyAddRelForceAtPos (dBodyID b, dReal fx, dReal fy, dReal fz,
			    dReal px, dReal py, dReal pz)
{
  dVector3 frel,f;
  frel[0] = fx;
  frel[1] = fy;
  frel[2] = fz;
  frel[3] = 0;
  dMULTIPLY0_331 (f,b->posr.R,frel);
  b->facc[0] += f[0];
  b->facc[1] += f[1];
  b->facc[2] += f[2];
  dVector3 q;
  q[0] = px - b->posr.pos[0];
  q[1] = py - b->posr.pos[1];
  q[2] = pz - b->posr.pos[2];
  dCROSS (b->tacc,+=,q,f);
}


EXPORT_C void dBodyAddRelForceAtRelPos (dBodyID b, dReal fx, dReal fy, dReal fz,
			       dReal px, dReal py, dReal pz)
{
  dVector3 frel,prel,f,p;
  frel[0] = fx;
  frel[1] = fy;
  frel[2] = fz;
  frel[3] = 0;
  prel[0] = px;
  prel[1] = py;
  prel[2] = pz;
  prel[3] = 0;
  dMULTIPLY0_331 (f,b->posr.R,frel);
  dMULTIPLY0_331 (p,b->posr.R,prel);
  b->facc[0] += f[0];
  b->facc[1] += f[1];
  b->facc[2] += f[2];
  dCROSS (b->tacc,+=,p,f);
}


EXPORT_C const dReal * dBodyGetForce (dBodyID b)
{
  return b->facc;
}


EXPORT_C const dReal * dBodyGetTorque (dBodyID b)
{
  return b->tacc;
}


EXPORT_C void dBodySetForce (dBodyID b, dReal x, dReal y, dReal z)
{
  b->facc[0] = x;
  b->facc[1] = y;
  b->facc[2] = z;
}


EXPORT_C void dBodySetTorque (dBodyID b, dReal x, dReal y, dReal z)
{
  b->tacc[0] = x;
  b->tacc[1] = y;
  b->tacc[2] = z;
}


EXPORT_C void dBodyGetRelPointPos (dBodyID b, dReal px, dReal py, dReal pz,
			  dVector3 result)
{
  dVector3 prel,p;
  prel[0] = px;
  prel[1] = py;
  prel[2] = pz;
  prel[3] = 0;
  dMULTIPLY0_331 (p,b->posr.R,prel);
  result[0] = p[0] + b->posr.pos[0];
  result[1] = p[1] + b->posr.pos[1];
  result[2] = p[2] + b->posr.pos[2];
}


EXPORT_C void dBodyGetRelPointVel (dBodyID b, dReal px, dReal py, dReal pz,
			  dVector3 result)
{
  dVector3 prel,p;
  prel[0] = px;
  prel[1] = py;
  prel[2] = pz;
  prel[3] = 0;
  dMULTIPLY0_331 (p,b->posr.R,prel);
  result[0] = b->lvel[0];
  result[1] = b->lvel[1];
  result[2] = b->lvel[2];
  dCROSS (result,+=,b->avel,p);
}


EXPORT_C void dBodyGetPointVel (dBodyID b, dReal px, dReal py, dReal pz,
		       dVector3 result)
{
  dVector3 p;
  p[0] = px - b->posr.pos[0];
  p[1] = py - b->posr.pos[1];
  p[2] = pz - b->posr.pos[2];
  p[3] = 0;
  result[0] = b->lvel[0];
  result[1] = b->lvel[1];
  result[2] = b->lvel[2];
  dCROSS (result,+=,b->avel,p);
}


EXPORT_C void dBodyGetPosRelPoint (dBodyID b, dReal px, dReal py, dReal pz,
			  dVector3 result)
{
  dVector3 prel;
  prel[0] = px - b->posr.pos[0];
  prel[1] = py - b->posr.pos[1];
  prel[2] = pz - b->posr.pos[2];
  prel[3] = 0;
  dMULTIPLY1_331 (result,b->posr.R,prel);
}


EXPORT_C void dBodyVectorToWorld (dBodyID b, dReal px, dReal py, dReal pz,
			 dVector3 result)
{
  dVector3 p;
  p[0] = px;
  p[1] = py;
  p[2] = pz;
  p[3] = 0;
  dMULTIPLY0_331 (result,b->posr.R,p);
}


EXPORT_C void dBodyVectorFromWorld (dBodyID b, dReal px, dReal py, dReal pz,
			   dVector3 result)
{
  dVector3 p;
  p[0] = px;
  p[1] = py;
  p[2] = pz;
  p[3] = 0;
  dMULTIPLY1_331 (result,b->posr.R,p);
}


EXPORT_C void dBodySetFiniteRotationMode (dBodyID b, int mode)
{
  b->flags &= ~(dxBodyFlagFiniteRotation | dxBodyFlagFiniteRotationAxis);
  if (mode) {
    b->flags |= dxBodyFlagFiniteRotation;
    if (b->finite_rot_axis[0] != 0 || b->finite_rot_axis[1] != 0 ||
	b->finite_rot_axis[2] != 0) {
      b->flags |= dxBodyFlagFiniteRotationAxis;
    }
  }
}


EXPORT_C void dBodySetFiniteRotationAxis (dBodyID b, dReal x, dReal y, dReal z)
{
  b->finite_rot_axis[0] = x;
  b->finite_rot_axis[1] = y;
  b->finite_rot_axis[2] = z;
  if (x != 0 || y != 0 || z != 0) {
    dNormalize3 (b->finite_rot_axis);
    b->flags |= dxBodyFlagFiniteRotationAxis;
  }
  else {
    b->flags &= ~dxBodyFlagFiniteRotationAxis;
  }
}


EXPORT_C int dBodyGetFiniteRotationMode (dBodyID b)
{
  return ((b->flags & dxBodyFlagFiniteRotation) != 0);
}


EXPORT_C void dBodyGetFiniteRotationAxis (dBodyID b, dVector3 result)
{
  result[0] = b->finite_rot_axis[0];
  result[1] = b->finite_rot_axis[1];
  result[2] = b->finite_rot_axis[2];
}


EXPORT_C int dBodyGetNumJoints (dBodyID b)
{
  int count=0;
  for (dxJointNode *n=b->firstjoint; n ; n=n->next, count++)
      {
      }
  return count;
}


EXPORT_C dJointID dBodyGetJoint (dBodyID b, int index)
{
  int i=0;
  for (dxJointNode *n=b->firstjoint; n; n=n->next, i++) {
    if (i == index) return n->joint;
  }
  return 0;
}


EXPORT_C void dBodyEnable (dBodyID b)
{
  b->flags &= ~dxBodyDisabled;
  b->adis_stepsleft = b->adis.idle_steps;
  b->adis_timeleft = b->adis.idle_time;
  // no code for average-processing needed here
}


EXPORT_C void dBodyDisable (dBodyID b)
{
  b->flags |= dxBodyDisabled;
}


EXPORT_C int dBodyIsEnabled (dBodyID b)
{
  return ((b->flags & dxBodyDisabled) == 0);
}


EXPORT_C void dBodySetGravityMode (dBodyID b, int mode)
{
  if (mode) b->flags &= ~dxBodyNoGravity;
  else b->flags |= dxBodyNoGravity;
}


EXPORT_C int dBodyGetGravityMode (dBodyID b)
{
  return ((b->flags & dxBodyNoGravity) == 0);
}


// body auto-disable functions

EXPORT_C dReal dBodyGetAutoDisableLinearThreshold (dBodyID b)
{
	return dSqrt (b->adis.linear_average_threshold);
}


EXPORT_C void dBodySetAutoDisableLinearThreshold (dBodyID b, dReal linear_average_threshold)
{
	b->adis.linear_average_threshold = dMUL(linear_average_threshold,linear_average_threshold);
}


EXPORT_C dReal dBodyGetAutoDisableAngularThreshold (dBodyID b)
{
	return dSqrt (b->adis.angular_average_threshold);
}


EXPORT_C void dBodySetAutoDisableAngularThreshold (dBodyID b, dReal angular_average_threshold)
{
	b->adis.angular_average_threshold = dMUL(angular_average_threshold,angular_average_threshold);
}


EXPORT_C int dBodyGetAutoDisableAverageSamplesCount (dBodyID b)
{
	return b->adis.average_samples;
}


EXPORT_C void dBodySetAutoDisableAverageSamplesCount (dBodyID b, unsigned int average_samples_count)
{
	b->adis.average_samples = average_samples_count;
	// update the average buffers
	if(b->average_lvel_buffer)
	{
		delete[] b->average_lvel_buffer;
		b->average_lvel_buffer = 0;
	}
	if(b->average_avel_buffer)
	{
		delete[] b->average_avel_buffer;
		b->average_avel_buffer = 0;
	}
	if(b->adis.average_samples > 0)
	{
		b->average_lvel_buffer = new dVector3[b->adis.average_samples];
		b->average_avel_buffer = new dVector3[b->adis.average_samples];
	}
	else
	{
		b->average_lvel_buffer = 0;
		b->average_avel_buffer = 0;
	}
	// new buffer is empty
	b->average_counter = 0;
	b->average_ready = 0;
}


EXPORT_C int dBodyGetAutoDisableSteps (dBodyID b)
{
	return b->adis.idle_steps;
}


EXPORT_C void dBodySetAutoDisableSteps (dBodyID b, int steps)
{
	b->adis.idle_steps = steps;
}


EXPORT_C dReal dBodyGetAutoDisableTime (dBodyID b)
{
	return b->adis.idle_time;
}


EXPORT_C void dBodySetAutoDisableTime (dBodyID b, dReal time)
{
	b->adis.idle_time = time;
}


EXPORT_C int dBodyGetAutoDisableFlag (dBodyID b)
{
	return ((b->flags & dxBodyAutoDisable) != 0);
}


EXPORT_C void dBodySetAutoDisableFlag (dBodyID b, int do_auto_disable)
{
	if (!do_auto_disable)
	{
		b->flags &= ~dxBodyAutoDisable;
		// (mg) we should also reset the IsDisabled state to correspond to the DoDisabling flag
		b->flags &= ~dxBodyDisabled;
		b->adis.idle_steps = dWorldGetAutoDisableSteps(b->world);
		b->adis.idle_time = dWorldGetAutoDisableTime(b->world);
		// resetting the average calculations too
		dBodySetAutoDisableAverageSamplesCount(b, dWorldGetAutoDisableAverageSamplesCount(b->world) );
	}
	else
	{
		b->flags |= dxBodyAutoDisable;
	}
}


EXPORT_C void dBodySetAutoDisableDefaults (dBodyID b)
{
	dWorldID w = b->world;
	b->adis = w->adis;
	dBodySetAutoDisableFlag (b, w->adis_flag);
}

//****************************************************************************
// joints

static void dJointInit (dxWorld *w, dxJoint *j)
{
  initObject (j,w);
  j->vtable = 0;
  j->flags = 0;
  j->node[0].joint = j;
  j->node[0].body = 0;
  j->node[0].next = 0;
  j->node[1].joint = j;
  j->node[1].body = 0;
  j->node[1].next = 0;
  dSetZero (j->lambda,6);
  addObjectToList (j,(dObject **) &w->firstjoint);
  w->nj++;
}


static dxJoint *createJoint (dWorldID w, dJointGroupID group,
			     dxJoint::Vtable *vtable)
{
  dxJoint *j;
  if (group) {
    j = (dxJoint*) group->stack.alloc (vtable->size);
    group->num++;
  }
  else j = (dxJoint*) dAlloc (vtable->size);
  dJointInit (w,j);
  j->vtable = vtable;
  if (group) j->flags |= dJOINT_INGROUP;
  if (vtable->init) vtable->init (j);
  j->feedback = 0;
  return j;
}


EXPORT_C dxJoint * dJointCreateBall (dWorldID w, dJointGroupID group)
{
  return createJoint (w,group,&__dball_vtable);
}


EXPORT_C dxJoint * dJointCreateHinge (dWorldID w, dJointGroupID group)
{
  return createJoint (w,group,&__dhinge_vtable);
}


EXPORT_C dxJoint * dJointCreateSlider (dWorldID w, dJointGroupID group)
{
  return createJoint (w,group,&__dslider_vtable);
}


EXPORT_C dxJoint * dJointCreateContact (dWorldID w, dJointGroupID group,
			       const dContact *c)
{
  dxJointContact *j = (dxJointContact *)
    createJoint (w,group,&__dcontact_vtable);
  j->contact = *c;
  return j;
}


EXPORT_C dxJoint * dJointCreateHinge2 (dWorldID w, dJointGroupID group)
{
  return createJoint (w,group,&__dhinge2_vtable);
}


EXPORT_C dxJoint * dJointCreateUniversal (dWorldID w, dJointGroupID group)
{
  return createJoint (w,group,&__duniversal_vtable);
}

EXPORT_C dxJoint * dJointCreatePR (dWorldID w, dJointGroupID group)
{
  return createJoint (w,group,&__dPR_vtable);
}

EXPORT_C dxJoint * dJointCreateFixed (dWorldID w, dJointGroupID group)
{
  return createJoint (w,group,&__dfixed_vtable);
}


EXPORT_C dxJoint * dJointCreateNull (dWorldID w, dJointGroupID group)
{
  return createJoint (w,group,&__dnull_vtable);
}


EXPORT_C dxJoint * dJointCreateAMotor (dWorldID w, dJointGroupID group)
{
  return createJoint (w,group,&__damotor_vtable);
}

EXPORT_C dxJoint * dJointCreateLMotor (dWorldID w, dJointGroupID group)
{
  return createJoint (w,group,&__dlmotor_vtable);
}

EXPORT_C dxJoint * dJointCreatePlane2D (dWorldID w, dJointGroupID group)
{
  return createJoint (w,group,&__dplane2d_vtable);
}

EXPORT_C void dJointDestroy (dxJoint *j)
{;
  if (j->flags & dJOINT_INGROUP) return;
  removeJointReferencesFromAttachedBodies (j);
  removeObjectFromList (j);
  j->world->nj--;
  dFree (j,j->vtable->size);
}


EXPORT_C dJointGroupID dJointGroupCreate (int /*max_size*/)
{
  dxJointGroup *group = new dxJointGroup;
  group->num = 0;
  return group;
}


EXPORT_C void dJointGroupDestroy (dJointGroupID group)
{
  dJointGroupEmpty (group);
  delete group;
}


EXPORT_C void dJointGroupEmpty (dJointGroupID group)
{
  // the joints in this group are detached starting from the most recently
  // added (at the top of the stack). this helps ensure that the various
  // linked lists are not traversed too much, as the joints will hopefully
  // be at the start of those lists.
  // if any group joints have their world pointer set to 0, their world was
  // previously destroyed. no special handling is required for these joints.

  int i;
  dxJoint **jlist = (dxJoint**) malloc (group->num * sizeof(dxJoint*));
  if (jlist == NULL) {
  	return;
  }
  dxJoint *j = (dxJoint*) group->stack.rewind();
  for (i=0; i < group->num; i++) {
    jlist[i] = j;
    j = (dxJoint*) (group->stack.next (j->vtable->size));
  }
  for (i=group->num-1; i >= 0; i--) {
    if (jlist[i]->world) {
      removeJointReferencesFromAttachedBodies (jlist[i]);
      removeObjectFromList (jlist[i]);
      jlist[i]->world->nj--;
    }
  }
  group->num = 0;
  
  free(jlist);
  
  group->stack.freeAll();
  
}


EXPORT_C void dJointAttach (dxJoint *joint, dxBody *body1, dxBody *body2)
{
  // remove any existing body attachments
  if (joint->node[0].body || joint->node[1].body) {
    removeJointReferencesFromAttachedBodies (joint);
  }

  // if a body is zero, make sure that it is body2, so 0 --> node[1].body
  if (body1==0) {
    body1 = body2;
    body2 = 0;
    joint->flags |= dJOINT_REVERSE;
  }
  else {
    joint->flags &= (~dJOINT_REVERSE);
  }

  // attach to new bodies
  joint->node[0].body = body1;
  joint->node[1].body = body2;
  if (body1) {
    joint->node[1].next = body1->firstjoint;
    body1->firstjoint = &joint->node[1];
  }
  else joint->node[1].next = 0;
  if (body2) {
    joint->node[0].next = body2->firstjoint;
    body2->firstjoint = &joint->node[0];
  }
  else {
    joint->node[0].next = 0;
  }
}


EXPORT_C void dJointSetData (dxJoint *joint, void *data)
{
  joint->userdata = data;
}


EXPORT_C void *dJointGetData (dxJoint *joint)
{
  return joint->userdata;
}


EXPORT_C int dJointGetType (dxJoint *joint)
{
  return joint->vtable->typenum;
}


EXPORT_C dBodyID dJointGetBody (dxJoint *joint, int index)
{
  if (index == 0 || index == 1) {
    if (joint->flags & dJOINT_REVERSE) return joint->node[1-index].body;
    else return joint->node[index].body;
  }
  else return 0;
}


EXPORT_C void dJointSetFeedback (dxJoint *joint, dJointFeedback *f)
{
  joint->feedback = f;
}


EXPORT_C dJointFeedback *dJointGetFeedback (dxJoint *joint)
{
  return joint->feedback;
}



EXPORT_C dJointID dConnectingJoint (dBodyID in_b1, dBodyID in_b2)
{
	dBodyID b1, b2;

	if (in_b1 == 0) {
		b1 = in_b2;
		b2 = in_b1;
	}
	else {
		b1 = in_b1;
		b2 = in_b2;
	}

    // look through b1's neighbour list for b2
    for (dxJointNode *n=b1->firstjoint; n; n=n->next) {
        if (n->body == b2) return n->joint;
    }

    return 0;
}



EXPORT_C int dConnectingJointList (dBodyID in_b1, dBodyID in_b2, dJointID* out_list)
{
	dBodyID b1, b2;

	if (in_b1 == 0) {
		b1 = in_b2;
		b2 = in_b1;
	}
	else {
		b1 = in_b1;
		b2 = in_b2;
	}

    // look through b1's neighbour list for b2
    int numConnectingJoints = 0;
    for (dxJointNode *n=b1->firstjoint; n; n=n->next) {
        if (n->body == b2)
            out_list[numConnectingJoints++] = n->joint;
    }

    return numConnectingJoints;
}


EXPORT_C int dAreConnected (dBodyID b1, dBodyID b2)
{
  // look through b1's neighbour list for b2
  for (dxJointNode *n=b1->firstjoint; n; n=n->next) {
    if (n->body == b2) return 1;
  }
  return 0;
}


EXPORT_C int dAreConnectedExcluding (dBodyID b1, dBodyID b2, int joint_type)
{
  // look through b1's neighbour list for b2
  for (dxJointNode *n=b1->firstjoint; n; n=n->next) {
    if (dJointGetType (n->joint) != joint_type && n->body == b2) return 1;
  }
  return 0;
}

//****************************************************************************
// world

EXPORT_C dxWorld * dWorldCreate()
{
  dxWorld *w = new dxWorld;
  w->firstbody = 0;
  w->firstjoint = 0;
  w->nb = 0;
  w->nj = 0;
  dSetZero (w->gravity,4);
  w->global_erp = REAL(0.2);

  w->global_cfm = REAL(2e-5f);

  w->adis.idle_steps = 10;
  w->adis.idle_time = 0;
  w->adis_flag = 0;
  w->adis.average_samples = 1;		// Default is 1 sample => Instantaneous velocity
  w->adis.angular_average_threshold = dMUL(REAL(0.01),REAL(0.01));	// (magnitude squared)
  w->adis.linear_average_threshold = dMUL(REAL(0.01),REAL(0.01));		// (magnitude squared)

  w->qs.num_iterations = 20;
  w->qs.w = REAL(1.3);

  w->contactp.max_vel = dInfinity;
  w->contactp.min_depth = 0;

  return w;
}


EXPORT_C void dWorldDestroy (dxWorld *w)
{
  // delete all bodies and joints

  dxBody *nextb, *b = w->firstbody;
  while (b) {
    nextb = (dxBody*) b->next;
    if(b->average_lvel_buffer)
    {
      delete[] (b->average_lvel_buffer);
      b->average_lvel_buffer = 0;
    }
    if(b->average_avel_buffer)
    {
      delete[] (b->average_avel_buffer);
      b->average_avel_buffer = 0;
    }
    dBodyDestroy(b); // calling here dBodyDestroy for correct destroying! (i.e. the average buffers)
    b = nextb;
  }
  dxJoint *nextj, *j = w->firstjoint;
  while (j) {
    nextj = (dxJoint*)j->next;
    if (j->flags & dJOINT_INGROUP) {
      // the joint is part of a group, so "deactivate" it instead
      j->world = 0;
      j->node[0].body = 0;
      j->node[0].next = 0;
      j->node[1].body = 0;
      j->node[1].next = 0;
    }
    else {
      dFree (j,j->vtable->size);
    }
    j = nextj;
  }
  delete w;
}


EXPORT_C void dWorldSetGravity (dWorldID w, dReal x, dReal y, dReal z)
{
  w->gravity[0] = x;
  w->gravity[1] = y;
  w->gravity[2] = z;
}


EXPORT_C void dWorldGetGravity (dWorldID w, dVector3 g)
{
  g[0] = w->gravity[0];
  g[1] = w->gravity[1];
  g[2] = w->gravity[2];
}


EXPORT_C void dWorldSetERP (dWorldID w, dReal erp)
{
  w->global_erp = erp;
}


EXPORT_C dReal dWorldGetERP (dWorldID w)
{
  return w->global_erp;
}


EXPORT_C void dWorldSetCFM (dWorldID w, dReal cfm)
{
  w->global_cfm = cfm;
}


EXPORT_C dReal dWorldGetCFM (dWorldID w)
{
  return w->global_cfm;
}


EXPORT_C void dWorldStep (dWorldID w, dReal stepsize)
{
  dxProcessIslands (w,stepsize,&dInternalStepIsland);
}


EXPORT_C void dWorldQuickStep (dWorldID w, dReal stepsize)
{
  dxProcessIslands (w,stepsize,&dxQuickStepper);
}


EXPORT_C void dWorldImpulseToForce (dWorldID /*w*/, dReal stepsize,
			   dReal ix, dReal iy, dReal iz,
			   dVector3 force)
{
  stepsize = dRecip(stepsize);
  force[0] = dMUL(stepsize,ix);
  force[1] = dMUL(stepsize,iy);
  force[2] = dMUL(stepsize,iz);
  // @@@ force[3] = 0;
}


// world auto-disable functions

EXPORT_C dReal dWorldGetAutoDisableLinearThreshold (dWorldID w)
{
	return dSqrt (w->adis.linear_average_threshold);
}


EXPORT_C void dWorldSetAutoDisableLinearThreshold (dWorldID w, dReal linear_average_threshold)
{
	w->adis.linear_average_threshold = dMUL(linear_average_threshold,linear_average_threshold);
}


EXPORT_C dReal dWorldGetAutoDisableAngularThreshold (dWorldID w)
{
	return dSqrt (w->adis.angular_average_threshold);
}


EXPORT_C void dWorldSetAutoDisableAngularThreshold (dWorldID w, dReal angular_average_threshold)
{
	w->adis.angular_average_threshold = dMUL(angular_average_threshold,angular_average_threshold);
}


EXPORT_C int dWorldGetAutoDisableAverageSamplesCount (dWorldID w)
{
	return w->adis.average_samples;
}


EXPORT_C void dWorldSetAutoDisableAverageSamplesCount (dWorldID w, unsigned int average_samples_count)
{
	w->adis.average_samples = average_samples_count;
}


EXPORT_C int dWorldGetAutoDisableSteps (dWorldID w)
{
	return w->adis.idle_steps;
}


EXPORT_C void dWorldSetAutoDisableSteps (dWorldID w, int steps)
{
	w->adis.idle_steps = steps;
}


EXPORT_C dReal dWorldGetAutoDisableTime (dWorldID w)
{
	return w->adis.idle_time;
}


EXPORT_C void dWorldSetAutoDisableTime (dWorldID w, dReal time)
{
	w->adis.idle_time = time;
}


EXPORT_C int dWorldGetAutoDisableFlag (dWorldID w)
{
	return w->adis_flag;
}


EXPORT_C void dWorldSetAutoDisableFlag (dWorldID w, int do_auto_disable)
{
	w->adis_flag = (do_auto_disable != 0);
}


EXPORT_C void dWorldSetQuickStepNumIterations (dWorldID w, int num)
{
	w->qs.num_iterations = num;
}


EXPORT_C int dWorldGetQuickStepNumIterations (dWorldID w)
{
	return w->qs.num_iterations;
}


EXPORT_C void dWorldSetQuickStepW (dWorldID w, dReal param)
{
	w->qs.w = param;
}


EXPORT_C dReal dWorldGetQuickStepW (dWorldID w)
{
	return w->qs.w;
}


EXPORT_C void dWorldSetContactMaxCorrectingVel (dWorldID w, dReal vel)
{
	w->contactp.max_vel = vel;
}


EXPORT_C dReal dWorldGetContactMaxCorrectingVel (dWorldID w)
{
	return w->contactp.max_vel;
}


EXPORT_C void dWorldSetContactSurfaceLayer (dWorldID w, dReal depth)
{
	w->contactp.min_depth = depth;
}


EXPORT_C dReal dWorldGetContactSurfaceLayer (dWorldID w)
{
	return w->contactp.min_depth;
}

