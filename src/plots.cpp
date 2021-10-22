#include "plots.h"
saf
using namespace std;

void PlotError::drawPlot(coder::array<double, 1U> &t,coder::array<double, 1U> &x_,coder::array<double, 1U> &y_){
  
  RGBABitmapImageReference *imageRef1 = CreateRGBABitmapImageReference();
  
  for(int i = 0; i<10000; i++){
    x_vect.emplace_back(x_[i]);
    y_vect.emplace_back(y_[i]);  
    t_vect.emplace_back(t[i]);  
  }
  
  // Error of x coordinate
  DrawScatterPlot(imageRef1, 1600, 900, &t_vect, &x_vect);
  vector<double> *pngData1 = ConvertToPNG(imageRef1->image);
  WriteToFile(pngData1, "x_error_plot.png");
  DeleteImage(imageRef1 -> image); 
  
  RGBABitmapImageReference *imageRef2 = CreateRGBABitmapImageReference();
  
  // Error of y coordinate
  DrawScatterPlot(imageRef2, 1600, 900, &t_vect, &y_vect);
  vector<double> *pngData2 = ConvertToPNG(imageRef2->image);
  WriteToFile(pngData2, "y_error_plot.png");
  DeleteImage(imageRef2 -> image);
}