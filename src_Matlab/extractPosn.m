function [x_,y_] = extractPosn(a,pTarget,posn, time)

xCurr_ = posn(1:size(time,1));
phi1_ =  posn(4*size(time,1)+1:5*size(time,1));

x_ = ones(size(time))*pTarget(1)-(xCurr_.*cos(phi1_)-a/2);
y_ = ones(size(time))*pTarget(2)-(xCurr_.*sin(phi1_));
end