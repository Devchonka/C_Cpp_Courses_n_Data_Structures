% PI controller with intergral anti-wind up
%[OutPutVector,ControlAction] = co2controllerClipS_V1(Kp,Ki,InputVector);

function [temp,Drive] = co2controllerClipS_V1(Kp,Ki,Y)

n = length(Y);    % number of samples

Clip = 1e5; % turned off
IntClip=0.1*Clip;

% Initialize arrays
Int=zeros(1,n);
Drive=zeros(1,n);
setPt=mean(Y);
Error=zeros(1,n);


temp=Y';
Error(1) = setPt - (temp(1));


for i = 1:n-1
    CE=1; % [%]

    temp(i) = temp(i)+Drive(i)*CE;

    Error(i) = setPt - temp(i); % error entering the PID controller

    Int(i+1) = Int(i) + Ki*Error(i);

    % Constrain integral
    if (Int(i+1)>IntClip) && (Error(i)>0)
        Int(i+1)=IntClip;
    end
    if (Int(i+1)<-IntClip) && (Error(i+1)<0)
        Int(i+1)=-IntClip;
    end

    % Constrain drive
    Drive(i+1)  = Kp*Error(i) + Int(i+1);
    if (Drive(i+1)>Clip)
        Drive(i+1)=Clip;
    end
    if (Drive(i+1)<-Clip)
        Drive(i+1)=-Clip;
    end


end
% set(0,'defaultlinelinewidth',1.5)
% figure(1);clf; plot(Error,'g');hold on;plot(Kp*Error,'r');
% % hold on; plot(temp,'--k');
% grid on
% legend ('Error','Kp Drive','Ki Drive',0)
% title('Anti-Wind-up Control')
% xlabel('idx'); ylabel('');
% pause
end