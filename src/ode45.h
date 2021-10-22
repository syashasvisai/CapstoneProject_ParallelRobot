#ifndef ODE45_H
#define ODE45_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class anonymous_function;

}

// Function Declarations
namespace coder {
void ode45(const anonymous_function ode,
           const ::coder::array<double, 2U> &tspan, const double b_y0[10],
           ::coder::array<double, 1U> &varargout_1,
           ::coder::array<double, 2U> &varargout_2);

}

#endif
//
// File trailer for ode45.h
//
// [EOF]
//
