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

#ifndef _ODE_ODE_H_
#define _ODE_ODE_H_

/* include *everything* here */

#include <ode/config.h>
#include <ode/compatibility.h>
#include <ode/common.h>
#include <ode/contact.h>
#include <ode/error.h>
#include <ode/memory.h>
#include <ode/odemath.h>
#include <ode/matrix.h>
#include <ode/timer.h>
#include <ode/rotation.h>
#include <ode/mass.h>
#include <ode/misc.h>
#include <ode/objects.h>
//#include "odecpp.h"
#include <ode/collision_space.h>
#include <ode/collision.h>
//#include "odecpp_collision.h"

struct dxPosR;

// function pointers and modes for n^2 class collider functions

struct dColliderEntry {
  dColliderFn *fn;	// collider function, 0 = no function available
  int reverse;		// 1 = reverse o1 and o2
};

// MAXNUM is the array size for events used by the test timer for debugging
// purposes. This value was decreased from 100 to 1 to reduce the amount
// of WSD used by ODE. If the timer is used ("TIMING" flag defined) then also
// this value has to be increased.
#define MAXNUM 1

struct TEventData 
    {
    unsigned long cc[2];		// clock counts
    double total_t;		// total clocks used in this slot.
    double total_p;		// total percentage points used in this slot.
    int count;			// number of times this slot has been updated.
    char *description;		// pointer to static string
    };

// struct used to overcome writable static data
struct TOdeStaticData
    {
    dxPosR* s_cachedPosR;
    int colliders_initialized;
    int num_user_classes;
    dGeomClass user_classes [dMaxUserClasses];
    dMessageFunction *error_function;
    dMessageFunction *debug_function;
    dMessageFunction *message_function;
    dAllocFunction *allocfn;
    dReallocFunction *reallocfn;
    dFreeFunction *freefn;
    int autoEnableDepth;
    int num;
    unsigned long seed;
    dColliderEntry colliders[dGeomNumClasses][dGeomNumClasses];
    bool hit;
    struct TEventData event[MAXNUM];
    };

struct TOdeStaticData* GetGlobalData();

#endif
