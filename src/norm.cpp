// Include Files
#include "norm.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const double x[2]
// Return Type  : double
//
namespace coder {
double b_norm(const double x[2])
{
  double absxk;
  double scale;
  double t;
  double y;
  scale = 3.3121686421112381E-170;
  absxk = std::abs(x[0]);
  if (absxk > 3.3121686421112381E-170) {
    y = 1.0;
    scale = absxk;
  } else {
    t = absxk / 3.3121686421112381E-170;
    y = t * t;
  }
  absxk = std::abs(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }
  return scale * std::sqrt(y);
}

} // namespace coder

//
// File trailer for norm.cpp
//
// [EOF]
//
