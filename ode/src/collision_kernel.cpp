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

/*

core collision functions and data structures, plus part of the public API
for geometry objects

*/
#ifndef __WINSCW__
#include <e32std.h>
#endif // !__WINSCW__

#include <ode/common.h>
#include <ode/matrix.h>
#include <ode/rotation.h>
#include <ode/objects.h>
#include <ode/odemath.h>
#include "collision_kernel.h"
#include "collision_util.h"
#include "collision_std.h"
#include "collision_transform.h"
#include <ode/ode.h>

//****************************************************************************
// helper functions for dCollide()ing a space with another geom

// this struct records the parameters passed to dCollideSpaceGeom()

// Allocate and free posr - we cache a single posr to avoid thrashing
dxPosR* dAllocPosr()
{
	dxPosR* retPosR;
	if (GetGlobalData()->s_cachedPosR)
	{
		retPosR = GetGlobalData()->s_cachedPosR;
		GetGlobalData()->s_cachedPosR = 0;
	}
	else
	{
		retPosR = (dxPosR*) dAlloc (sizeof(dxPosR));
	}
	return retPosR;
}

void dFreePosr(dxPosR* oldPosR)
{
	if (oldPosR)
	{
		if (GetGlobalData()->s_cachedPosR)
		{
			dFree(GetGlobalData()->s_cachedPosR, sizeof(dxPosR));
		}
		GetGlobalData()->s_cachedPosR = oldPosR;
	}
}

void dClearPosrCache(void)
{
	if (GetGlobalData()->s_cachedPosR)
	{
		dFree(GetGlobalData()->s_cachedPosR, sizeof(dxPosR));
		GetGlobalData()->s_cachedPosR = 0;
	}
}

struct SpaceGeomColliderData {
  int flags;			// space left in contacts array
  dContactGeom *contact;
  int skip;
};


static void space_geom_collider (void *data, dxGeom *o1, dxGeom *o2)
{
  SpaceGeomColliderData *d = (SpaceGeomColliderData*) data;
  if (d->flags & NUMC_MASK) {
    int n = dCollide (o1,o2,d->flags,d->contact,d->skip);
    d->contact = CONTACT (d->contact,d->skip*n);
    d->flags -= n;
  }
}


static int dCollideSpaceGeom (dxGeom *o1, dxGeom *o2, int flags,
			      dContactGeom *contact, int skip)
{
  SpaceGeomColliderData data;
  data.flags = flags;
  data.contact = contact;
  data.skip = skip;
  dSpaceCollide2 (o1,o2,&data,&space_geom_collider);
  return (flags & NUMC_MASK) - (data.flags & NUMC_MASK);
}

//****************************************************************************
// dispatcher for the N^2 collider functions


// setCollider() will refuse to write over a collider entry once it has
// been written.

static void setCollider (int i, int j, dColliderFn *fn)
{
  if (GetGlobalData()->colliders[i][j].fn == 0) {
    GetGlobalData()->colliders[i][j].fn = fn;
    GetGlobalData()->colliders[i][j].reverse = 0;
  }
  if (GetGlobalData()->colliders[j][i].fn == 0) {
    GetGlobalData()->colliders[j][i].fn = fn;
    GetGlobalData()->colliders[j][i].reverse = 1;
  }
}


static void setAllColliders (int i, dColliderFn *fn)
{
  for (int j=0; j<dGeomNumClasses; j++) setCollider (i,j,fn);
}


