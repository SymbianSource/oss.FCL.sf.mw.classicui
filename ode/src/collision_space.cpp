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

spaces

*/

#include <ode/common.h>
#include <ode/matrix.h>
#include <ode/collision_space.h>
#include <ode/collision.h>
#include "collision_kernel.h"

#include "collision_space_internal.h"

//****************************************************************************
// make the geom dirty by setting the GEOM_DIRTY and GEOM_BAD_AABB flags
// and moving it to the front of the space's list. all the parents of a
// dirty geom also become dirty.

void dGeomMoved (dxGeom *geom)
{
  
  // if geom is offset, mark it as needing a calculate
  if (geom->offset_posr) {
    geom->gflags |= GEOM_POSR_BAD;
  }
  
  // from the bottom of the space heirarchy up, process all clean geoms
  // turning them into dirty geoms.
  dxSpace *parent = geom->parent_space;

  while (parent && (geom->gflags & GEOM_DIRTY)==0) {

    geom->gflags |= GEOM_DIRTY | GEOM_AABB_BAD;
    parent->dirty (geom);
    geom = parent;
    parent = parent->parent_space;
  }

  // all the remaining dirty geoms must have their AABB_BAD flags set, to
  // ensure that their AABBs get recomputed
  while (geom) {
    geom->gflags |= GEOM_DIRTY | GEOM_AABB_BAD;

    geom = geom->parent_space;
  }
}

#define GEOM_ENABLED(g) ((g)->gflags & GEOM_ENABLED)

//****************************************************************************
// dxSpace

dxSpace::dxSpace (dSpaceID _space) : dxGeom (_space,0)
{
  count = 0;
  first = 0;
  cleanup = 1;
  current_index = 0;
  current_geom = 0;
  lock_count = 0;
}


dxSpace::~dxSpace()
{
  if (cleanup) {
    // note that destroying each geom will call remove()
    dxGeom *g,*n;
    for (g = first; g; g=n) {
      n = g->next;
      dGeomDestroy (g);
    }
  }
  else {
    dxGeom *g,*n;
    for (g = first; g; g=n) {
      n = g->next;
      remove (g);
    }
  }
}


void dxSpace::computeAABB()
{
  if (first) {
    int i;
    dReal a[6];
    a[0] = dInfinity;
    a[1] = -dInfinity;
    a[2] = dInfinity;
    a[3] = -dInfinity;
    a[4] = dInfinity;
    a[5] = -dInfinity;
    for (dxGeom *g=first; g; g=g->next) {
      g->recomputeAABB();
      for (i=0; i<6; i += 2) if (g->aabb[i] < a[i]) a[i] = g->aabb[i];
      for (i=1; i<6; i += 2) if (g->aabb[i] > a[i]) a[i] = g->aabb[i];
    }
    memcpy(aabb,a,6*sizeof(dReal));
  }
  else {
    dSetZero (aabb,6);
  }
}


void dxSpace::setCleanup (int mode)
{
  cleanup = (mode != 0);
}


int dxSpace::getCleanup()
{
  return cleanup;
}


int dxSpace::query (dxGeom *geom)
{
  return (geom->parent_space == this);
}


int dxSpace::getNumGeoms()
{
  return count;
}


// the dirty geoms are numbered 0..k, the clean geoms are numbered k+1..count-1

dxGeom *dxSpace::getGeom (int i)
{
  if (current_geom && current_index == i-1) {
    current_geom = current_geom->next;
    current_index = i;
    return current_geom;
  }
  else {
    dxGeom *g=first;
    for (int j=0; j<i; j++) {
      if (g) g = g->next; else return 0;
    }
    current_geom = g;
    current_index = i;
    return g;
  }
}


void dxSpace::add (dxGeom *geom)
{

  // add
  geom->parent_space = this;
  geom->spaceAdd (&first);
  count++;

  // enumerator has been invalidated
  current_geom = 0;

  // new geoms are added to the front of the list and are always
  // considered to be dirty. as a consequence, this space and all its
  // parents are dirty too.
  geom->gflags |= GEOM_DIRTY | GEOM_AABB_BAD;
  dGeomMoved (this);
}


void dxSpace::remove (dxGeom *geom)
{

  // remove
  geom->spaceRemove();
  count--;

  // safeguard
  geom->next = 0;
  geom->tome = 0;
  geom->parent_space = 0;

  // enumerator has been invalidated
  current_geom = 0;

  // the bounding box of this space (and that of all the parents) may have
  // changed as a consequence of the removal.
  dGeomMoved (this);
}


void dxSpace::dirty (dxGeom *geom)
{
  geom->spaceRemove();
  geom->spaceAdd (&first);
}

//****************************************************************************
// simple space - reports all n^2 object intersections

struct dxSimpleSpace : public dxSpace {
  dxSimpleSpace (dSpaceID _space);
  void cleanGeoms();
  void collide (void *data, dNearCallback *callback);
  void collide2 (void *data, dxGeom *geom, dNearCallback *callback);
};


dxSimpleSpace::dxSimpleSpace (dSpaceID _space) : dxSpace (_space)
{
  type = dSimpleSpaceClass;
}


