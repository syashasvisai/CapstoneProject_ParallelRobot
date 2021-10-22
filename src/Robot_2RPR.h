#ifndef ROBOT_2RPR_H
#define ROBOT_2RPR_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct struct0_T;

// Type Definitions
class Robot_2RPR {
public:
  Robot_2RPR();
  ~Robot_2RPR();
  void executeSystem(const struct0_T *params, const double coordinates[8],
                     const double time_params[3], coder::array<double, 1U> &t,
                     coder::array<double, 2U> &y, coder::array<double, 1U> &x_,
                     coder::array<double, 1U> &y_);
};

#endif
//
// File trailer for Robot_2RPR.h
//
// [EOF]
//
