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

geom transform

*/

#include <ode/collision.h>
#include <ode/matrix.h>
#include <ode/rotation.h>
#include <ode/odemath.h>
#include "collision_transform.h"
#include "collision_util.h"

//****************************************************************************
// dxGeomTransform class

struct dxGeomTransform : public dxGeom {
  dxGeom *obj;		// object that is being transformed
  int cleanup;		// 1 to destroy obj when destroyed
  int infomode;		// 1 to put Tx geom in dContactGeom g1

  // cached final object transform (body tx + relative tx). this is set by
  // computeAABB(), and it is valid while the AABB is valid.
  dxPosR transform_posr;

  dxGeomTransform (dSpaceID space);
  ~dxGeomTransform();
  void computeAABB();
  void computeFinalTx();
};


dxGeomTransform::dxGeomTransform (dSpaceID space) : dxGeom (space,1)
{
  type = dGeomTransformClass;
  obj = 0;
  cleanup = 0;
  infomode = 0;
  dSetZero (transform_posr.pos,4);
  dRSetIdentity (transform_posr.R);
}


dxGeomTransform::~dxGeomTransform()
{
  if (obj && cleanup) delete obj;
}


void dxGeomTransform::computeAABB()
{
  if (!obj) {
    dSetZero (aabb,6);
    return;
  }

  // backup the relative pos and R pointers of the encapsulated geom object
  dxPosR* posr_bak = obj->final_posr;

  // compute temporary pos and R for the encapsulated geom object
  computeFinalTx();
  obj->final_posr = &transform_posr;

  // compute the AABB
  obj->computeAABB();
  memcpy (aabb,obj->aabb,6*sizeof(dReal));

  // restore the pos and R
  obj->final_posr = posr_bak;
}


// utility function for dCollideTransform() : compute final pos and R
// for the encapsulated geom object

void dxGeomTransform::computeFinalTx()
{
  dMULTIPLY0_331 (transform_posr.pos,final_posr->R,obj->final_posr->pos);
  transform_posr.pos[0] += final_posr->pos[0];
  transform_posr.pos[1] += final_posr->pos[1];
  transform_posr.pos[2] += final_posr->pos[2];
  dMULTIPLY0_333 (transform_posr.R,final_posr->R,obj->final_posr->R);
}

//****************************************************************************
// collider function:
// this collides a transformed geom with another geom. the other geom can
// also be a transformed geom, but this case is not handled specially.

int dCollideTransform (dxGeom *o1, dxGeom *o2, int flags,
		       dContactGeom *contact, int skip)
{


  dxGeomTransform *tr = (dxGeomTransform*) o1;
  if (!tr->obj) return 0;


  // backup the relative pos and R pointers of the encapsulated geom object,
  // and the body pointer
  dxPosR *posr_bak = tr->obj->final_posr;
  dxBody *bodybak = tr->obj->body;

  // compute temporary pos and R for the encapsulated geom object.
  // note that final_pos and final_R are valid if no GEOM_AABB_BAD flag,
  // because computeFinalTx() will have already been called in
  // dxGeomTransform::computeAABB()

  if (tr->gflags & GEOM_AABB_BAD) tr->computeFinalTx();
  tr->obj->final_posr = &tr->transform_posr;
  tr->obj->body = o1->body;

  // do the collision
  int n = dCollide (tr->obj,o2,flags,contact,skip);

  // if required, adjust the 'g1' values in the generated contacts so that
  // thay indicated the GeomTransform object instead of the encapsulated
  // object.
  if (tr->infomode) {
    for (int i=0; i<n; i++) {
      dContactGeom *c = CONTACT(contact,skip*i);
      c->g1 = o1;
    }
  }

  // restore the pos, R and body
  tr->obj->final_posr = posr_bak;
  tr->obj->body = bodybak;
  return n;
}

//****************************************************************************
// public API

EXPORT_C dGeomID dCreateGeomTransform (dSpaceID space)
{
  return new dxGeomTransform (space);
}


EXPORT_C void dGeomTransformSetGeom (dGeomID g, dGeomID obj)
{

  dxGeomTransform *tr = (dxGeomTransform*) g;
  if (tr->obj && tr->cleanup) delete tr->obj;
  tr->obj = obj;
}


EXPORT_C dGeomID dGeomTransformGetGeom (dGeomID g)
{

  dxGeomTransform *tr = (dxGeomTransform*) g;
  return tr->obj;
}


EXPORT_C void dGeomTransformSetCleanup (dGeomID g, int mode)
{

  dxGeomTransform *tr = (dxGeomTransform*) g;
  tr->cleanup = mode;
}


EXPORT_C int dGeomTransformGetCleanup (dGeomID g)
{

  dxGeomTransform *tr = (dxGeomTransform*) g;
  return tr->cleanup;
}


EXPORT_C void dGeomTransformSetInfo (dGeomID g, int mode)
{

  dxGeomTransform *tr = (dxGeomTransform*) g;
  tr->infomode = mode;
}


EXPORT_C int dGeomTransformGetInfo (dGeomID g)
{

  dxGeomTransform *tr = (dxGeomTransform*) g;
  return tr->infomode;
}
