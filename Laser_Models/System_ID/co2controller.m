% PID controller for CO2

% y= actual predicted measurement (red curve)
% idx= index

function temp = co2controller(y)

Kp = 1;             % proportional term Kp
Ki = 0.01;           % Integral term Ki
Kd = 0;           % derivative term Kd
dt = 1/50000;          % sampling time
n = length(y);    % number of samples

% Initialize arrays 
Prop=zeros(1,n); Der=zeros(1,n);
Int=zeros(1,n); I=zeros(1,n);
Drive=zeros(1,n);
temp =zeros(1,n);
% FeedBack=zeros(1,n);
setPt=mean(y);
Error=zeros(1,n);


temp(1)=y(1);


for i = 1:n-1
    CE=1;
    Error(i+1) = setPt - temp(i+1); % error entering the PID controller
    
    Prop(i+1) = Error(i+1);% error of proportional term
    Der(i+1)  = (Error(i+1) - Error(i)) /dt; % derivative of the error
    Int(i+1)  = (Error(i+1) + Error(i))*dt/2; % integration of the error
    I(i+1)    = sum(Int); % the sum of the integration of the error
    
    Drive(i+1)  = Kp*Prop(i+1) + Ki*I(i+1)+ Kd*Der(i); % the three PID terms
    
    temp(i+1) = Drive(i+1)*CE;
%     temp(i+1:end) = Drive(i+1)*CE;
    
end

end