static void initColliders()
{
  int i,j;

  if (GetGlobalData()->colliders_initialized) return;
  GetGlobalData()->colliders_initialized = 1;

  memset (GetGlobalData()->colliders,0,sizeof(GetGlobalData()->colliders));

  // setup space colliders
  for (i=dFirstSpaceClass; i <= dLastSpaceClass; i++) {
    for (j=0; j < dGeomNumClasses; j++) {
      setCollider (i,j,&dCollideSpaceGeom);
    }
  }

  setCollider (dSphereClass,dSphereClass,&dCollideSphereSphere);
  setCollider (dSphereClass,dBoxClass,&dCollideSphereBox);
  setCollider (dSphereClass,dPlaneClass,&dCollideSpherePlane);
  setCollider (dBoxClass,dBoxClass,&dCollideBoxBox);
  setCollider (dBoxClass,dPlaneClass,&dCollideBoxPlane);
  setCollider (dCapsuleClass,dSphereClass,&dCollideCapsuleSphere);
  setCollider (dCapsuleClass,dBoxClass,&dCollideCapsuleBox);
  setCollider (dCapsuleClass,dCapsuleClass,&dCollideCapsuleCapsule);
  setCollider (dCapsuleClass,dPlaneClass,&dCollideCapsulePlane);
  setCollider (dRayClass,dSphereClass,&dCollideRaySphere);
  setCollider (dRayClass,dBoxClass,&dCollideRayBox);
  setCollider (dRayClass,dCapsuleClass,&dCollideRayCapsule);
  setCollider (dRayClass,dPlaneClass,&dCollideRayPlane);
  setCollider (dRayClass,dCylinderClass,&dCollideRayCylinder);
  setCollider (dCylinderClass,dBoxClass,&dCollideCylinderBox);
  setCollider (dCylinderClass,dSphereClass,&dCollideCylinderSphere);
  setCollider (dCylinderClass,dPlaneClass,&dCollideCylinderPlane);
  //setCollider (dCylinderClass,dCylinderClass,&dCollideCylinderCylinder);

//--> Convex Collision
  setCollider (dConvexClass,dPlaneClass,&dCollideConvexPlane);
  setCollider (dSphereClass,dConvexClass,&dCollideSphereConvex);
  setCollider (dConvexClass,dBoxClass,&dCollideConvexBox);
  setCollider (dConvexClass,dCapsuleClass,&dCollideConvexCapsule);
  setCollider (dConvexClass,dConvexClass,&dCollideConvexConvex);
  setCollider (dRayClass,dConvexClass,&dCollideRayConvex);
//<-- Convex Collision

//--> dHeightfield Collision
  setCollider (dHeightfieldClass,dRayClass,&dCollideHeightfield);
  setCollider (dHeightfieldClass,dSphereClass,&dCollideHeightfield);
  setCollider (dHeightfieldClass,dBoxClass,&dCollideHeightfield);
  setCollider (dHeightfieldClass,dCapsuleClass,&dCollideHeightfield);
  setCollider (dHeightfieldClass,dCylinderClass,&dCollideHeightfield);
  setCollider (dHeightfieldClass,dConvexClass,&dCollideHeightfield);
#if dTRIMESH_ENABLED
  setCollider (dHeightfieldClass,dTriMeshClass,&dCollideHeightfield);
#endif
//<-- dHeightfield Collision

  setAllColliders (dGeomTransformClass,&dCollideTransform);
}


EXPORT_C int dCollide (dxGeom *o1, dxGeom *o2, int flags, dContactGeom *contact,
	      int skip)
{

  // no contacts if both geoms are the same
  if (o1 == o2) return 0;

  // no contacts if both geoms on the same body, and the body is not 0
  if (o1->body == o2->body && o1->body) return 0;

  o1->recomputePosr();
  o2->recomputePosr();

  dColliderEntry *ce = &GetGlobalData()->colliders[o1->type][o2->type];
  int count = 0;
  if (ce->fn) {
    if (ce->reverse) {
      count = (*ce->fn) (o2,o1,flags,contact,skip);
      for (int i=0; i<count; i++) {
	dContactGeom *c = CONTACT(contact,skip*i);
	c->normal[0] = -c->normal[0];
	c->normal[1] = -c->normal[1];
	c->normal[2] = -c->normal[2];
	dxGeom *tmp = c->g1;
	c->g1 = c->g2;
	c->g2 = tmp;
	int tmpint = c->side1;
	c->side1 = c->side2;
	c->side2 = tmpint;
      }
    }
    else {
      count = (*ce->fn) (o1,o2,flags,contact,skip);
    }
  }
  return count;
}

//****************************************************************************
// dxGeom

dxGeom::dxGeom (dSpaceID _space, int is_placeable)
{
  initColliders();

  // setup body vars. invalid type of -1 must be changed by the constructor.
  type = -1;
  gflags = GEOM_DIRTY | GEOM_AABB_BAD | GEOM_ENABLED;
  if (is_placeable) gflags |= GEOM_PLACEABLE;
  data = 0;
  body = 0;
  body_next = 0;
  if (is_placeable) {
	final_posr = dAllocPosr();
    dSetZero (final_posr->pos,4);
    dRSetIdentity (final_posr->R);
  }
  else {
    final_posr = 0;
  }
  offset_posr = 0;

  // setup space vars
  next = 0;
  tome = 0;
  parent_space = 0;
  dSetZero (aabb,6);
  category_bits = ~0;
  collide_bits = ~0;

  // put this geom in a space if required
  if (_space) dSpaceAdd (_space,this);
}


