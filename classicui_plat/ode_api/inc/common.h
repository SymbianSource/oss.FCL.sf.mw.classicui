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

#ifndef _ODE_COMMON_H_
#define _ODE_COMMON_H_
#include <ode/config.h>
#include <ode/error.h>
#include <math.h>

#include <ode/lookup_tables.h>

#ifdef __cplusplus
extern "C" {
#endif


/* configuration stuff */

/* the efficient alignment. most platforms align data structures to some
 * number of bytes, but this is not always the most efficient alignment.
 * for example, many x86 compilers align to 4 bytes, but on a pentium it
 * is important to align doubles to 8 byte boundaries (for speed), and
 * the 4 floats in a SIMD register to 16 byte boundaries. many other
 * platforms have similar behavior. setting a larger alignment can waste
 * a (very) small amount of memory. NOTE: this number must be a power of
 * two. this is set to 16 by default.
 */
#define EFFICIENT_ALIGNMENT 16
#define QFACTOR				16 // 16


/* constants */

/* pi and 1/sqrt(2) are defined here if necessary because they don't get
 * defined in <math.h> on some platforms (like MS-Windows)
 */

#define dPI				REAL(3.1415926535897932384626433832795029)
#define dSQRT1_2 		REAL(0.7071067811865475244008443621048490)

#define dInfinity		REAL(1e+14) //REAL(1e+14)

#define dEpsilon 		REAL(2e-5)


/* floating point data type, vector, matrix and quaternion types */

#ifdef dSINGLE
typedef int64 dReal;
#endif

/* round an integer up to a multiple of 4, except that 0 and 1 are unmodified
 * (used to compute matrix leading dimensions)
 */
#define dPAD(a) (((a) > 1) ? ((((a)-1)|3)+1) : (a))

/* these types are mainly just used in headers */
typedef dReal dVector3[4];
typedef dReal dVector4[4];
typedef dReal dMatrix3[4*3];
typedef dReal dMatrix4[4*4];
typedef dReal dMatrix6[8*6];
typedef dReal dQuaternion[4];


/* precision dependent scalar math functions */


#if defined(dSINGLE)

#define dMUL(x,y)		( (dReal)(((x)*(y))>>QFACTOR) )
#define dDIV(x,y)		( (dReal)(((x)<<QFACTOR)/(y)) )
#define REAL(x)			( (dReal)( (x)*(1<<QFACTOR) ) )
#define dFLOAT(x)		( ((float)(x))/((float)(1<<QFACTOR)) )
#define dRecip(x)		( (dReal)(REAL(1/dFLOAT(x))) )
#define dSqrt(x)		( (dReal)( sqrt( (x)<<QFACTOR ) ) )
#define dRecipSqrt(x)	( (dReal)( REAL(1/(sqrt(dFLOAT(x)))) ) )
#define dSin(x)			( (dReal)(sin_table[((x)>>QFACTOR) + ((x)!=0)])	)//sin(x)
#define dCos(x)			( (dReal)(sin_table[((x)>>QFACTOR) + ((x)!=0) + 90]) )//cos(x)
#define dFabs(x)		( (dReal)(abs(x)) )

#define dIsNan(x)		(_isnan(dFLOAT(x)))
#define dCopySign(a,b)	( (dReal)(copysign((a),(b))) )

#endif


/* utility */

/* round something up to be a multiple of the EFFICIENT_ALIGNMENT */

#define dEFFICIENT_SIZE(x) ((((x)-1)|(EFFICIENT_ALIGNMENT-1))+1)


/* alloca aligned to the EFFICIENT_ALIGNMENT. note that this can waste
 * up to 15 bytes per allocation, depending on what alloca() returns.
 */

#define dALLOCA16(n) \
  ((char*)dEFFICIENT_SIZE(((size_t)(malloc/*alloca*/((n)+(EFFICIENT_ALIGNMENT-1))))))


// Use the error-checking memory allocation system.  Because this system uses heap
//  (malloc) instead of stack (alloca), it is slower.  However, it allows you to
//  simulate larger scenes, as well as handle out-of-memory errors in a somewhat
//  graceful manner

#define dUSE_MALLOC_FOR_ALLOCA

#ifdef dUSE_MALLOC_FOR_ALLOCA
enum {
  d_MEMORY_OK = 0,		/* no memory errors */
  d_MEMORY_OUT_OF_MEMORY	/* malloc failed due to out of memory error */
};

#endif



/* internal object types (all prefixed with `dx') */

struct dxWorld;		/* dynamics world */
struct dxSpace;		/* collision space */
struct dxBody;		/* rigid body (dynamics object) */
struct dxGeom;		/* geometry (collision object) */
struct dxJoint;
struct dxJointNode;
struct dxJointGroup;

typedef struct dxWorld *dWorldID;
typedef struct dxSpace *dSpaceID;
typedef struct dxBody *dBodyID;
typedef struct dxGeom *dGeomID;
typedef struct dxJoint *dJointID;
typedef struct dxJointGroup *dJointGroupID;


/* error numbers */

enum {
  d_ERR_UNKNOWN = 0,		/* unknown error */
  d_ERR_IASSERT,		/* internal assertion failed */
  d_ERR_UASSERT,		/* user assertion failed */
  d_ERR_LCP			/* user assertion failed */
};


/* joint type numbers */

enum {
  dJointTypeNone = 0,		/* or "unknown" */
  dJointTypeBall,
  dJointTypeHinge,
  dJointTypeSlider,
  dJointTypeContact,
  dJointTypeUniversal,
  dJointTypeHinge2,
  dJointTypeFixed,
  dJointTypeNull,
  dJointTypeAMotor,
  dJointTypeLMotor,
  dJointTypePlane2D,
  dJointTypePR
};


/* standard joint parameter names. why are these here? - because we don't want
 * to include all the joint function definitions in joint.cpp. hmmmm.
 * MSVC complains if we call D_ALL_PARAM_NAMES_X with a blank second argument,
 * which is why we have the D_ALL_PARAM_NAMES macro as well. please copy and
 * paste between these two.
 */

#define D_ALL_PARAM_NAMES(start) \
  /* parameters for limits and motors */ \
  dParamLoStop = start, \
  dParamHiStop, \
  dParamVel, \
  dParamFMax, \
  dParamFudgeFactor, \
  dParamBounce, \
  dParamCFM, \
  dParamStopERP, \
  dParamStopCFM, \
  /* parameters for suspension */ \
  dParamSuspensionERP, \
  dParamSuspensionCFM,

#define D_ALL_PARAM_NAMES_X(start,x) \
  /* parameters for limits and motors */ \
  dParamLoStop ## x = start, \
  dParamHiStop ## x, \
  dParamVel ## x, \
  dParamFMax ## x, \
  dParamFudgeFactor ## x, \
  dParamBounce ## x, \
  dParamCFM ## x, \
  dParamStopERP ## x, \
  dParamStopCFM ## x, \
  /* parameters for suspension */ \
  dParamSuspensionERP ## x, \
  dParamSuspensionCFM ## x,

enum {
  D_ALL_PARAM_NAMES(0)
  D_ALL_PARAM_NAMES_X(0x100,2)
  D_ALL_PARAM_NAMES_X(0x200,3)

  /* add a multiple of this constant to the basic parameter numbers to get
   * the parameters for the second, third etc axes.
   */
  dParamGroup=0x100
};


/* angular motor mode numbers */

enum{
  dAMotorUser = 0,
  dAMotorEuler = 1
};


/* joint force feedback information */

typedef struct dJointFeedback {
  dVector3 f1;		/* force applied to body 1 */
  dVector3 t1;		/* torque applied to body 1 */
  dVector3 f2;		/* force applied to body 2 */
  dVector3 t2;		/* torque applied to body 2 */
} dJointFeedback;


/* private functions that must be implemented by the collision library:
 * (1) indicate that a geom has moved, (2) get the next geom in a body list.
 * these functions are called whenever the position of geoms connected to a
 * body have changed, e.g. with dBodySetPosition(), dBodySetRotation(), or
 * when the ODE step function updates the body state.
 */

void dGeomMoved (dGeomID);
dGeomID dGeomGetBodyNext (dGeomID);


#ifdef __cplusplus
}
#endif

#endif
