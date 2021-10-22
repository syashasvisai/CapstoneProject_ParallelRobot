#ifndef XROTG_H
#define XROTG_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace blas {
void xrotg(double *a, double *b, double *c, double *s);

}
} // namespace internal
} // namespace coder

#endif
//
// File trailer for xrotg.h
//
// [EOF]
//