dxGeom::~dxGeom()
{
   if (parent_space) dSpaceRemove (parent_space,this);
   if ((gflags & GEOM_PLACEABLE) && (!body || (body && offset_posr)))
     dFreePosr(final_posr);
   if (offset_posr) dFreePosr(offset_posr);
   bodyRemove();
}


int dxGeom::AABBTest (dxGeom */*o*/, dReal /*aabb*/[6])
{
  return 1;
}


void dxGeom::bodyRemove()
{
  if (body) {
    // delete this geom from body list
    dxGeom **last = &body->geom, *g = body->geom;
    while (g) {
      if (g == this) {
	*last = g->body_next;
	break;
      }
      last = &g->body_next;
      g = g->body_next;
    }
    body = 0;
    body_next = 0;
  }
}

inline void myswap(dReal& a, dReal& b) { dReal t=b; b=a; a=t; }


inline void matrixInvert(const dMatrix3& inMat, dMatrix3& outMat)
{
	memcpy(outMat, inMat, sizeof(dMatrix3));
	// swap _12 and _21
	myswap(outMat[0 + 4*1], outMat[1 + 4*0]);
	// swap _31 and _13
	myswap(outMat[2 + 4*0], outMat[0 + 4*2]);
	// swap _23 and _32
	myswap(outMat[1 + 4*2], outMat[2 + 4*1]);
}

void getBodyPosr(const dxPosR& offset_posr, const dxPosR& final_posr, dxPosR& body_posr)
{
	dMatrix3 inv_offset;
	matrixInvert(offset_posr.R, inv_offset);

	dMULTIPLY0_333(body_posr.R, final_posr.R, inv_offset);
	dVector3 world_offset;
	dMULTIPLY0_331(world_offset, body_posr.R, offset_posr.pos);
	body_posr.pos[0] = final_posr.pos[0] - world_offset[0];
	body_posr.pos[1] = final_posr.pos[1] - world_offset[1];
	body_posr.pos[2] = final_posr.pos[2] - world_offset[2];
}

void getWorldOffsetPosr(const dxPosR& body_posr, const dxPosR& world_posr, dxPosR& offset_posr)
{
	dMatrix3 inv_body;
	matrixInvert(body_posr.R, inv_body);

	dMULTIPLY0_333(offset_posr.R, inv_body, world_posr.R);
	dVector3 world_offset;
	world_offset[0] = world_posr.pos[0] - body_posr.pos[0];
	world_offset[1] = world_posr.pos[1] - body_posr.pos[1];
	world_offset[2] = world_posr.pos[2] - body_posr.pos[2];
	dMULTIPLY0_331(offset_posr.pos, inv_body, world_offset);
}

void dxGeom::computePosr()
{
  // should only be recalced if we need to - ie offset from a body
  
  dMULTIPLY0_331 (final_posr->pos,body->posr.R,offset_posr->pos);
  final_posr->pos[0] += body->posr.pos[0];
  final_posr->pos[1] += body->posr.pos[1];
  final_posr->pos[2] += body->posr.pos[2];
  dMULTIPLY0_333 (final_posr->R,body->posr.R,offset_posr->R);
}

//****************************************************************************
// misc

dxGeom *dGeomGetBodyNext (dxGeom *geom)
{
  return geom->body_next;
}

//****************************************************************************
// public API for geometry objects



EXPORT_C void dGeomDestroy (dxGeom *g)
{
  delete g;
}


EXPORT_C void dGeomSetData (dxGeom *g, void *data)
{
  g->data = data;
}


EXPORT_C void *dGeomGetData (dxGeom *g)
{
  return g->data;
}