void dxSimpleSpace::cleanGeoms()
{
  // compute the AABBs of all dirty geoms, and clear the dirty flags
  lock_count++;
  for (dxGeom *g=first; g && (g->gflags & GEOM_DIRTY); g=g->next) {
    if (IS_SPACE(g)) {
      ((dxSpace*)g)->cleanGeoms();
    }
    g->recomputeAABB();
    g->gflags &= (~(GEOM_DIRTY|GEOM_AABB_BAD));
  }
  lock_count--;
}


void dxSimpleSpace::collide (void *data, dNearCallback *callback)
{

  lock_count++;
  cleanGeoms();

  // intersect all bounding boxes
  for (dxGeom *g1=first; g1; g1=g1->next) {
    if (GEOM_ENABLED(g1)){
      for (dxGeom *g2=g1->next; g2; g2=g2->next) {
	if (GEOM_ENABLED(g2)){
	  collideAABBs (g1,g2,data,callback);
	}
      }
    }
  }

  lock_count--;
}


void dxSimpleSpace::collide2 (void *data, dxGeom *geom,
			      dNearCallback *callback)
{

  lock_count++;
  cleanGeoms();
  geom->recomputeAABB();

  // intersect bounding boxes
  for (dxGeom *g=first; g; g=g->next) {
    if (GEOM_ENABLED(g)){
      collideAABBs (g,geom,data,callback);
    }
  }

  lock_count--;
}

//****************************************************************************
// utility stuff for hash table space

// kind of silly, but oh well...
#ifndef MAXINT
#define MAXINT ((int)((((unsigned int)(-1)) << 1) >> 1))
#endif


// prime[i] is the largest prime smaller than 2^i
#define NUM_PRIMES 31


// an axis aligned bounding box in the hash table
struct dxAABB {
  dxAABB *next;		// next in the list of all AABBs
  int level;		// the level this is stored in (cell size = 2^level)
  int dbounds[6];	// AABB bounds, discretized to cell size
  dxGeom *geom;		// corresponding geometry object (AABB stored here)
  int index;		// index of this AABB, starting from 0
};


// a hash table node that represents an AABB that intersects a particular cell
// at a particular level
struct Node {
  Node *next;		// next node in hash table collision list, 0 if none
  int x,y,z;		// cell position in space, discretized to cell size
  dxAABB *aabb;		// axis aligned bounding box that intersects this cell
};



//****************************************************************************
// space functions

EXPORT_C dxSpace *dSimpleSpaceCreate (dxSpace *space)
{
  return new dxSimpleSpace (space);
}

EXPORT_C void dSpaceDestroy (dxSpace *space)
{
  dGeomDestroy (space);
}


EXPORT_C void dSpaceSetCleanup (dxSpace *space, int mode)
{

  space->setCleanup (mode);
}


EXPORT_C int dSpaceGetCleanup (dxSpace *space)
{

  return space->getCleanup();
}


EXPORT_C void dSpaceAdd (dxSpace *space, dxGeom *g)
{

  space->add (g);
}


EXPORT_C void dSpaceRemove (dxSpace *space, dxGeom *g)
{
  space->remove (g);
}


EXPORT_C int dSpaceQuery (dxSpace *space, dxGeom *g)
{

  return space->query (g);
}

EXPORT_C void dSpaceClean (dxSpace *space){

  space->cleanGeoms();
}

EXPORT_C int dSpaceGetNumGeoms (dxSpace *space)
{
  return space->getNumGeoms();
}


EXPORT_C dGeomID dSpaceGetGeom (dxSpace *space, int i)
{
  return space->getGeom (i);
}


EXPORT_C void dSpaceCollide (dxSpace *space, void *data, dNearCallback *callback)
{

  space->collide (data,callback);
}


EXPORT_C void dSpaceCollide2 (dxGeom *g1, dxGeom *g2, void *data,
		     dNearCallback *callback)
{

  dxSpace *s1,*s2;

  // see if either geom is a space
  if (IS_SPACE(g1)) s1 = (dxSpace*) g1; else s1 = 0;
  if (IS_SPACE(g2)) s2 = (dxSpace*) g2; else s2 = 0;

  // handle the four space/geom cases
  if (s1) {
    if (s2) {
      // g1 and g2 are spaces.
      if (s1==s2) {
	// collide a space with itself --> interior collision
	s1->collide (data,callback);
      }
      else {
	// iterate through the space that has the fewest geoms, calling
	// collide2 in the other space for each one.
	if (s1->count < s2->count) {
	  for (dxGeom *g = s1->first; g; g=g->next) {
	    s2->collide2 (data,g,callback);
	  }
	}
	else {
	  for (dxGeom *g = s2->first; g; g=g->next) {
	    s1->collide2 (data,g,callback);
	  }
	}
      }
    }
    else {
      // g1 is a space, g2 is a geom
      s1->collide2 (data,g2,callback);
    }
  }
  else {
    if (s2) {
      // g1 is a geom, g2 is a space
      s2->collide2 (data,g1,callback);
    }
    else {
      // g1 and g2 are geoms, call the callback directly
      callback (data,g1,g2);
    }
  }
}
