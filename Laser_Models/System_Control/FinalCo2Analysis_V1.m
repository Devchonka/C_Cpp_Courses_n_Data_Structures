clear; close all;clc
% delete('C:\Elena\CO2Control\MattVectors')
% delete('C:\Elena\CO2Control\Matt')
pathname = 'C:\Documents and Settings\L503763\Desktop\yelena\matlab_data';
Kp = 0.5;
Ki = 0.9; 

%% On Droplet
filename = '20130618_105343_RT02_000_seedOpen_TruOn_PA1On_PA23On_DropOn.mat';
% filename = '20130617_223431_RT02_000_seedOpen_TruOn_PA1On_PA23On_DropOn.mat';
on = load([pathname '\' filename]);
on.t_ = on.t - on.t(1);

% identify burst boundaries
if ~isfield(on,'ECburstIndex')
    on.ECburstIndex = zeros(length(on.burstStartIdx),1);
    idst = find(on.burstStartIdx == 1);
    for ss = 2:length(idst);
        on.ECburstIndex(idst(ss-1):idst(ss)-1) = ss;
    end
    on.ECburstIndex(idst(length(idst)):end) = length(idst);
end
% identify burst boundaries
bd = unique(on.ECburstIndex);
bd = bd(2:end-1); 
% get on signals
onCO2 = bitget(on.ECmiscellaneousStatus,5); % RF on
% onDrop = circshift(bitget(on.ECmiscellaneousStatus,22),[2,0]); % on droplet synched w/ EUV
holdOff = 500;

% PSD resolution 
res = 2^13;

fs = mean(1./diff(on.t_));
% data initialization
onTime = [];
onEuv = [];
onEuvUC = [];
onCo2 = [];
onCo2UC = [];
DriveOn=[];
onCe = [];
onEuvC = [];
onSeuv = zeros(res/2+1,length(bd));
onSco2 = zeros(res/2+1,length(bd));
onSce = zeros(res/2+1,length(bd));

count = [];
for kk = 1:10% length(bd);
    count = [count, kk];
    % index pulses in burst & count ensamble average
    idx = find(on.ECburstIndex == bd(kk) & onCO2 == 1);
    %idx = find(on.ECburstIndex == bd(kk) & onCO2 == 1 & onDrop == 1);
    idx = idx(holdOff+1:end);
    
    % Time Domain
    onTime = [onTime; on.t_(idx)];
    onEuv = [onEuv; on.ECeuvValue(idx)];
    onEuvUC = [onEuvUC; on.ECeuvValue(idx)];
  
    temp1=on.ECpem1Value(idx)+on.ECpem2Value(idx);
    onCo2UC= [onCo2UC; temp1];
     % On-Droplet Controller Here
%          [temp1a,DriveOnNew] = co2controller(temp1);
    [temp1a,DriveOnNew] = co2controllerClipS_V1(Kp,Ki,temp1);
    temp1a=temp1a';
    DriveOnNew=DriveOnNew';

    DriveOn=[DriveOn;DriveOnNew]; 
    onCo2 = [onCo2; temp1a];
    onCe = [onCe; on.ECeuvValue(idx)./(0.26*0.92*(on.ECpem1Value(idx)+on.ECpem2Value(idx)))*100];
    onCeMean=mean(on.ECeuvValue(idx)./(0.26*0.92*(on.ECpem1Value(idx)+on.ECpem2Value(idx)))*100);
    onEuvC = [onEuvC; (0.26*0.92*(temp1a)) .* onCeMean / 100];
    
    % PSDs
    [temp,onf] = PsdLite(onEuvC,res,fs);
    onSeuv(:,kk) = temp;
    [temp,onf] = PsdLite(onEuvUC,res,fs);
    onSeuvUC(:,kk) = temp;
        
    
    [temp,onf] = PsdLite(onCo2,res,fs);
    onSco2(:,kk) = temp;
    [temp,onf] = PsdLite(onCo2UC,res,fs);
    onSco2UC(:,kk) = temp;
    
    [temp,onf] = PsdLite(DriveOn,res,fs);
    DriveOnPsd(:,kk) = temp;
    
    [temp,onf] = PsdLite(onCe,res,fs);
    onSce(:,kk) = temp;
end
onCeMean = mean(onCe);
onCo2Mean = mean(onCo2);

clear on

%% Off Droplet Plots
filename = '20130618_105929_RT02_000_seedOpen_TruOn_PA1On_PA23On_DropOff.mat';
% filename = '20130617_223248_RT02_000_seedOpen_TruOn_PA1On_PA23On_DropOff.mat';
off = load([pathname '\' filename]);
off.t_ = off.t - off.t(1);

% identify burst boundaries
if ~isfield(off,'ECburstIndex')
    off.ECburstIndex = zeros(length(off.burstStartIdx),1);
    idst = find(off.burstStartIdx == 1);
    for ss = 2:length(idst);
        off.ECburstIndex(idst(ss-1):idst(ss)-1) = ss;
    end
    off.ECburstIndex(idst(length(idst)):end) = length(idst);
end
% identify burst boundaries
bd = unique(off.ECburstIndex);
bd = bd(2:end-1); 
% get on signals
onCO2 = bitget(off.ECmiscellaneousStatus,5); % RF on
onDrop = bitget(off.ECmiscellaneousStatus,22)+2; % on droplet synched w/ EUV
holdOff = 500;

% PSD resolution 
res = 2^13;

fs = mean(1./diff(off.t_));
% data initialization
offTime = [];
offCo2 = [];
offSco2 = zeros(res/2+1,length(bd));
simEuv = [];
simSeuv = zeros(res/2+1,length(bd));
adjCo2 = [];
adjCo2UC= [];
DriveOff=[];
adjSco2 = zeros(res/2+1,length(bd));
adjSco2UC = zeros(res/2+1,length(bd));
adjEuv = [];
DriveOff=[];
adjEuvUC=[];
adjSeuv = zeros(res/2+1,length(bd));
adjSeuvUC = zeros(res/2+1,length(bd));

count = [];
for kk = 1:10% length(bd);
 
    count = [count, kk];
    % index pulses in burst & count ensamble average
    idx = find(off.ECburstIndex == bd(kk) & onCO2 == 1);
    %idx = find(off.ECburstIndex == bd(kk) & onCO2 == 1 & onDrop == 0);
    idx = idx(holdOff+1:end);
    
    % Time Domain
    offTime = [offTime; off.t_(idx)];
    temp = off.ECpem1Value(idx) + off.ECpem2Value(idx);
    offCo2 = [offCo2; temp];
    simEuv = [simEuv; (0.26*0.92*(temp)) .* onCeMean / 100];
    
    % PSDs
    [temp,offf] = PsdLite(offCo2,res,fs);
    offSco2(:,kk) = temp;
    [temp,offf] = PsdLite(simEuv,res,fs);
    simSeuv(:,kk) = temp;
%     
%     % Adjustments
%     rvCo2 = 1.4*randn(length(idx),1); % mJ of CO2
%     tempAdj = 8 * (off.ECpem1Value(idx) + off.ECpem2Value(idx)) - 2600  + rvCo2;
     tempUC = (off.ECpem1Value(idx) + off.ECpem2Value(idx));
     adjCo2UC = [adjCo2UC; tempUC];
     
         % Off-Droplet Controller Here
%      [temp,DriveOffNew]= co2controller(tempAdj);
     [temp,DriveOffNew]= co2controllerClipS_V1(Kp,Ki,tempUC);
     temp=temp';
     DriveOffNew=DriveOffNew';
    
    adjCo2 = [adjCo2; temp];
    DriveOff=[DriveOff;DriveOffNew];
    adjEuvUC = [adjEuvUC; (0.26*0.92*(tempUC)) .* onCeMean / 100];
    adjEuv = [adjEuv; (0.26*0.92*(temp)) .* onCeMean / 100];
    
    % Adjusted PSDs
    [temp,offf] = PsdLite(adjCo2,res,fs);
    adjSco2(:,kk) = temp;
    [temp,offf] = PsdLite(adjCo2UC,res,fs);
    adjSco2UC(:,kk) = temp;
    
    [temp,offf] = PsdLite(DriveOff,res,fs);
    DriveOffPsd(:,kk) = temp;
    
    [temp,offf] = PsdLite(adjEuv,res,fs);
    adjSeuv(:,kk) = temp;
    [temp,offf] = PsdLite(adjEuvUC,res,fs);
    adjSeuvUC(:,kk) = temp;
end

clear off


%% Plots
at = [];
af = [];

%Time Domain plots
h = figure(1); 
% Co2
set(h,'Color','w','Name',['On Droplet Time Domain w/ Simulated EUV'],'WindowStyle', 'docked');

subplot(221); plot(onTime,onCo2UC,'b',onTime,onCo2,'r'); at = [at; gca];
xlabel('Time [s]'); ylabel('PP + MP FCEM PEM [mJ]'); grid on
axis([0 9.5 250 525])
legend('Open-Loop','Closed-Loop')
title('On Droplet CO_2','FontSize',16)
subplot(223); plot(offTime,adjCo2UC,'b',offTime,adjCo2,'r'); at = [at; gca];
xlabel('Time [s]'); ylabel('PP + MP FCEM PEM [mJ]'); grid on
axis([0 9.5 250 525])
title('Simulated Off-droplet CO_2','FontSize',16)

% EUV
set(h,'Color','w','Name',['Off Droplet Time Domain w/ Simulated EUV'],'WindowStyle', 'docked');
subplot(222); plot(onTime,onEuvUC,'b',offTime,adjEuv,'r'); at = [at; gca];
xlabel('Time [s]'); ylabel('Sim. EUV [mJ]'); grid on
axis([0 9.5 0 2.8])
legend('Open-Loop','Closed-Loop')
title('On Droplet EUV','FontSize',16)
subplot(224); plot(offTime,adjEuvUC,'b',onTime,onEuvC,'r'); at = [at; gca];
xlabel('Time [s]'); ylabel('Sim. EUV [mJ]'); grid on
axis([0 9.5 0 2.8])
title('Simulated Off-droplet EUV','FontSize',16)


%PSD plots

h = figure(2); 
% Co2
set(h,'Color','w','Name',['Off Droplet Time Domain w/ Simulated EUV'],'WindowStyle', 'docked');

subplot(221); plot(onf,20*log(mean(onSco2UC(:,count),2)),'b',...
    offf,20*log(mean(onSco2(:,count),2)),'r');af = [af; gca];
xlabel('Freq [Hz]'); ylabel('Amplitude CO_2 [dB]'); grid on
legend('Open-Loop','Closed-Loop')
title('PSD: On Droplet CO_2','FontSize',16)
axis([0 10000 -300 70])
 subplot(223); plot(onf,20*log(mean(adjSco2UC(:,count),2)),'b',...
    offf,20*log(mean(adjSco2(:,count),2)),'r'); af = [af; gca];
xlabel('Freq [Hz]'); ylabel('Amplitude CO_2 [dB]'); grid on
title('PSD: Simulated Off-droplet CO_2','FontSize',16)
axis([0 10000 -300 70])

% EUV
set(h,'Color','w','Name',['Off Droplet Time Domain w/ Simulated EUV'],'WindowStyle', 'docked');
 subplot(222); plot(onf,20*log(mean(onSeuvUC(:,count),2)),'b',...
    offf,20*log(mean(onSeuv(:,count),2)),'r'); af = [af; gca];
xlabel('Freq [Hz]'); ylabel('Amplitude EUV [dB]'); grid on
title('PSD: On Droplet EUV','FontSize',16)
legend('Open-Loop','Closed-Loop')
axis([0 10000 -500 -150])
subplot(224); plot(onf,20*log(mean(adjSeuvUC(:,count),2)),'b',...
    offf,20*log(mean(adjSeuv(:,count),2)),'r'); af = [af; gca];
xlabel('Freq [Hz]'); ylabel('Amplitude EUV [dB]'); grid on
title('PSD: Simulated Off-droplet EUV','FontSize',16)
axis([0 10000 -500 -150])

linkaxes(at,'x');
linkaxes(af,'x');
% imwrite(h,'070313_Co2PSD.jpg','jpg') 


h = figure(3); 
% PID Controller Plots
set(h,'Color','w','Name',['on-Droplet PI Drive'],'WindowStyle', 'docked');
subplot(211);
x=onTime;
y1=onCo2;
y2=DriveOn;
[AX,H1,H2] = plotyy(x,y1,x,y2,'plot');


set(get(AX(1),'Ylabel'),'String','Closed-Loop CO_2','FontSize',15) ;
set(get(AX(2),'Ylabel'),'String','on-Droplet PID Drive','FontSize',15) 
% xlim(AX(1), [0.115 0.1155])
% xlim(AX(2), [0.115 0.1155])
ylim(AX(1), [310 390])
ylim(AX(2), [-20 20])
xlabel('Time [s]'); 
set(H1,'Linewidth',2)
set(H2,'LineStyle','--','Linewidth',2)
title('PID Drive and the Following CO_2','FontSize',16);
grid on

%PID PSD
subplot(212);
plot(onf,20*log(mean(DriveOnPsd(:,count),2)),'b',...
    offf,20*log(mean(DriveOffPsd(:,count),2)),'r');af = [af; gca];
xlabel('Freq [Hz]'); ylabel('Amplitude PID Drive [dB]'); grid on
title('PSD: PID Drive','FontSize',16)
legend('On-Droplet','Off-Droplet')

h = figure(4); 
% PID Controller Plots
set(h,'Color','w','Name',['PSD: Comparison of EUV'],'WindowStyle', 'docked');
plot(onf,20*log(mean(onSeuvUC(:,count),2)),'g',...
    onf,20*log(mean(adjSeuvUC(:,count),2)),'b',...
    offf,20*log(mean(adjSeuv(:,count),2)),'r'); af = [af; gca];
legend('Open loop On-Droplet EUV','Open Loop Sim Off-Droplet EUV','Closed Loop Sim Off-Droplet EUV')
xlabel('Freq [Hz]'); ylabel('Amplitude EUV [dB]'); grid on
title('PSD: Comparison of EUV','FontSize',16)
h = findobj(gcf,'type','line');
set(h,'linewidth',2);
axis([0 10000 -550 -150])
grid on


Matt = struct;
Matt.freq = onf;
Matt.onDrop = onSeuvUC;
Matt.offDropOL = adjSeuvUC;
Matt.offDropCL = adjSeuv;
save('C:\Elena\CO2Control\Matt','Matt');
return