EXPORT_C void dGeomSetBody (dxGeom *g, dxBody *b)
{

  if (b) {
    if (!g->body) dFreePosr(g->final_posr);
    if (g->body != b) {
      if (g->offset_posr) {
        dFreePosr(g->offset_posr);
        g->offset_posr = 0;
      }
      g->final_posr = &b->posr;
      g->bodyRemove();
      g->bodyAdd (b);
    }
    dGeomMoved (g);
  }
  else {
    if (g->body) {
      if (g->offset_posr)
      {
        // if we're offset, we already have our own final position, make sure its updated
        g->recomputePosr();
        dFreePosr(g->offset_posr);
        g->offset_posr = 0;
      }
      else
      {
        g->final_posr = dAllocPosr();
        memcpy (g->final_posr->pos,g->body->posr.pos,sizeof(dVector3));
        memcpy (g->final_posr->R,g->body->posr.R,sizeof(dMatrix3));
      }
      g->bodyRemove();
    }
    // dGeomMoved() should not be called if the body is being set to 0, as the
    // new position of the geom is set to the old position of the body, so the
    // effective position of the geom remains unchanged.
  }
}


EXPORT_C dBodyID dGeomGetBody (dxGeom *g)
{
  return g->body;
}


EXPORT_C void dGeomSetPosition (dxGeom *g, dReal x, dReal y, dReal z)
{
  if (g->offset_posr) {
    // move body such that body+offset = position
	dVector3 world_offset;
	dMULTIPLY0_331(world_offset, g->body->posr.R, g->offset_posr->pos);
	dBodySetPosition(g->body,
	    x - world_offset[0],
	    y - world_offset[1],
	    z - world_offset[2]);
  }
  else if (g->body) {
    // this will call dGeomMoved (g), so we don't have to
    dBodySetPosition (g->body,x,y,z);
  }
  else {
    g->final_posr->pos[0] = x;
    g->final_posr->pos[1] = y;
    g->final_posr->pos[2] = z;
    dGeomMoved (g);
  }
}


EXPORT_C void dGeomSetRotation (dxGeom *g, const dMatrix3 R)
{

  if (g->offset_posr) {
    g->recomputePosr();
    // move body such that body+offset = rotation
    dxPosR new_final_posr;
    dxPosR new_body_posr;
    memcpy(new_final_posr.pos, g->final_posr->pos, sizeof(dVector3));
    memcpy(new_final_posr.R, R, sizeof(dMatrix3));
    getBodyPosr(*g->offset_posr, new_final_posr, new_body_posr);
    dBodySetRotation(g->body, new_body_posr.R);
    dBodySetPosition(g->body, new_body_posr.pos[0], new_body_posr.pos[1], new_body_posr.pos[2]);
  }
  else if (g->body) {
    // this will call dGeomMoved (g), so we don't have to
    dBodySetRotation (g->body,R);
  }
  else {
    memcpy (g->final_posr->R,R,sizeof(dMatrix3));
    dGeomMoved (g);
  }
}


EXPORT_C void dGeomSetQuaternion (dxGeom *g, const dQuaternion quat)
{
  if (g->offset_posr) {
    g->recomputePosr();
    // move body such that body+offset = rotation
    dxPosR new_final_posr;
    dxPosR new_body_posr;
    dQtoR (quat, new_final_posr.R);
    memcpy(new_final_posr.pos, g->final_posr->pos, sizeof(dVector3));
    
    getBodyPosr(*g->offset_posr, new_final_posr, new_body_posr);
    dBodySetRotation(g->body, new_body_posr.R);
    dBodySetPosition(g->body, new_body_posr.pos[0], new_body_posr.pos[1], new_body_posr.pos[2]);
  }
  if (g->body) {
    // this will call dGeomMoved (g), so we don't have to
    dBodySetQuaternion (g->body,quat);
  }
  else {
    dQtoR (quat, g->final_posr->R);
    dGeomMoved (g);
  }
}


EXPORT_C const dReal * dGeomGetPosition (dxGeom *g)
{
  g->recomputePosr();
  return g->final_posr->pos;
}


EXPORT_C void dGeomCopyPosition(dxGeom *g, dVector3 pos)
{
  g->recomputePosr();
  const dReal* src = g->final_posr->pos;
  pos[0] = src[0];
  pos[1] = src[1];
  pos[2] = src[2];
}


EXPORT_C const dReal * dGeomGetRotation (dxGeom *g)
{
  g->recomputePosr();
  return g->final_posr->R;
}


