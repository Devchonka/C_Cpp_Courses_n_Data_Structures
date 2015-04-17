% Function

function [co2,euv,misc] = mainScript_V1(Kp,Ki)

pathname = 'C:\Documents and Settings\L503763\Desktop\yelena\matlab_data';
filename = '20130618_105343_RT02_000_seedOpen_TruOn_PA1On_PA23On_DropOn.mat';
on = load([pathname '\' filename],'ECburstIndex',...
    'ECmiscellaneousStatus','ECpem1Value','ECpem2Value','ECpem3Value',...
    't_','ECeuvValue');

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
% onDrop = bitget(on.ECmiscellaneousStatus,22)+2; % on droplet synched w/ EUV
% some parameters of system
holdOff = 500;
res = 2^13;
fs = mean(1./diff(on.t_));

% data initialization
onTime = [];
onFwd = [];
onCo2 = [];

onPsdFwd = zeros(res/2+1,length(bd));
onPsdCo2 = zeros(res/2+1,length(bd));
onPsdCo2Ctrl = zeros(res/2+1,length(bd));
onPsdAc = zeros(res/2+1,length(bd));

% CO2 control simulation
onTimeCtrl = [];
onCo2Ctrl = [];
onEuv = [];

onCe = [];
onCeMean=[];
onEuvC = [];
% Ac = [];

A = zeros(1,10);
EuvBar = [];


for kk = 1:10 % length(bd);
    % index pulses in burst & count ensamble average
    idx = find(on.ECburstIndex == bd(kk) & onCO2 == 1);
    idx = idx(2:end);

    burstData = structfun(@(x) x(idx),on,'UniformOutput',0);
    % Check Cross-correlation btwn experimental CO2 and EUV
    
%     AcBurst=xcorr(burstData.ECeuvValue,burstData.ECpem1Value);
%     Ac = [Ac;AcBurst];
    
    % Time Domain
    onTime = [onTime; burstData.t_];
    onFwd = [onFwd; burstData.ECpem3Value]; % forward going CO2
    onCo2 = [onCo2; burstData.ECpem1Value];
    onEuv = [onEuv; burstData.ECeuvValue];

    % = % Control Simulation % = % = % = % = % = % = % = % = % = % = %
    idxCtrl =holdOff+1 - 100:length(idx); % without hold-off
    tempCo2 = burstData.ECpem1Value(idxCtrl);

    [tempCo2,ans] = co2controllerClipS_V1(Kp,Ki,tempCo2);

    onTimeCtrl = [onTimeCtrl; burstData.t_(idxCtrl)];
    onCo2Ctrl = [onCo2Ctrl; tempCo2'];


    % = % = % = % = % = % = % = % = % = % = % = % = % = % = % = % = %

%Co2 compensated EUV
    A(kk) = mean(burstData.ECeuvValue(idxCtrl) ./(0.26*0.92*(burstData.ECpem1Value(idxCtrl)))); % Conversion Efficiency calc

%     idx = ismember(onTime,onTimeCtrl);
    EuvB = burstData.ECeuvValue(idxCtrl) - A(kk)*(burstData.ECpem1Value(idxCtrl) - tempCo2');
    EuvBar = [EuvBar;EuvB];

    % Compute PSD in burst
    [temp,onf] = PsdLite(burstData.ECpem1Value(idxCtrl),res,fs);
    onPsdCo2(:,kk) = temp;
    [temp,onf] = PsdLite(tempCo2,res,fs);
    onPsdCo2Ctrl(:,kk) = temp;

    [temp,onf] = PsdLite(burstData.ECeuvValue(idxCtrl),res,fs);
    onPsdEuv(:,kk) = temp;
    [temp,onf] = PsdLite(EuvB,res,fs); 
    onPsdEuvCtrl(:,kk) = temp;
    
    % Psd of Cross-correlation
    [temp,AcFreq] = CPSDlite(burstData.ECeuvValue,burstData.ECpem1Value,res,fs); 
    onPsdAc(:,kk) = temp;


end

co2 = struct;
co2.onCo2 = onCo2; % true CO2
co2.onPsdCo2 =onPsdCo2;
co2.onCo2Ctrl = onCo2Ctrl;
co2.onPsdCo2Ctrl = onPsdCo2Ctrl;


euv = struct;
euv.onEuv = onEuv; % true EUV
euv.EuvBar = EuvBar;
euv.onPsdEuv = onPsdEuv;
euv.onPsdEuvCtrl = onPsdEuvCtrl;

misc = struct;
misc.onf = onf;
misc.onTime = onTime;
misc.onTimeCtrl = onTimeCtrl;
misc.A = A;
misc.onPsdAc = onPsdAc;
misc.AcFreq = AcFreq;
misc.corr = corr2(onCo2,onEuv);
misc.PIDtf = tf([Kp Ki],[1 0]);


end
