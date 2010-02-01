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

#include <ode/common.h>
#include <ode/matrix.h>

// misc defines
//#define ALLOCA dALLOCA16


EXPORT_C void dSetZero (dReal *a, int n)
{
  while (n > 0) {
    *(a++) = 0;
    n--;
  }
}


EXPORT_C void dSetValue (dReal *a, int n, dReal value)
{
  while (n > 0) {
    *(a++) = value;
    n--;
  }
}


EXPORT_C void dMultiply0 (dReal *A, const dReal *B, const dReal *C, int p, int q, int r)
{
  int i,j,k,qskip,rskip,rpad;
  qskip = dPAD(q);
  rskip = dPAD(r);
  rpad = rskip - r;
  dReal sum;
  const dReal *b,*c,*bb;
  bb = B;
  for (i=p; i; i--) {
    for (j=0 ; j<r; j++) {
      c = C + j;
      b = bb;
      sum = 0;
      for (k=q; k; k--, c+=rskip) sum += dMUL((*(b++)),(*c));
      *(A++) = sum; 
    }
    A += rpad;
    bb += qskip;
  }
}


EXPORT_C void dMultiply1 (dReal *A, const dReal *B, const dReal *C, int p, int q, int r)
{
  int i,j,k,pskip,rskip;
  dReal sum;
  pskip = dPAD(p);
  rskip = dPAD(r);
  for (i=0; i<p; i++) {
    for (j=0; j<r; j++) {
      sum = 0;
      for (k=0; k<q; k++) sum += dMUL(B[i+k*pskip],C[j+k*rskip]);
      A[i*rskip+j] = sum;
    }
  }
}


EXPORT_C void dMultiply2 (dReal *A, const dReal *B, const dReal *C, int p, int q, int r)
{
  int i,j,k,z,rpad,qskip;
  dReal sum;
  const dReal *bb,*cc;
  rpad = dPAD(r) - r;
  qskip = dPAD(q);
  bb = B;
  for (i=p; i; i--) {
    cc = C;
    for (j=r; j; j--) {
      z = 0;
      sum = 0;
      for (k=q; k; k--,z++) sum += dMUL(bb[z],cc[z]);
      *(A++) = sum; 
      cc += qskip;
    }
    A += rpad;
    bb += qskip;
  }
}


EXPORT_C int dFactorCholesky (dReal *A, int n)
{
  int i,j,k,nskip;
  dReal sum,*a,*b,*aa,*bb,*cc,*recip;
  nskip = dPAD (n);
  recip = (dReal*) malloc (n * sizeof(dReal));
  if(recip == NULL) {
  	return 0;
  }
  aa = A;
  for (i=0; i<n; i++) {
    bb = A;
    cc = A + i*nskip;
    for (j=0; j<i; j++) {
      sum = *cc;
      a = aa;
      b = bb;
      for (k=j; k; k--) sum -= dMUL((*(a++)),(*(b++)));
      *cc = dMUL(sum,recip[j]);
      bb += nskip;
      cc++;
    }
    sum = *cc;
    a = aa;
    for (k=i; k; k--, a++) sum -= dMUL((*a),(*a));
    if (sum <= REAL(0.0)) {
        free(recip);
        return 0;
    }
    *cc = dSqrt(sum);
    recip[i] = dRecip (*cc);
    aa += nskip;
  }
  free(recip);
  return 1;
}


EXPORT_C void dSolveCholesky (const dReal *L, dReal *b, int n)
{
  int i,k,nskip;
  dReal sum,*y;
  nskip = dPAD (n);
  y = (dReal*) malloc (n*sizeof(dReal));
  if (y == NULL) {
  	return;
  }
  for (i=0; i<n; i++) {
    sum = 0;
    for (k=0; k < i; k++) sum += dMUL(L[i*nskip+k],y[k]);
    y[i] = dDIV((b[i]-sum),L[i*nskip+i]);
  }
  for (i=n-1; i >= 0; i--) {
    sum = 0;
    for (k=i+1; k < n; k++) sum += dMUL(L[k*nskip+i],b[k]);
    b[i] = dDIV((y[i]-sum),L[i*nskip+i]);
  }
  free(y);
}


