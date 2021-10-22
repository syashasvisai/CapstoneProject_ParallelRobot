// Include Files
#include "cos.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : ::coder::array<double, 1U> &x
// Return Type  : void
//
namespace coder {
void b_cos(::coder::array<double, 1U> &x)
{
  int nx;
  nx = x.size(0);
  for (int k{0}; k < nx; k++) {
    x[k] = std::cos(x[k]);
  }
}

} // namespace coder

//
// File trailer for cos.cpp
//
// [EOF]
//
