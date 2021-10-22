#ifndef LINSPACE_H
#define LINSPACE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void linspace(double d1, double d2, double n, ::coder::array<double, 2U> &y);

}

#endif
//
// File trailer for linspace.h
//
// [EOF]
//