EXPORT_C int dInvertPDMatrix (const dReal *A, dReal *Ainv, int n)
{
  int i,j,nskip;
  dReal *L,*x;
  nskip = dPAD (n);
  L = (dReal*) malloc (nskip*n*sizeof(dReal));
  if (L == NULL) {
  	return 0;
  }
  memcpy (L,A,nskip*n*sizeof(dReal));
  x = (dReal*) malloc (n*sizeof(dReal));
  if (x == NULL) {
  	free(L);
  	return 0;
  }
  if (dFactorCholesky (L,n)==0) {
    free(L);
    free(x);
    return 0;
  }
  dSetZero (Ainv,n*nskip);	// make sure all padding elements set to 0
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) x[j] = REAL(0.0);
    x[i] = REAL(1.0);
    dSolveCholesky (L,x,n);
    for (j=0; j<n; j++) Ainv[j*nskip+i] = x[j];
  }
  free(L);
  free(x);
  return 1;  
}


EXPORT_C int dIsPositiveDefinite (const dReal *A, int n)
{
  dReal *Acopy;
  int nskip = dPAD (n);
  Acopy = (dReal*) malloc (nskip*n * sizeof(dReal));
  if ( Acopy == NULL) {
  	return 0;
  }
  memcpy (Acopy,A,nskip*n * sizeof(dReal));
  int ret = dFactorCholesky (Acopy,n);
  free(Acopy);
  return ret;
}


/***** this has been replaced by a faster version
void dSolveL1T (const dReal *L, dReal *b, int n, int nskip)
{
  int i,j;
  dReal sum;
  for (i=n-2; i>=0; i--) {
    sum = 0;
    for (j=i+1; j<n; j++) sum += L[j*nskip+i]*b[j];
    b[i] -= sum;
  }
}
*/


EXPORT_C void dVectorScale (dReal *a, const dReal *d, int n)
{
  for (int i=0; i<n; i++) a[i] = dMUL(a[i],d[i]);
}


EXPORT_C void dSolveLDLT (const dReal *L, const dReal *d, dReal *b, int n, int nskip)
{
  dSolveL1 (L,b,n,nskip);
  dVectorScale (b,d,n);
  dSolveL1T (L,b,n,nskip);
}


EXPORT_C void dLDLTAddTL (dReal *L, dReal *d, const dReal *a, int n, int nskip)
{
  int j,p;
  dReal *W1,*W2,W11,W21,alpha1,alpha2,alphanew,gamma1,gamma2,k1,k2,Wp,ell,dee;

  if (n < 2) return;
  W1 = (dReal*) malloc (n*sizeof(dReal));
  if (W1 == NULL) {
  	return;
  }
  W2 = (dReal*) malloc (n*sizeof(dReal));
  if (W2 == NULL) {
  	free(W1);
  	return;
  }

  W1[0] = 0;
  W2[0] = 0;
  for (j=1; j<n; j++) W1[j] = W2[j] = dMUL(a[j],dSQRT1_2);
  W11 = dMUL((dMUL(REAL(0.5),a[0])+REAL(1.0)),dSQRT1_2);
  W21 = dMUL((dMUL(REAL(0.5),a[0])-REAL(1.0)),dSQRT1_2);

  alpha1=REAL(1.0);
  alpha2=REAL(1.0);

  dee = d[0];
  alphanew = alpha1 + dMUL(dMUL(W11,W11),dee);
  dee = dDIV(dee,alphanew);
  gamma1 = dMUL(W11,dee);
  dee = dMUL(dee,alpha1);
  alpha1 = alphanew;
  alphanew = alpha2 - dMUL(dMUL(W21,W21),dee);
  dee = dDIV(dee,alphanew);
  gamma2 = dMUL(W21,dee);
  alpha2 = alphanew;
  k1 = REAL(1.0) - dMUL(W21,gamma1);
  k2 = dMUL(W21,dMUL(gamma1,W11)) - W21;
  for (p=1; p<n; p++) {
    Wp = W1[p];
    ell = L[p*nskip];
    W1[p] =    Wp - dMUL(W11,ell);
    W2[p] = dMUL(k1,Wp) +  dMUL(k2,ell);
  }

  for (j=1; j<n; j++) {
    dee = d[j];
    alphanew = alpha1 + dMUL(dMUL(W1[j],W1[j]),dee);
    dee = dDIV(dee,alphanew);
    gamma1 = dMUL(W1[j],dee);
    dee = dMUL(dee,alpha1);
    alpha1 = alphanew;
    alphanew = alpha2 - dMUL(dMUL(W2[j],W2[j]),dee);
    dee = dDIV(dee,alphanew);
    gamma2 = dMUL(W2[j],dee);
    dee = dMUL(dee,alpha2);
    d[j] = dee;
    alpha2 = alphanew;

    k1 = W1[j];
    k2 = W2[j];
    for (p=j+1; p<n; p++) {
      ell = L[p*nskip+j];
      Wp = W1[p] - dMUL(k1,ell);
      ell += dMUL(gamma1,Wp);
      W1[p] = Wp;
      Wp = W2[p] - dMUL(k2,ell);
      ell -= dMUL(gamma2,Wp);
      W2[p] = Wp;
      L[p*nskip+j] = ell;
    }
  }
  free(W1);
  free(W2);
}


