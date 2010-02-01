/* generated code, do not edit. */

#include <ode/matrix.h>


EXPORT_C dReal dDot (const dReal *a, const dReal *b, int n)
{  
  dReal p0,q0,m0,p1,q1,m1,sum;
  sum = 0;
  n -= 2;
  while (n >= 0) {
    p0 = a[0]; q0 = b[0];
    m0 = dMUL(p0,q0);
    p1 = a[1]; q1 = b[1];
    m1 = dMUL(p1,q1);
    sum += m0;
    sum += m1;
    a += 2;
    b += 2;
    n -= 2;
  }
  n += 2;
  while (n > 0) {
    sum += dMUL((*a),(*b));
    a++;
    b++;
    n--;
  }
  return sum;
}
