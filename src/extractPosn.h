#ifndef EXTRACTPOSN_H
#define EXTRACTPOSN_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
void extractPosn(double a, const double pTarget[2],
                 const coder::array<double, 1U> &posn,
                 const coder::array<double, 1U> &b_time,
                 coder::array<double, 1U> &x_, coder::array<double, 1U> &y_);

#endif
//
// File trailer for extractPosn.h
//
// [EOF]
//
