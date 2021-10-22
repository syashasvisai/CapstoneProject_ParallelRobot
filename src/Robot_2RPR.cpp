//    3 rigid bodies (1 manipulator platform joint & 2 linear actuators)
  //    2 DOF (Planar Mechanism) 6 variable coordinates:
  //    - Position of manipulator joint(x,y),
  //    - Angle the linear actuators make with the horizontal (phi1,phi2)
  //    - Variable length of the linear actuators (rho1,rho2)
  //
  //  Input arguments:
  //    PARAMS = Structure that has fields for system parameters
  //    COORDINATES = Contains Initial, Fixed-Joint and Target coordinates
  //    TIME_PARAMS = Contains the Start and end times and the time steps for
  //    simulation
  //
  //    Output arguments:
  //    T,Y - Row vectors that contain position vs time data for the parallel
  //    robot//


// Include Files
#include "Robot_2RPR.h"
#include "CalcVars.h"
#include "ParallelRobotSys.h"
#include "anonymous_function.h"
#include "executeSystem_internal_types.h"
#include "executeSystem_types.h"
#include "extractPosn.h"
#include "ode45.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
Robot_2RPR::Robot_2RPR()
{
}

//
// Arguments    : void
// Return Type  : void
//
Robot_2RPR::~Robot_2RPR()
{
  // (no terminate code required)
}


// EXECUTESYSTEM - Executes the system equations along with the controller
//    task of moving the platform from initial position to final position
// Arguments    : const struct0_T *params
//                const double coordinates[8]
//                const double time_params[3]
//                coder::array<double, 1U> &t
//                coder::array<double, 2U> &y
//                coder::array<double, 1U> &x_
//                coder::array<double, 1U> &y_
// Return Type  : void
//
void Robot_2RPR::executeSystem(const struct0_T *params,
                               const double coordinates[8],
                               const double time_params[3],
                               coder::array<double, 1U> &t,
                               coder::array<double, 2U> &y,
                               coder::array<double, 1U> &x_,
                               coder::array<double, 1U> &y_)
{
  coder::anonymous_function b_this;
  coder::array<double, 2U> time_span;
  coder::array<double, 1U> c_y;
  double x_init[10];
  int b_y;
  
  //  Calculate System Variables
  CalcVars(coordinates, time_params, x_init, time_span);
  //  Create and initialize a Parallel Robot object with system parameters
  b_this.workspace.obj.init(params->m1, params->m2, params->m3, params->a);
  //  Evolve the system
  //  Evolves the system of equations with respect to the control input
  coder::ode45(b_this, time_span, x_init, t, y);
  //  Extract position of Platform
  b_y = y.size(0) * 10;
  c_y = y.reshape(b_y);
  extractPosn(params->a, *(double(*)[2]) & coordinates[6], c_y, t, x_, y_);
}

//
// File trailer for Robot_2RPR.cpp
//
// [EOF]
//
