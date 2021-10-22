#ifndef PARALLELROBOTSYS_H
#define PARALLELROBOTSYS_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class ParallelRobotSys {
public:
  void init(double mass1, double mass2, double mass3, double dist_a);
  void ctrl_input(const double y[10], double dy[10]) const;
  void dynamics(const double y[10], const double u[2], double dy[10]) const;

protected:
  double m1;
  double m2;
  double m3;
  double a;
  double Kpx, Kpy, Kdx,Kdy;
  
};

#endif
//
// File trailer for ParallelRobotSys.h
//
// [EOF]
//
