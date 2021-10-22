#ifndef CALCVARS_H
#define CALCVARS_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
void CalcVars(const double coordinates[8], const double time_params[3],
              double x_init[10], coder::array<double, 2U> &time_span);

#endif
//
// File trailer for CalcVars.h
//
// [EOF]
//
