// Include Files
#include "ode45.h"
#include "ParallelRobotSys.h"
#include "anonymous_function.h"
#include "executeSystem_internal_types.h"
#include "coder_array.h"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <math.h>

// Function Declarations
static int div_nde_s32_floor(int numerator);

// Function Definitions
//
// Arguments    : int numerator
// Return Type  : int
//
static int div_nde_s32_floor(int numerator)
{
  int b_numerator;
  if ((numerator < 0) && (numerator % 10 != 0)) {
    b_numerator = -1;
  } else {
    b_numerator = 0;
  }
  return numerator / 10 + b_numerator;
}

//
// Arguments    : const anonymous_function ode
//                const ::coder::array<double, 2U> &tspan
//                const double b_y0[10]
//                ::coder::array<double, 1U> &varargout_1
//                ::coder::array<double, 2U> &varargout_2
// Return Type  : void
//
namespace coder {
void ode45(const anonymous_function ode,
           const ::coder::array<double, 2U> &tspan, const double b_y0[10],
           ::coder::array<double, 1U> &varargout_1,
           ::coder::array<double, 2U> &varargout_2)
{
  static const double x[21]{0.2,
                            0.075,
                            0.225,
                            0.97777777777777775,
                            -3.7333333333333334,
                            3.5555555555555554,
                            2.9525986892242035,
                            -11.595793324188385,
                            9.8228928516994358,
                            -0.29080932784636487,
                            2.8462752525252526,
                            -10.757575757575758,
                            8.9064227177434727,
                            0.27840909090909088,
                            -0.2735313036020583,
                            0.091145833333333329,
                            0.0,
                            0.44923629829290207,
                            0.65104166666666663,
                            -0.322376179245283,
                            0.13095238095238096};
  static const double b[7]{0.0012326388888888888,
                           0.0,
                           -0.0042527702905061394,
                           0.036979166666666667,
                           -0.05086379716981132,
                           0.0419047619047619,
                           -0.025};
  static const double b_b[7]{-2.859375,
                             0.0,
                             4.0431266846361185,
                             -3.90625,
                             2.7939268867924527,
                             -1.5714285714285714,
                             1.5};
  static const double c_b[7]{3.0833333333333335,
                             0.0,
                             -6.2893081761006293,
                             10.416666666666666,
                             -6.8773584905660377,
                             3.6666666666666665,
                             -4.0};
  static const double d_b[7]{-1.1328125,
                             0.0,
                             2.6954177897574123,
                             -5.859375,
                             3.7610554245283021,
                             -1.9642857142857142,
                             2.5};
  array<double, 2U> tout;
  array<double, 2U> yout;
  double f[70];
  double f0[10];
  double y[10];
  double ynew[10];
  double absh;
  double absx;
  double d2;
  double hmax;
  double t;
  double tdir;
  double tfinal;
  double twidth;
  int Bcolidx;
  int b_k;
  int exponent;
  int i;
  int k;
  int next;
  int nnxt;
  int nout;
  boolean_T Done;
  boolean_T MinStepExit;
  tfinal = tspan[tspan.size(1) - 1];
  ode.workspace.obj.ctrl_input(b_y0, f0);
  tout.set_size(1, tspan.size(1));
  Bcolidx = tspan.size(1);
  for (i = 0; i < Bcolidx; i++) {
    tout[i] = 0.0;
  }
  yout.set_size(10, tspan.size(1));
  Bcolidx = 10 * tspan.size(1);
  for (i = 0; i < Bcolidx; i++) {
    yout[i] = 0.0;
  }
  nout = 1;
  tout[0] = tspan[0];
  for (i = 0; i < 10; i++) {
    yout[i] = b_y0[i];
  }
  twidth = std::abs(tspan[tspan.size(1) - 1] - tspan[0]);
  absx = std::abs(tspan[0]);
  hmax = std::fmin(
      twidth,
      std::fmax(0.1 * twidth,
                3.5527136788005009E-15 *
                    std::fmax(absx, std::abs(tspan[tspan.size(1) - 1]))));
  if (absx <= 2.2250738585072014E-308) {
    d2 = 4.94065645841247E-324;
  } else {
    frexp(absx, &nnxt);
    d2 = std::ldexp(1.0, nnxt - 53);
  }
  absh = std::fmin(hmax, std::abs(tspan[1] - tspan[0]));
  twidth = 0.0;
  for (k = 0; k < 10; k++) {
    absx = std::abs(f0[k] / std::fmax(std::abs(b_y0[k]), 0.001));
    if (absx > twidth) {
      twidth = absx;
    }
  }
  twidth /= 0.20095091452076641;
  if (absh * twidth > 1.0) {
    absh = 1.0 / twidth;
  }
  absh = std::fmax(absh, 16.0 * d2);
  t = tspan[0];
  std::copy(&b_y0[0], &b_y0[10], &y[0]);
  std::memset(&f[0], 0, 70U * sizeof(double));
  std::copy(&f0[0], &f0[10], &f[0]);
  tdir = tspan[tspan.size(1) - 1] - tspan[0];
  if (tdir < 0.0) {
    tdir = -1.0;
  } else if (tdir > 0.0) {
    tdir = 1.0;
  }
  next = 0;
  MinStepExit = false;
  Done = false;
  int exitg1;
  do {
    double d;
    double err;
    double h;
    double hmin;
    double mxerr;
    double tnew;
    boolean_T NoFailedAttempts;
    exitg1 = 0;
    absx = std::abs(t);
    if (absx <= 2.2250738585072014E-308) {
      d2 = 4.94065645841247E-324;
    } else {
      frexp(absx, &exponent);
      d2 = std::ldexp(1.0, exponent - 53);
    }
    hmin = 16.0 * d2;
    absh = std::fmin(hmax, std::fmax(hmin, absh));
    h = tdir * absh;
    if (1.1 * absh >= std::abs(tfinal - t)) {
      h = tfinal - t;
      absh = std::abs(h);
      Done = true;
    }
    NoFailedAttempts = true;
    int exitg2;
    do {
      int ia;
      int iac;
      exitg2 = 0;
      Bcolidx = 0;
      for (k = 0; k < 5; k++) {
        Bcolidx += k;
        std::copy(&y[0], &y[10], &f0[0]);
        if (h != 0.0) {
          i = 10 * k + 1;
          for (iac = 1; iac <= i; iac += 10) {
            twidth = h * x[Bcolidx + div_nde_s32_floor(iac - 1)];
            b_k = iac + 9;
            for (ia = iac; ia <= b_k; ia++) {
              nnxt = ia - iac;
              f0[nnxt] += f[ia - 1] * twidth;
            }
          }
        }
        ode.workspace.obj.ctrl_input(f0, *(double(*)[10]) & f[10 * (k + 1)]);
      }
      tnew = t + h;
      std::copy(&y[0], &y[10], &ynew[0]);
      if (h != 0.0) {
        for (iac = 0; iac <= 50; iac += 10) {
          twidth = h * x[(Bcolidx + div_nde_s32_floor(iac)) + 5];
          i = iac + 10;
          for (ia = iac + 1; ia <= i; ia++) {
            nnxt = (ia - iac) - 1;
            ynew[nnxt] += f[ia - 1] * twidth;
          }
        }
      }
      ode.workspace.obj.ctrl_input(ynew, *(double(*)[10]) & f[60]);
      for (i = 0; i < 10; i++) {
        d = 0.0;
        for (b_k = 0; b_k < 7; b_k++) {
          d += f[i + 10 * b_k] * b[b_k];
        }
        f0[i] = d;
      }
      if (Done) {
        tnew = tfinal;
      }
      h = tnew - t;
      mxerr = 0.0;
      for (k = 0; k < 10; k++) {
        twidth = std::abs(f0[k]);
        absx = std::abs(y[k]);
        d2 = std::abs(ynew[k]);
        if (absx > d2) {
          if (absx > 0.001) {
            twidth /= absx;
          } else {
            twidth /= 0.001;
          }
        } else if (d2 > 0.001) {
          twidth /= d2;
        } else {
          twidth /= 0.001;
        }
        if (twidth > mxerr) {
          mxerr = twidth;
        }
      }
      err = absh * mxerr;
      if (err > 0.001) {
        if (absh <= hmin) {
          MinStepExit = true;
          exitg2 = 1;
        } else {
          if (NoFailedAttempts) {
            NoFailedAttempts = false;
            absh = std::fmax(
                hmin, absh * std::fmax(0.1, 0.8 * std::pow(0.001 / err, 0.2)));
          } else {
            absh = std::fmax(hmin, 0.5 * absh);
          }
          h = tdir * absh;
          Done = false;
        }
      } else {
        exitg2 = 1;
      }
    } while (exitg2 == 0);
    if (MinStepExit) {
      exitg1 = 1;
    } else {
      nnxt = next;
      while ((nnxt + 2 <= tspan.size(1)) &&
             (tdir * (tnew - tspan[nnxt + 1]) >= 0.0)) {
        nnxt++;
      }
      Bcolidx = nnxt - next;
      if (Bcolidx > 0) {
        for (k = next + 2; k <= nnxt; k++) {
          d = tspan[k - 1];
          tout[k - 1] = d;
          twidth = (d - t) / h;
          for (b_k = 0; b_k < 10; b_k++) {
            d = 0.0;
            absx = 0.0;
            d2 = 0.0;
            for (i = 0; i < 7; i++) {
              mxerr = f[b_k + 10 * i];
              d += mxerr * (h * b_b[i]);
              absx += mxerr * (h * c_b[i]);
              d2 += mxerr * (h * d_b[i]);
            }
            yout[b_k + 10 * (k - 1)] =
                (((d2 * twidth + absx) * twidth + d) * twidth + f[b_k] * h) *
                    twidth +
                y[b_k];
          }
        }
        tout[nnxt] = tspan[nnxt];
        if (tspan[nnxt] == tnew) {
          for (i = 0; i < 10; i++) {
            yout[i + 10 * nnxt] = ynew[i];
          }
        } else {
          twidth = (tspan[nnxt] - t) / h;
          for (k = 0; k < 10; k++) {
            d = 0.0;
            absx = 0.0;
            d2 = 0.0;
            for (i = 0; i < 7; i++) {
              mxerr = f[k + 10 * i];
              d += mxerr * (h * b_b[i]);
              absx += mxerr * (h * c_b[i]);
              d2 += mxerr * (h * d_b[i]);
            }
            yout[k + 10 * nnxt] =
                (((d2 * twidth + absx) * twidth + d) * twidth + f[k] * h) *
                    twidth +
                y[k];
          }
        }
        nout += Bcolidx;
        next = nnxt;
      }
      if (Done) {
        exitg1 = 1;
      } else {
        if (NoFailedAttempts) {
          twidth = 1.25 * std::pow(err / 0.001, 0.2);
          if (twidth > 0.2) {
            absh /= twidth;
          } else {
            absh *= 5.0;
          }
        }
        t = tnew;
        for (Bcolidx = 0; Bcolidx < 10; Bcolidx++) {
          y[Bcolidx] = ynew[Bcolidx];
          f[Bcolidx] = f[Bcolidx + 60];
        }
      }
    }
  } while (exitg1 == 0);
  varargout_1.set_size(nout);
  for (i = 0; i < nout; i++) {
    varargout_1[i] = tout[i];
  }
  varargout_2.set_size(nout, 10);
  for (i = 0; i < 10; i++) {
    for (b_k = 0; b_k < nout; b_k++) {
      varargout_2[b_k + varargout_2.size(0) * i] = yout[i + 10 * b_k];
    }
  }
}

} // namespace coder

//
// File trailer for ode45.cpp
//
// [EOF]
//