// macros for dLDLTRemove() for accessing A - either access the matrix
// directly or access it via row pointers. we are only supposed to reference
// the lower triangle of A (it is symmetric), but indexes i and j come from
// permutation vectors so they are not predictable. so do a test on the
// indexes - this should not slow things down too much, as we don't do this
// in an inner loop.

#define _GETA(i,j) (A[i][j])
//#define _GETA(i,j) (A[(i)*nskip+(j)])
#define GETA(i,j) ((i > j) ? _GETA(i,j) : _GETA(j,i))


EXPORT_C void dLDLTRemove (dReal **A, const int *p, dReal *L, dReal *d,
		  int /*n1*/, int n2, int r, int nskip)
{
  int i;
 

  if (r==n2-1) {
    return;		// deleting last row/col is easy
  }
  else if (r==0) {
    dReal *a = (dReal*) malloc (n2 * sizeof(dReal));
    if (a == NULL) {
    	return;
    }
    for (i=0; i<n2; i++) a[i] = -GETA(p[i],p[0]);
    a[0] += REAL(1.0);
    dLDLTAddTL (L,d,a,n2,nskip);
    free(a);
  }
  else {
    dReal *t = (dReal*) malloc (r * sizeof(dReal));
    if (t == NULL) {
    	return;
    }
    dReal *a = (dReal*) malloc ((n2-r) * sizeof(dReal));
    if (a == NULL) {
    	free(t);
    	return;
    }
    for (i=0; i<r; i++) t[i] = dDIV(L[r*nskip+i],d[i]);
    for (i=0; i<(n2-r); i++)
      a[i] = dDot(L+(r+i)*nskip,t,r) - GETA(p[r+i],p[r]);
    a[0] += REAL(1.0);
    dLDLTAddTL (L + r*nskip+r, d+r, a, n2-r, nskip);
    free(t);
    free(a);
  }

  // snip out row/column r from L and d
  dRemoveRowCol (L,n2,nskip,r);
  if (r < (n2-1)) memmove (d+r,d+r+1,(n2-r-1)*sizeof(dReal));
}


EXPORT_C void dRemoveRowCol (dReal *A, int n, int nskip, int r)
{
  int i;
  if (r >= n-1) return;
  if (r > 0) {
    for (i=0; i<r; i++)
      memmove (A+i*nskip+r,A+i*nskip+r+1,(n-r-1)*sizeof(dReal));
    for (i=r; i<(n-1); i++)
      memcpy (A+i*nskip,A+i*nskip+nskip,r*sizeof(dReal));
  }
  for (i=r; i<(n-1); i++)
    memcpy (A+i*nskip+r,A+i*nskip+nskip+r+1,(n-r-1)*sizeof(dReal));
}
