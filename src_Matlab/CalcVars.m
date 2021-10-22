function [x_init, time_span] = CalcVars(coordinates,time_params)

% Create and initialize a Parallel Robot object with system parameters
newVars = CalcSysVars(coordinates,time_params);
 
% Get Initial Lengths and Angles
[x_init] = newVars.getInitialVars();

% Get time span
time_span = newVars.getTimeSpan(); 