EXPORT_C void dGeomCopyRotation(dxGeom *g, dMatrix3 R)
{
  g->recomputePosr();
  const dReal* src = g->final_posr->R;
  R[0]  = src[0];
  R[1]  = src[1];
  R[2]  = src[2];
  R[4]  = src[4];
  R[5]  = src[5];
  R[6]  = src[6];
  R[8]  = src[8];
  R[9]  = src[9];
  R[10] = src[10];
}


EXPORT_C void dGeomGetQuaternion (dxGeom *g, dQuaternion quat)
{
  if (g->body && !g->offset_posr) {
    const dReal * body_quat = dBodyGetQuaternion (g->body);
    quat[0] = body_quat[0];
    quat[1] = body_quat[1];
    quat[2] = body_quat[2];
    quat[3] = body_quat[3];
  }
  else {
    g->recomputePosr();
    dRtoQ (g->final_posr->R, quat);
  }
}


EXPORT_C void dGeomGetAABB (dxGeom *g, dReal aabb[6])
{
  g->recomputeAABB();
  memcpy (aabb,g->aabb,6 * sizeof(dReal));
}


EXPORT_C int dGeomIsSpace (dxGeom *g)
{

  return IS_SPACE(g);
}


EXPORT_C dSpaceID dGeomGetSpace (dxGeom *g)
{

  return g->parent_space;
}


EXPORT_C int dGeomGetClass (dxGeom *g)
{

  return g->type;
}


EXPORT_C void dGeomSetCategoryBits (dxGeom *g, unsigned long bits)
{

  g->category_bits = bits;
}


EXPORT_C void dGeomSetCollideBits (dxGeom *g, unsigned long bits)
{

  g->collide_bits = bits;
}


EXPORT_C unsigned long dGeomGetCategoryBits (dxGeom *g)
{

  return g->category_bits;
}


EXPORT_C unsigned long dGeomGetCollideBits (dxGeom *g)
{

  return g->collide_bits;
}


EXPORT_C void dGeomEnable (dxGeom *g)
{

	g->gflags |= GEOM_ENABLED;
}

EXPORT_C void dGeomDisable (dxGeom *g)
{

	g->gflags &= ~GEOM_ENABLED;
}

EXPORT_C int dGeomIsEnabled (dxGeom *g)
{

	return (g->gflags & GEOM_ENABLED) != 0;
}


//****************************************************************************
// C interface that lets the user make new classes. this interface is a lot
// more cumbersome than C++ subclassing, which is what is used internally
// in ODE. this API is mainly to support legacy code.

struct dxUserGeom : public dxGeom {
  void *user_data;

  dxUserGeom (int class_num);
  ~dxUserGeom();
  void computeAABB();
  int AABBTest (dxGeom *o, dReal aabb[6]);
};


dxUserGeom::dxUserGeom (int class_num) : dxGeom (0,1)
{
  type = class_num;
  int size = GetGlobalData()->user_classes[type-dFirstUserClass].bytes;
  user_data = dAlloc (size);
  memset (user_data,0,size);
}


dxUserGeom::~dxUserGeom()
{
  dGeomClass *c = &GetGlobalData()->user_classes[type-dFirstUserClass];
  if (c->dtor) c->dtor (this);
  dFree (user_data,c->bytes);
}


void dxUserGeom::computeAABB()
{
  GetGlobalData()->user_classes[type-dFirstUserClass].aabb (this,aabb);
}


int dxUserGeom::AABBTest (dxGeom *o, dReal aabb[6])
{
  dGeomClass *c = &GetGlobalData()->user_classes[type-dFirstUserClass];
  if (c->aabb_test) return c->aabb_test (this,o,aabb);
  else return 1;
}


