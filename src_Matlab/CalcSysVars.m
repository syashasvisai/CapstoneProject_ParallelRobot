classdef CalcSysVars
    % CALCSYSVARS - A class that calculates the system variables:         
    %   time-span
    %   Initial state vector vars - lengths and angles subtended

    properties (SetAccess = private, GetAccess = protected)
        pInitial_, jInitial_,xTarget_,yTarget_;startTime_,endTime_,timeSteps_;
    end
    
    methods
        % Constructor
        function obj = CalcSysVars(coordinates,time_params)
            obj.pInitial_ = coordinates(1:2);
            obj.jInitial_ = reshape(coordinates(3:6)',[2,2]);
            obj.xTarget_ = coordinates(7);
            obj.yTarget_ = coordinates(8);
            obj.startTime_ = time_params(1);
            obj.endTime_ = time_params(2);
            obj.timeSteps_ = time_params(3);
        end

        function [x_init] = getInitialVars(obj)
            % Calculating initial length between the actuator joint and the platform joint at the starting position
            OB_i = zeros(2,2);
            Rot = zeros(2,2);
            Length_init = zeros(1,2);

            for i=1:2
                OB_i(:,i)=obj.pInitial_'-obj.jInitial_(:,i);
            end
            for i=1:2
                Rot(:,i)=OB_i(:,i)/norm(OB_i(:,i)); % vector / norm (vector)
                Length_init(:,i)=norm(OB_i(:,i)); % Gives the length of the Actuator arms
            end 
            phi_init=[atan2(Rot(2,1),Rot(1,1)) atan2(Rot(2,2),Rot(1,2))];
            x_init = [Length_init(1) 0 Length_init(2) 0 phi_init(1) 0 phi_init(2) 0 obj.xTarget_ obj.yTarget_];
        end

        function time_span = getTimeSpan(obj)
            N = (obj.endTime_ - obj.startTime_)/obj.timeSteps_;
            time_span = linspace(obj.startTime_,obj.endTime_,N);
        end
    end
end