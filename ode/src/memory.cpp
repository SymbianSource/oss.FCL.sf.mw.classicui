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

#include <ode/config.h>
#include <ode/memory.h>
#include <ode/error.h>
#include <ode/ode.h>


EXPORT_C void dSetAllocHandler (dAllocFunction *fn)
{
  GetGlobalData()->allocfn = fn;
}


EXPORT_C void dSetReallocHandler (dReallocFunction *fn)
{
  GetGlobalData()->reallocfn = fn;
}


EXPORT_C void dSetFreeHandler (dFreeFunction *fn)
{
  GetGlobalData()->freefn = fn;
}


EXPORT_C dAllocFunction *dGetAllocHandler()
{
  return GetGlobalData()->allocfn;
}


EXPORT_C dReallocFunction *dGetReallocHandler()
{
  return GetGlobalData()->reallocfn;
}


EXPORT_C dFreeFunction *dGetFreeHandler()
{
  return GetGlobalData()->freefn;
}


EXPORT_C void * dAlloc (size_t size)
{
  if (GetGlobalData()->allocfn) return GetGlobalData()->allocfn (size); else return malloc (size);
}


EXPORT_C void * dRealloc (void *ptr, size_t oldsize, size_t newsize)
{
  if (GetGlobalData()->reallocfn) return GetGlobalData()->reallocfn (ptr,oldsize,newsize);
  else return realloc (ptr,newsize);
}


EXPORT_C void dFree (void *ptr, size_t size)
{
  if (!ptr) return;
  if (GetGlobalData()->freefn) GetGlobalData()->freefn (ptr,size); else free (ptr);
}
