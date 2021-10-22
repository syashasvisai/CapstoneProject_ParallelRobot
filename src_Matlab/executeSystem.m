function [t,y,x_,y_] = executeSystem(params,coordinates, time_params)

%   EXECUTESYSTEM - Executes the system equations along with the controller
%   task of moving the platform from initial position to final position

%   3 rigid bodies (1 manipulator platform joint & 2 linear actuators)
%   2 DOF (Planar Mechanism) 6 variable coordinates:
%   - Position of manipulator joint(x,y),
%   - Angle the linear actuators make with the horizontal (phi1,phi2) 
%   - Variable length of the linear actuators (rho1,rho2)
%
% Input arguments:
%   PARAMS = Structure that has fields for system parameters
%   COORDINATES = Contains Initial, Fixed-Joint and Target coordinates
%   TIME_PARAMS = Contains the Start and end times and the time steps for
%   simulation
% 
%   Output arguments:
%   T,Y - Row vectors that contain position vs time data for the parallel
%   robot
 
% Calculate System Variables
[x_init, time_span] = CalcVars(coordinates,time_params);

% Create and initialize a Parallel Robot object with system parameters
myparallelRobot = ParallelRobotSys(params.m1,params.m2,params.m3,params.a);

% Evolve the system
[t,y] = myparallelRobot.evolution(x_init,time_span);

% Extract position of Platform
[x_,y_] = extractPosn(params.a,coordinates(7:8),y(:),t);
