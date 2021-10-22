// Include Files
#include "CalcVars.h"
#include "CalcSysVars.h"
#include "coder_array.h"

// Function Definitions
//
// Create and initialize a Parallel Robot object with system parameters
//
// Arguments    : const double coordinates[8]
//                const double time_params[3]
//                double x_init[10]
//                coder::array<double, 2U> &time_span
// Return Type  : void
//
void CalcVars(const double coordinates[8], const double time_params[3],
              double x_init[10], coder::array<double, 2U> &time_span)
{
  CalcSysVars newVars;
  newVars.init(coordinates, time_params);
  //  Get Initial Lengths and Angles
  newVars.getInitialVars(x_init);
  //  Get time span
  newVars.getTimeSpan(time_span);
}

//
// File trailer for CalcVars.cpp
//
// [EOF]
//
