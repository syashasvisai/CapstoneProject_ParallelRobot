% System parameters of the 2RPR robot are defined with the structure params
% Fixed and Tuning parameters 
params.a = 2*175;
params.m1 = 1;
params.m2 = 1; 
params.m3 = 1;	

% Tuning parameters
Kpx = 5; Kdx = 1;
Kpy = 5; Kdy = 1;

% Time span
init_t=0; final_t=10; dt=0.001;

% Initial platform coordinates
pInitial=[50 50]; 
% Target platform coordinates
pTarget=[80 80];
% Co-ordinates of the two stationary joints
jInitial=[-params.a/2 params.a/2; 0 0]; 

coordinates = [pInitial, jInitial(:)', pTarget];
time_params = [init_t, final_t, dt];

tic
% Where the magic happens
[t,pos,x_,y_] = executeSystem(params,coordinates,time_params);
time_PD_1 = toc;

%% Plots
figure(1);
subplot(2,1,1)
plot(t,x_,'r-.');
set(gca,'xlim',[0 8]);
title('X error');
xlabel('time');
ylabel('error');
legend('PD','Location','southeast');
legend('boxoff');
grid on
subplot(2,1,2)
plot(t,y_,'r-.')
set(gca,'xlim',[0 8]);
title('Y error');
xlabel('time');
ylabel('error');
legend('PD','Location','southeast');
legend('boxoff');
sgtitle('Position tracking');
grid on
%% Animation
figure(1); hold on;
x1 = pos;
pause(8);
for i=1:length(pos)
     if(mod(i,50)==1)
        clf;
        %x1
        x1_1=x1(i,1);
        x1_2=x1(i,3);
        x1_3=x1(i,5);
        x1_4=x1(i,7);
        x7=x1(i,9);
        x8=x1(i,10);
        p1x_1 = x1_1*cos(x1_3)-params.a/2;
        p1y_1 = x1_1*sin(x1_3);
        p2x_1 = x1_2*cos(x1_4)+params.a/2;
        p2y_1 = x1_2*sin(x1_4);
        px1_1=[-params.a/2 p1x_1];
        py1_1=[0 p1y_1];
        plot(px1_1,py1_1,'r-.') % plot arm 1
        hold on;
        grid on;
        px2_1=[params.a/2 p2x_1];
        py2_1=[0 p2y_1];
        p1 = plot(px2_1,py2_1,'r-.'); % plot arm 2 
        plot(x7,x8,'bx'); % plot target
        plot(pInitial(1),pInitial(2),'ro'); % plot initial point
        plot(-params.a/2,0,'ro',params.a/2,0,'ro')
        legend(p1,'PD')
        axis([-200 200 -200 200]);
        pause(0.001); 
     end
end