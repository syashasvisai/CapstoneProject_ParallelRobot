
// Include Files
#include "CalcSysVars.h"
#include "linspace.h"
#include "norm.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Calculating initial length between the actuator joint and the platform joint
// at the starting position
//
// Arguments    : double x_init[10]
// Return Type  : void
//
void CalcSysVars::getInitialVars(double x_init[10]) const
{
  double OB_i[4];
  double Length_init_idx_0;
  double Rot_idx_0;
  double Rot_idx_1;
  double Rot_tmp;
  OB_i[0] = pInitial_[0] - jInitial_[0];
  OB_i[1] = pInitial_[1] - jInitial_[1];
  OB_i[2] = pInitial_[0] - jInitial_[2];
  OB_i[3] = pInitial_[1] - jInitial_[3];
  Rot_tmp = coder::b_norm(*(double(*)[2]) & OB_i[0]);
  Rot_idx_0 = OB_i[0] / Rot_tmp;
  Rot_idx_1 = OB_i[1] / Rot_tmp;
  //  vector / norm (vector)
  Length_init_idx_0 = Rot_tmp;
  //  Gives the length of the Actuator arms
  Rot_tmp = coder::b_norm(*(double(*)[2]) & OB_i[2]);
  //  vector / norm (vector)
  //  Gives the length of the Actuator arms
  x_init[0] = Length_init_idx_0;
  x_init[1] = 0.0;
  x_init[2] = Rot_tmp;
  x_init[3] = 0.0;
  x_init[4] = std::atan2(Rot_idx_1, Rot_idx_0);
  x_init[5] = 0.0;
  x_init[6] = std::atan2(OB_i[3] / Rot_tmp, OB_i[2] / Rot_tmp);
  x_init[7] = 0.0;
  x_init[8] = xTarget_;
  x_init[9] = yTarget_;
}

//
// Arguments    : coder::array<double, 2U> &time_span
// Return Type  : void
//
void CalcSysVars::getTimeSpan(coder::array<double, 2U> &time_span) const
{
  coder::linspace(startTime_, endTime_, (endTime_ - startTime_) / timeSteps_,
                  time_span);
}

//
// Arguments    : const double coordinates[8]
//                const double time_params[3]
// Return Type  : void
//
void CalcSysVars::init(const double coordinates[8], const double time_params[3])
{
  //  Constructor
  pInitial_[0] = coordinates[0];
  pInitial_[1] = coordinates[1];
  jInitial_[0] = coordinates[2];
  jInitial_[1] = coordinates[3];
  jInitial_[2] = coordinates[4];
  jInitial_[3] = coordinates[5];
  xTarget_ = coordinates[6];
  yTarget_ = coordinates[7];
  startTime_ = time_params[0];
  endTime_ = time_params[1];
  timeSteps_ = time_params[2];
}

//
// File trailer for CalcSysVars.cpp
//
// [EOF]
//
