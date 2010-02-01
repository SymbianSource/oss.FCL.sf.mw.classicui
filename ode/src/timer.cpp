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

TODO
----

* gettimeofday() and the pentium time stamp counter return the real time,
  not the process time. fix this somehow!

*/

#include <ode/common.h>
#include <ode/timer.h>
#include <ode/ode.h>

// misc defines
#define ALLOCA dALLOCA16


#include <sys/time.h>
#include <unistd.h>


static inline void getClockCount (unsigned long cc[2])
{
  struct timeval tv;
  gettimeofday (&tv,0);
  cc[0] = tv.tv_usec;
  cc[1] = tv.tv_sec;
}


static inline void serialize()
{
}


static inline double loadClockCount (unsigned long a[2])
{
  return a[1]*1.0e6 + a[0];
}


EXPORT_C double dTimerResolution()
{
  unsigned long cc1[2],cc2[2];
  getClockCount (cc1);
  do {
    getClockCount (cc2);
  }
  while (cc1[0]==cc2[0] && cc1[1]==cc2[1]);
  do {
    getClockCount (cc1);
  }
  while (cc1[0]==cc2[0] && cc1[1]==cc2[1]);
  double t1 = loadClockCount (cc1);
  double t2 = loadClockCount (cc2);
  return (t1-t2) / dTimerTicksPerSecond();
}


EXPORT_C double dTimerTicksPerSecond()
{
  return 1000000;
}

//****************************************************************************
// stop watches

EXPORT_C void dStopwatchReset (dStopwatch *s)
{
  s->time = 0;
  s->cc[0] = 0;
  s->cc[1] = 0;
}


EXPORT_C void dStopwatchStart (dStopwatch *s)
{
  serialize();
  getClockCount (s->cc);
}


EXPORT_C void dStopwatchStop  (dStopwatch *s)
{
  unsigned long cc[2];
  serialize();
  getClockCount (cc);
  double t1 = loadClockCount (s->cc);
  double t2 = loadClockCount (cc);
  s->time += t2-t1;
}


EXPORT_C double dStopwatchTime (dStopwatch *s)
{
  return s->time / dTimerTicksPerSecond();
}

//****************************************************************************
// code timers

// maximum number of events to record


// make sure all slot totals and counts reset to 0 at start

static void initSlots()
{
  static int initialized=0;
  if (!initialized) {
    for (int i=0; i<MAXNUM; i++) {
      GetGlobalData()->event[i].count = 0;
      GetGlobalData()->event[i].total_t = 0;
      GetGlobalData()->event[i].total_p = 0;
    }
    initialized = 1;
  }
}


EXPORT_C void dTimerStart (const char *description)
{
  initSlots();
  GetGlobalData()->event[0].description = const_cast<char*> (description);
  GetGlobalData()->num = 1;
  serialize();
  getClockCount (GetGlobalData()->event[0].cc);
}


EXPORT_C void dTimerNow (const char *description)
{
  if (GetGlobalData()->num < MAXNUM) {
    // do not serialize
    getClockCount (GetGlobalData()->event[GetGlobalData()->num].cc);
    GetGlobalData()->event[GetGlobalData()->num].description = const_cast<char*> (description);
    GetGlobalData()->num++;
  }
}


EXPORT_C void dTimerEnd()
{
  if (GetGlobalData()->num < MAXNUM) {
    serialize();
    getClockCount (GetGlobalData()->event[GetGlobalData()->num].cc);
    GetGlobalData()->event[GetGlobalData()->num].description = "TOTAL";
    GetGlobalData()->num++;
  }
}

//****************************************************************************
// print report

static void fprintDoubleWithPrefix (FILE *f, double a, char *fmt)
{
  if (a >= 0.999999) {
    fprintf (f,fmt,a);
    return;
  }
  a *= 1000.0;
  if (a >= 0.999999) {
    fprintf (f,fmt,a);
    fprintf (f,"m");
    return;
  }
  a *= 1000.0;
  if (a >= 0.999999) {
    fprintf (f,fmt,a);
    fprintf (f,"u");
    return;
  }
  a *= 1000.0;
  fprintf (f,fmt,a);
  fprintf (f,"n");
}


EXPORT_C void dTimerReport (FILE *fout, int average)
{
  int i;
  size_t maxl;
  double ccunit = 1.0/dTimerTicksPerSecond();
  fprintf (fout,"\nTimer Report (");
  fprintDoubleWithPrefix (fout,ccunit,"%.2f ");
  fprintf (fout,"s resolution)\n------------\n");
  if (GetGlobalData()->num < 1) return;

  // get maximum description length
  maxl = 0;
  for (i=0; i<GetGlobalData()->num; i++) {
    size_t l = strlen (GetGlobalData()->event[i].description);
    if (l > maxl) maxl = l;
  }

  // calculate total time
  double t1 = loadClockCount (GetGlobalData()->event[0].cc);
  double t2 = loadClockCount (GetGlobalData()->event[GetGlobalData()->num-1].cc);
  double total = t2 - t1;
  if (total <= 0) total = 1;

  // compute time difference for all slots except the last one. update totals
  double *times = (double*) malloc (GetGlobalData()->num * sizeof(double));
  if (times == NULL) {
  	return;
  }
  for (i=0; i < (GetGlobalData()->num-1); i++) {
    double t1 = loadClockCount (GetGlobalData()->event[i].cc);
    double t2 = loadClockCount (GetGlobalData()->event[i+1].cc);
    times[i] = t2 - t1;
    GetGlobalData()->event[i].count++;
    GetGlobalData()->event[i].total_t += times[i];
    GetGlobalData()->event[i].total_p += times[i]/total * 100.0;
  }

  // print report (with optional averages)
  for (i=0; i<GetGlobalData()->num; i++) {
    double t,p;
    if (i < (GetGlobalData()->num-1)) {
      t = times[i];
      p = t/total * 100.0;
    }
    else {
      t = total;
      p = 100.0;
    }
    fprintf (fout,"%-*s %7.2fms %6.2f%%",maxl,GetGlobalData()->event[i].description,
	     t*ccunit * 1000.0, p);
    if (average && i < (GetGlobalData()->num-1)) {
      fprintf (fout,"  (avg %7.2fms %6.2f%%)",
	       (GetGlobalData()->event[i].total_t / GetGlobalData()->event[i].count)*ccunit * 1000.0,
	       GetGlobalData()->event[i].total_p / GetGlobalData()->event[i].count);
    }
    fprintf (fout,"\n");
  }
  fprintf (fout,"\n");
  
  free(times);
}
