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
#include <ode/error.h>
#include <ode/ode.h>


extern "C" EXPORT_C void dSetErrorHandler (dMessageFunction *fn)
{
  GetGlobalData()->error_function = fn;
}


extern "C" EXPORT_C void dSetDebugHandler (dMessageFunction *fn)
{
  GetGlobalData()->debug_function = fn;
}


extern "C" EXPORT_C void dSetMessageHandler (dMessageFunction *fn)
{
  GetGlobalData()->message_function = fn;
}


extern "C" EXPORT_C dMessageFunction *dGetErrorHandler()
{
  return GetGlobalData()->error_function;
}


extern "C" EXPORT_C dMessageFunction *dGetDebugHandler()
{
  return GetGlobalData()->debug_function;
}


extern "C" EXPORT_C dMessageFunction *dGetMessageHandler()
{
  return GetGlobalData()->message_function;
}


static void printMessage (int num, const char *msg1, const char *msg2,
			  va_list ap)
{
  fflush (stderr);
  fflush (stdout);
  if (num) fprintf (stderr,"\n%s %d: ",msg1,num);
  else fprintf (stderr,"\n%s: ",msg1);
  vfprintf (stderr,msg2,ap);
  fprintf (stderr,"\n");
  fflush (stderr);
}

//****************************************************************************
// unix

#ifndef WIN32

extern "C" EXPORT_C void dError (int num, const char *msg, ...)
{
  va_list ap;
  va_start (ap,msg);
  if (GetGlobalData()->error_function) GetGlobalData()->error_function (num,msg,ap);
  else printMessage (num,"ODE Error",msg,ap);
  exit (1);
}

/*
extern "C" void dDebug (int num, const char *msg, ...)
{
  va_list ap;
  va_start (ap,msg);
  if (debug_function) debug_function (num,msg,ap);
  else printMessage (num,"ODE INTERNAL ERROR",msg,ap);
  // *((char *)0) = 0;   ... commit SEGVicide
  abort();
}


extern "C" void dMessage (int num, const char *msg, ...)
{
  va_list ap;
  va_start (ap,msg);
  if (message_function) message_function (num,msg,ap);
  else printMessage (num,"ODE Message",msg,ap);
}
*/
#endif

