#ifndef SVD_H
#define SVD_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void svd(const double A[4], double U[4], double s[2], double V[4]);

}
} // namespace coder

#endif
//
// File trailer for svd.h
//
// [EOF]
//