static int dCollideUserGeomWithGeom (dxGeom *o1, dxGeom *o2, int flags,
				     dContactGeom *contact, int skip)
{
  // this generic collider function is called the first time that a user class
  // tries to collide against something. it will find out the correct collider
  // function and then set the colliders array so that the correct function is
  // called directly the next time around.

  int t1 = o1->type;	// note that o1 is a user geom
  int t2 = o2->type;	// o2 *may* be a user geom

  // find the collider function to use. if o1 does not know how to collide with
  // o2, then o2 might know how to collide with o1 (provided that it is a user
  // geom).
  dColliderFn *fn = GetGlobalData()->user_classes[t1-dFirstUserClass].collider (t2);
  int reverse = 0;
  if (!fn && t2 >= dFirstUserClass && t2 <= dLastUserClass) {
    fn = GetGlobalData()->user_classes[t2-dFirstUserClass].collider (t1);
    reverse = 1;
  }

  // set the colliders array so that the correct function is called directly
  // the next time around. note that fn can be 0 here if no collider was found,
  // which means that dCollide() will always return 0 for this case.
  GetGlobalData()->colliders[t1][t2].fn = fn;
  GetGlobalData()->colliders[t1][t2].reverse = reverse;
  GetGlobalData()->colliders[t2][t1].fn = fn;
  GetGlobalData()->colliders[t2][t1].reverse = !reverse;

  // now call the collider function indirectly through dCollide(), so that
  // contact reversing is properly handled.
  return dCollide (o1,o2,flags,contact,skip);
}


EXPORT_C int dCreateGeomClass (const dGeomClass *c)
{


  if (GetGlobalData()->num_user_classes >= dMaxUserClasses) {

  }
  GetGlobalData()->user_classes[GetGlobalData()->num_user_classes] = *c;
  int class_number = GetGlobalData()->num_user_classes + dFirstUserClass;
  initColliders();
  setAllColliders (class_number,&dCollideUserGeomWithGeom);

  GetGlobalData()->num_user_classes++;
  return class_number;
}


EXPORT_C void * dGeomGetClassData (dxGeom *g)
{

  dxUserGeom *user = (dxUserGeom*) g;
  return user->user_data;
}


EXPORT_C dGeomID dCreateGeom (int classnum)
{

  return new dxUserGeom (classnum);
}



/* ************************************************************************ */
/* geom offset from body */

void dGeomCreateOffset (dxGeom *g)
{

  if (g->offset_posr)
  {
	return; // already created
  }

  
  g->final_posr = dAllocPosr();
  g->offset_posr = dAllocPosr();
  dSetZero (g->offset_posr->pos,4);
  dRSetIdentity (g->offset_posr->R);
  
  g->gflags |= GEOM_POSR_BAD;
}

EXPORT_C void dGeomSetOffsetPosition (dxGeom *g, dReal x, dReal y, dReal z)
{


  if (!g->offset_posr) 
  {
	dGeomCreateOffset(g);
  }
  g->offset_posr->pos[0] = x;
  g->offset_posr->pos[1] = y;
  g->offset_posr->pos[2] = z;
  dGeomMoved (g);
}

EXPORT_C void dGeomSetOffsetRotation (dxGeom *g, const dMatrix3 R)
{

  if (!g->offset_posr) 
  {
	dGeomCreateOffset (g);
  }
  memcpy (g->offset_posr->R,R,sizeof(dMatrix3));
  dGeomMoved (g);
}

EXPORT_C void dGeomSetOffsetQuaternion (dxGeom *g, const dQuaternion quat)
{

  if (!g->offset_posr) 
  {
	dGeomCreateOffset (g);
  }
  dQtoR (quat, g->offset_posr->R);
  dGeomMoved (g);
}

EXPORT_C void dGeomSetOffsetWorldPosition (dxGeom *g, dReal x, dReal y, dReal z)
{

  if (!g->offset_posr) 
  {
	dGeomCreateOffset(g);
  }
  dBodyGetPosRelPoint(g->body, x, y, z, g->offset_posr->pos);
  dGeomMoved (g);
}

EXPORT_C void dGeomSetOffsetWorldRotation (dxGeom *g, const dMatrix3 R)
{

  if (!g->offset_posr) 
  {
	dGeomCreateOffset (g);
  }
  g->recomputePosr();
  
  dxPosR new_final_posr;
  memcpy(new_final_posr.pos, g->final_posr->pos, sizeof(dVector3));
  memcpy(new_final_posr.R, R, sizeof(dMatrix3));
  
  getWorldOffsetPosr(g->body->posr, new_final_posr, *g->offset_posr);
  dGeomMoved (g);
}

