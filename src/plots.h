#ifndef PLOTS_H
#define PLOTS_H


#include "coder_array.h"
#include "pbPlots.hpp"
#include "supportLib.hpp"
#include <cmath>


class PlotError{
  public:
  void drawPlot(coder::array<double, 1U> &t,coder::array<double, 1U> &x_,coder::array<double, 1U> &y_);
  private:
  vector<double> x_vect, t_vect,y_vect;
};


#endif