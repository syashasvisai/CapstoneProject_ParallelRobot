// Include Files
#include "xswap.h"

// Function Definitions
//
// Arguments    : double x[4]
// Return Type  : void
//
namespace coder {
namespace internal {
namespace blas {
void xswap(double x[4])
{
  double temp;
  temp = x[0];
  x[0] = x[2];
  x[2] = temp;
  temp = x[1];
  x[1] = x[3];
  x[3] = temp;
}

} // namespace blas
} // namespace internal
} // namespace coder

//
// File trailer for xswap.cpp
//
// [EOF]
//
