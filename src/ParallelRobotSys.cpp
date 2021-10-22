// Include Files
#include "ParallelRobotSys.h"
#include "pinv.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const double y[10]
//                const double u[2]
//                double dy[10]
// Return Type  : void
//
void ParallelRobotSys::dynamics(const double y[10], const double u[2],
                                double dy[10]) const
{
  double b_dy_tmp;
  double c_dy_tmp;
  double dy2_tmp;
  double dy2_tmp_tmp;
  double dy_tmp;
  //  Gives the dynamic relationship between variables - Equations of
  //  motion
  dy2_tmp_tmp = y[4] - y[6];
  dy2_tmp = std::cos(dy2_tmp_tmp);
  dy2_tmp_tmp = std::sin(dy2_tmp_tmp);
  dy[0] = y[1];
  dy_tmp = y[5] * y[5];
  b_dy_tmp = 4.0 * m3;
  c_dy_tmp = (m1 + m2) + b_dy_tmp;
  dy[1] = ((((4.0 * u[0] + 4.0 * u[1] * dy2_tmp) + m1 * y[0] * dy_tmp) +
            m2 * y[0] * dy_tmp) +
           b_dy_tmp * y[0] * dy_tmp) /
          c_dy_tmp;
  dy[2] = y[3];
  dy_tmp = y[7] * y[7];
  dy[3] = ((((4.0 * u[1] + 4.0 * u[0] * dy2_tmp) + m1 * y[2] * dy_tmp) +
            m2 * y[2] * dy_tmp) +
           b_dy_tmp * y[2] * dy_tmp) /
          c_dy_tmp;
  dy[4] = y[5];
  dy[5] =
      -(2.0 *
        (((2.0 * u[1] * dy2_tmp_tmp + m1 * y[1] * y[5]) + m2 * y[1] * y[5]) +
         b_dy_tmp * y[1] * y[5])) /
      (y[0] * c_dy_tmp);
  dy[6] = y[7];
  dy[7] =
      -(2.0 *
        (((m1 * y[3] * y[7] - 2.0 * u[0] * dy2_tmp_tmp) + m2 * y[3] * y[7]) +
         b_dy_tmp * y[3] * y[7])) /
      (y[2] * c_dy_tmp);
  dy[8] = 0.0;
  dy[9] = 0.0;
}

//
// Arguments    : const double y[10]
//                double dy[10]
// Return Type  : void
//
void ParallelRobotSys::ctrl_input(const double y[10], double dy[10]) const
{
  double S[4];
  double b_S[4];
  double u[2];
  double xDot_curr;
  double x_curr;
  double x_curr_tmp;
  double yDot_curr;
  double y_curr;
  double y_curr_tmp;
  //  Assigns the controller to the tasks and then evolves the system
  //  with the control input u generated by the controller
  //  Forward Kinematics to calculate current position of Platform (x,y)
  x_curr_tmp = std::cos(y[4]);
  x_curr = y[0] * x_curr_tmp - a / 2.0;
  y_curr_tmp = std::sin(y[4]);
  y_curr = y[0] * y_curr_tmp;
  //  for efficient error vector(k) calculation. The derivatives need to be
  //  calculated through numerical difference methods
  yDot_curr = y[0] * y[5];
  xDot_curr = y[1] * x_curr_tmp - yDot_curr * y_curr_tmp;
  yDot_curr = y[1] * y_curr_tmp + yDot_curr * x_curr_tmp;
  // Task Space Controller
  S[1] = std::cos(y[6]);
  S[3] = std::sin(y[6]);
  if ((y[9] >= 0.0) && (y_curr >= 0.0)) {
    b_S[0] = x_curr_tmp;
    b_S[1] = y_curr_tmp;
    b_S[2] = S[1];
    b_S[3] = S[3];
    coder::pinv(b_S, S);
    x_curr_tmp = Kpx * (y[8] - x_curr) - Kdx * xDot_curr;
    yDot_curr = Kpy * (y[9] - y_curr) - Kdy * yDot_curr;
    u[0] = S[0] * x_curr_tmp + S[2] * yDot_curr;
    u[1] = S[1] * x_curr_tmp + S[3] * yDot_curr;
  } else if ((y[9] < 0.0) && (y_curr < 0.0)) {
    b_S[0] = x_curr_tmp;
    b_S[1] = y_curr_tmp;
    b_S[2] = S[1];
    b_S[3] = S[3];
    coder::pinv(b_S, S);
    x_curr_tmp = Kpx * (y[8] - x_curr) - Kdx * xDot_curr;
    yDot_curr = -(Kpy * (y[9] - y_curr) - Kpy * yDot_curr);
    u[0] = S[0] * x_curr_tmp + S[2] * yDot_curr;
    u[1] = S[1] * x_curr_tmp + S[3] * yDot_curr;
  } else if ((y_curr >= 0.0) && (y[9] < 0.0)) {
    b_S[0] = x_curr_tmp;
    b_S[1] = y_curr_tmp;
    b_S[2] = S[1];
    b_S[3] = S[3];
    coder::pinv(b_S, S);
    x_curr_tmp = Kpx * (y[8] - x_curr) - Kdx * xDot_curr;
    yDot_curr += Kpy * (y[9] - y_curr);
    u[0] = S[0] * x_curr_tmp + S[2] * yDot_curr;
    u[1] = S[1] * x_curr_tmp + S[3] * yDot_curr;
  } else if ((y_curr <= 0.0) && (y[9] > 0.0)) {
    b_S[0] = x_curr_tmp;
    b_S[1] = y_curr_tmp;
    b_S[2] = S[1];
    b_S[3] = S[3];
    coder::pinv(b_S, S);
    x_curr_tmp = Kpx * (y[8] - x_curr) - Kdx * xDot_curr;
    yDot_curr += -Kpy * (y[9] - y_curr);
    u[0] = S[0] * x_curr_tmp + S[2] * yDot_curr;
    u[1] = S[1] * x_curr_tmp + S[3] * yDot_curr;
  } else {
    u[0] = 0.0;
    u[1] = 0.0;
  }
  dynamics(y, u, dy);
}

//
// Arguments    : double mass1
//                double mass2
//                double mass3
//                double dist_a
// Return Type  : void
//
void ParallelRobotSys::init(double mass1, double mass2, double mass3,
                            double dist_a)
{
  //  Constructor
  m1 = mass1;
  m2 = mass2;
  m3 = mass3;
  a = dist_a;
  Kpx = 5;
  Kpy = 5;
  Kdx = 3;
  Kdy = 3;
}

//
// File trailer for ParallelRobotSys.cpp
//
// [EOF]
//