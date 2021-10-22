// Include Files
#include "extractPosn.h"
#include "cos.h"
#include "sin.h"
#include "coder_array.h"

// Function Declarations
static void binary_expand_op(coder::array<double, 1U> &x_,
                             const double pTarget[2], const unsigned int r[2],
                             const coder::array<double, 1U> &posn,
                             const coder::array<double, 1U> &b_time, double a);

static void binary_expand_op(coder::array<double, 1U> &y_,
                             const double pTarget[2], const unsigned int r[2],
                             const coder::array<double, 1U> &posn,
                             const coder::array<double, 1U> &b_time);

// Function Definitions
//
// Arguments    : coder::array<double, 1U> &x_
//                const double pTarget[2]
//                const unsigned int r[2]
//                const coder::array<double, 1U> &posn
//                const coder::array<double, 1U> &b_time
//                double a
// Return Type  : void
//
static void binary_expand_op(coder::array<double, 1U> &x_,
                             const double pTarget[2], const unsigned int r[2],
                             const coder::array<double, 1U> &posn,
                             const coder::array<double, 1U> &b_time, double a)
{
  coder::array<double, 1U> b_pTarget;
  double b_a;
  int i;
  int i1;
  int stride_1_0;
  int stride_2_0;
  int unnamed_idx_0;
  unnamed_idx_0 = static_cast<int>(r[0]);
  b_a = a / 2.0;
  i = b_time.size(0);
  if (x_.size(0) == 1) {
    i1 = i;
  } else {
    i1 = x_.size(0);
  }
  if (i1 == 1) {
    i1 = unnamed_idx_0;
  } else if (x_.size(0) == 1) {
    i1 = i;
  } else {
    i1 = x_.size(0);
  }
  b_pTarget.set_size(i1);
  stride_1_0 = (i != 1);
  stride_2_0 = (x_.size(0) != 1);
  if (x_.size(0) == 1) {
    i1 = i;
  } else {
    i1 = x_.size(0);
  }
  if (i1 != 1) {
    if (x_.size(0) == 1) {
      unnamed_idx_0 = i;
    } else {
      unnamed_idx_0 = x_.size(0);
    }
  }
  for (i = 0; i < unnamed_idx_0; i++) {
    b_pTarget[i] =
        pTarget[0] - (posn[i * stride_1_0] * x_[i * stride_2_0] - b_a);
  }
  x_.set_size(b_pTarget.size(0));
  unnamed_idx_0 = b_pTarget.size(0);
  for (i = 0; i < unnamed_idx_0; i++) {
    x_[i] = b_pTarget[i];
  }
}

//
// Arguments    : coder::array<double, 1U> &y_
//                const double pTarget[2]
//                const unsigned int r[2]
//                const coder::array<double, 1U> &posn
//                const coder::array<double, 1U> &b_time
// Return Type  : void
//
static void binary_expand_op(coder::array<double, 1U> &y_,
                             const double pTarget[2], const unsigned int r[2],
                             const coder::array<double, 1U> &posn,
                             const coder::array<double, 1U> &b_time)
{
  coder::array<double, 1U> b_pTarget;
  int i;
  int i1;
  int stride_1_0;
  int stride_2_0;
  int unnamed_idx_0;
  unnamed_idx_0 = static_cast<int>(r[0]);
  i = b_time.size(0);
  if (y_.size(0) == 1) {
    i1 = i;
  } else {
    i1 = y_.size(0);
  }
  if (i1 == 1) {
    i1 = unnamed_idx_0;
  } else if (y_.size(0) == 1) {
    i1 = i;
  } else {
    i1 = y_.size(0);
  }
  b_pTarget.set_size(i1);
  stride_1_0 = (i != 1);
  stride_2_0 = (y_.size(0) != 1);
  if (y_.size(0) == 1) {
    i1 = i;
  } else {
    i1 = y_.size(0);
  }
  if (i1 != 1) {
    if (y_.size(0) == 1) {
      unnamed_idx_0 = i;
    } else {
      unnamed_idx_0 = y_.size(0);
    }
  }
  for (i = 0; i < unnamed_idx_0; i++) {
    b_pTarget[i] = pTarget[1] - posn[i * stride_1_0] * y_[i * stride_2_0];
  }
  y_.set_size(b_pTarget.size(0));
  unnamed_idx_0 = b_pTarget.size(0);
  for (i = 0; i < unnamed_idx_0; i++) {
    y_[i] = b_pTarget[i];
  }
}

//
// Arguments    : double a
//                const double pTarget[2]
//                const coder::array<double, 1U> &posn
//                const coder::array<double, 1U> &b_time
//                coder::array<double, 1U> &x_
//                coder::array<double, 1U> &y_
// Return Type  : void
//
void extractPosn(double a, const double pTarget[2],
                 const coder::array<double, 1U> &posn,
                 const coder::array<double, 1U> &b_time,
                 coder::array<double, 1U> &x_, coder::array<double, 1U> &y_)
{
  double b_a;
  double d;
  unsigned int uv[2];
  int i;
  int i1;
  int loop_ub;
  b_a = 4.0 * static_cast<double>(b_time.size(0)) + 1.0;
  d = 5.0 * static_cast<double>(b_time.size(0));
  if (b_a > d) {
    i = 0;
    i1 = 0;
  } else {
    i = static_cast<int>(b_a) - 1;
    i1 = static_cast<int>(d);
  }
  uv[0] = static_cast<unsigned int>(b_time.size(0));
  uv[1] = 1U;
  loop_ub = i1 - i;
  x_.set_size(loop_ub);
  for (i1 = 0; i1 < loop_ub; i1++) {
    x_[i1] = posn[i + i1];
  }
  coder::b_cos(x_);
  if (b_time.size(0) == 1) {
    i1 = x_.size(0);
  } else {
    i1 = b_time.size(0);
  }
  if ((b_time.size(0) == x_.size(0)) && (b_time.size(0) == i1)) {
    int b_loop_ub;
    b_a = a / 2.0;
    x_.set_size(b_time.size(0));
    b_loop_ub = b_time.size(0);
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      x_[i1] = pTarget[0] - (posn[i1] * x_[i1] - b_a);
    }
  } else {
    binary_expand_op(x_, pTarget, uv, posn, b_time, a);
  }
  uv[0] = static_cast<unsigned int>(b_time.size(0));
  uv[1] = 1U;
  y_.set_size(loop_ub);
  for (i1 = 0; i1 < loop_ub; i1++) {
    y_[i1] = posn[i + i1];
  }
  coder::b_sin(y_);
  if (b_time.size(0) == 1) {
    i = y_.size(0);
  } else {
    i = b_time.size(0);
  }
  if ((b_time.size(0) == y_.size(0)) && (b_time.size(0) == i)) {
    y_.set_size(b_time.size(0));
    loop_ub = b_time.size(0);
    for (i = 0; i < loop_ub; i++) {
      y_[i] = pTarget[1] - posn[i] * y_[i];
    }
  } else {
    binary_expand_op(y_, pTarget, uv, posn, b_time);
  }
}

//
// File trailer for extractPosn.cpp
//
// [EOF]
//