EXPORT_C void dGeomSetOffsetWorldQuaternion (dxGeom *g, const dQuaternion quat)
{

  if (!g->offset_posr) 
  {
	dGeomCreateOffset (g);
  }

  g->recomputePosr();
  
  dxPosR new_final_posr;
  memcpy(new_final_posr.pos, g->final_posr->pos, sizeof(dVector3));
  dQtoR (quat, new_final_posr.R);
  
  getWorldOffsetPosr(g->body->posr, new_final_posr, *g->offset_posr);
  dGeomMoved (g);
}

EXPORT_C void dGeomClearOffset(dxGeom *g)
{

  if (g->offset_posr)
  {
    // no longer need an offset posr
	dFreePosr(g->offset_posr);
	g->offset_posr = 0;
    // the geom will now share the position of the body
    dFreePosr(g->final_posr);
    g->final_posr = &g->body->posr;
    // geom has moved
    g->gflags &= ~GEOM_POSR_BAD;
    dGeomMoved (g);
  }
}

EXPORT_C int dGeomIsOffset(dxGeom *g)
{

  return ((0 != g->offset_posr) ? 1 : 0);
}

static const dVector3 OFFSET_POSITION_ZERO = { REAL(0.0f), REAL(0.0f), REAL(0.0f), REAL(0.0f) };

EXPORT_C const dReal * dGeomGetOffsetPosition (dxGeom *g)
{

  if (g->offset_posr)
  {
    return g->offset_posr->pos;
  }
  return OFFSET_POSITION_ZERO;
}

EXPORT_C void dGeomCopyOffsetPosition (dxGeom *g, dVector3 pos)
{

  if (g->offset_posr)
  {
    const dReal* src = g->offset_posr->pos;
    pos[0] = src[0];
	 pos[1] = src[1];
	 pos[2] = src[2];
  }
  else
  {
    pos[0] = 0;
	 pos[1] = 0;
	 pos[2] = 0;
  }
}

static const dMatrix3 OFFSET_ROTATION_ZERO = 
{ 
	REAL(1.0f), REAL(0.0f), REAL(0.0f), REAL(0.0f), 
	REAL(0.0f), REAL(1.0f), REAL(0.0f), REAL(0.0f), 
	REAL(0.0f), REAL(0.0f), REAL(1.0f), REAL(0.0f), 
};

EXPORT_C const dReal * dGeomGetOffsetRotation (dxGeom *g)
{

  if (g->offset_posr)
  {
    return g->offset_posr->R;
  }
  return OFFSET_ROTATION_ZERO;
}

EXPORT_C void dGeomCopyOffsetRotation (dxGeom *g, dMatrix3 R)
{

	if (g->offset_posr)
	{
		const dReal* src = g->final_posr->R;
		R[0]  = src[0];
		R[1]  = src[1];
		R[2]  = src[2];
		R[4]  = src[4];
		R[5]  = src[5];
		R[6]  = src[6];
		R[8]  = src[8];
		R[9]  = src[9];
		R[10] = src[10];
	}
	else
	{
		R[0]  = OFFSET_ROTATION_ZERO[0];
		R[1]  = OFFSET_ROTATION_ZERO[1];
		R[2]  = OFFSET_ROTATION_ZERO[2];
		R[4]  = OFFSET_ROTATION_ZERO[4];
		R[5]  = OFFSET_ROTATION_ZERO[5];
		R[6]  = OFFSET_ROTATION_ZERO[6];
		R[8]  = OFFSET_ROTATION_ZERO[8];
		R[9]  = OFFSET_ROTATION_ZERO[9];
		R[10] = OFFSET_ROTATION_ZERO[10];
	}
}

EXPORT_C void dGeomGetOffsetQuaternion (dxGeom *g, dQuaternion result)
{
  if (g->offset_posr)
  {
    dRtoQ (g->offset_posr->R, result);
  }
  else
  {
    dSetZero (result,4);
    result[0] = REAL(1.0);
  }
}

//****************************************************************************
// initialization and shutdown routines - allocate and initialize data,
// cleanup before exiting

extern void opcode_collider_cleanup();

EXPORT_C void dInitODE()
{
#ifndef __WINSCW__
    Mem::FillZ( GetGlobalData(), sizeof( TOdeStaticData ) );
    GetGlobalData()->autoEnableDepth = 2;
#endif // !__WINSCW__
}

EXPORT_C void dCloseODE()
{
  GetGlobalData()->colliders_initialized = 0;
  GetGlobalData()->num_user_classes = 0;
  dClearPosrCache();
}
