
#ifndef CALCSYSVARS_H
#define CALCSYSVARS_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class CalcSysVars {
public:
  void init(const double coordinates[8], const double time_params[3]);
  void getInitialVars(double x_init[10]) const;
  void getTimeSpan(coder::array<double, 2U> &time_span) const;

protected:
  double pInitial_[2];
  double jInitial_[4];
  double xTarget_;
  double yTarget_;
  double startTime_;
  double endTime_;
  double timeSteps_;
};

#endif
//
// File trailer for CalcSysVars.h
//
// [EOF]
//
