// Include Files
#include "main_PR.h"
#include "Robot_2RPR.h"
#include "executeSystem_types.h"
#include "coder_array.h"

using namespace std;


// Function Declarations
static void main_executeSystem(Robot_2RPR *instancePtr);

static void main_executeSystem(Robot_2RPR *instancePtr)
{
  coder::array<double, 1U> xPlatform_;
  coder::array<double, 2U> odeResult;
  coder::array<double, 1U> yPlatform_;
  coder::array<double, 1U> t;
  struct0_T r;
  double coordinates[8];
  double time_params[3];
  // Initialize function 'executeSystem' input arguments.
  // Initialize function input argument 'params'.
  // Initialize function input argument 'coordinates'.
  // Initialize function input argument 'time_params'.
  // Call the entry-point 'executeSystem'.
  r.m1 = 1;
  r.m2 = 1;
  r.m3 = 1;
  r.a = 2*175;

  time_params[0] = 0; // init_time
  time_params[1]= 10; //final_time
  time_params[2] = 0.001; // time_step

  coordinates[0] = 50; // x_initial (platform)
  coordinates[1] = 50; // y_initial
  coordinates[2] = -r.a/2; // joint_1 x coordinate
  coordinates[3] = 0; // joint_1 y coordinate
  coordinates[4] = r.a/2; // joint_2 x coordinate
  coordinates[5] = 0; // joint_2 y coordinate
  coordinates[6] = 80; // x_target (platform)
  coordinates[7] = 80;// y_target


  instancePtr->executeSystem(&r, coordinates, time_params, t, odeResult, xPlatform_, yPlatform_);
  
  // Plot position error in x coordinate to compare with Matlab results
  vector<double> x_vect, t_vect,y_vect;
  for(int i = 0; i<10000; i++){
    x_vect.emplace_back(xPlatform_[i]);
  	t_vect.emplace_back(t[i]);  
  }
  
  cout<<"Pick and place task executed. Please compare the error plots from Matlab to the x_error_plot.png in the build folder for validation"<<"\n";
  
  // Using pbplots - https://github.com/InductiveComputerScience/pbPlots.git
 RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
  
 // Error of x coordinate
  DrawScatterPlot(imageRef, 1600, 900, &t_vect, &x_vect);
  vector<double> *pngData = ConvertToPNG(imageRef->image);
  WriteToFile(pngData, "x_error_plot.png");
  DeleteImage(imageRef -> image);
}

//
// Arguments    : int argc
//                char **argv
// Return Type  : int
//
int main(int, char **)
{
  Robot_2RPR classInstance;
  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_executeSystem(&classInstance);
  
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
