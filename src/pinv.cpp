// Include Files
#include "pinv.h"
#include "svd.h"
#include <cmath>
#include <cstring>
#include <math.h>

// Function Definitions
//
// Arguments    : const double A[4]
//                double X[4]
// Return Type  : void
//
namespace coder {
void pinv(const double A[4], double X[4])
{
  double U[4];
  double V[4];
  double s[2];
  double absx;
  int exponent;
  int r;
  X[0] = 0.0;
  X[1] = 0.0;
  X[2] = 0.0;
  X[3] = 0.0;
  internal::svd(A, U, s, V);
  absx = std::abs(s[0]);
  if (absx <= 2.2250738585072014E-308) {
    absx = 4.94065645841247E-324;
  } else {
    frexp(absx, &exponent);
    absx = std::ldexp(1.0, exponent - 53);
  }
  absx *= 2.0;
  r = -1;
  exponent = 0;
  while ((exponent < 2) && (s[exponent] > absx)) {
    r++;
    exponent++;
  }
  if (r + 1 > 0) {
    int br;
    int i;
    int vcol;
    vcol = 1;
    for (br = 0; br <= r; br++) {
      absx = 1.0 / s[br];
      i = vcol + 1;
      for (exponent = vcol; exponent <= i; exponent++) {
        V[exponent - 1] *= absx;
      }
      vcol += 2;
    }
    for (exponent = 0; exponent <= 2; exponent += 2) {
      i = exponent + 1;
      vcol = exponent + 2;
      if (i <= vcol) {
        std::memset(&X[i + -1], 0, ((vcol - i) + 1) * sizeof(double));
      }
    }
    br = 0;
    for (exponent = 0; exponent <= 2; exponent += 2) {
      int ar;
      ar = -1;
      br++;
      i = br + (r << 1);
      for (int ib{br}; ib <= i; ib += 2) {
        int i1;
        vcol = exponent + 1;
        i1 = exponent + 2;
        for (int ic{vcol}; ic <= i1; ic++) {
          X[ic - 1] += U[ib - 1] * V[(ar + ic) - exponent];
        }
        ar += 2;
      }
    }
  }
}

} // namespace coder

//
// File trailer for pinv.cpp
//
// [EOF]
//
