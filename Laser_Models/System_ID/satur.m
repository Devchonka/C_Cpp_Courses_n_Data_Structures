function OutVector=satur(InVector,lowLim,UpLim)
%satur is an approximation of the saturation of a function  between the values [-1,1]
%The main advantage and purpose of designing this simple yet powerful
%function is to obtain a smooth funtion that has a continous derivative.
%It can be easily adjusted to different lower and upper bounds by alterning
%the value "5" in the formula. Play around with it as you desire and as
%suitable to your application.

OutVector = zeros(size(InVector));

for i  = 1: length(InVector)
 OutVector(i)=(atan(5e3.*InVector(i))-atan(-5e3.*InVector(i)))/(pi);
end
end
 
 
 