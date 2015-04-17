% Function

function [co2,euv,misc] = mainScript(Kp,Ki)

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

% CO2 control simulation
onTimeCtrl = [];
onCo2Ctrl = [];
onEuv = [];

onCe = [];
onCeMean=[];
onEuvC = [];


for kk = 1:10 % length(bd);
    % index pulses in burst & count ensamble average
    idx = find(on.ECburstIndex == bd(kk) & onCO2 == 1);
    idx = idx(2:end);

    % Time Domain
    onTime = [onTime; on.t_(idx)];
    onFwd = [onFwd; on.ECpem3Value(idx)]; % forward going CO2
    onCo2 = [onCo2; on.ECpem1Value(idx)];
    onEuv = [onEuv; on.ECeuvValue(idx)];

    % = % Control Simulation % = % = % = % = % = % = % = % = % = % = %
    idxCtrl = idx(holdOff+1 - 100:end);
    tempCo2 = on.ECpem1Value(idxCtrl);

    [tempCo2,Drive] = co2controllerClipS_V1(Kp,Ki,tempCo2);

    onTimeCtrl = [onTimeCtrl; on.t_(idxCtrl)];
    onCo2Ctrl = [onCo2Ctrl; tempCo2'];


    % = % = % = % = % = % = % = % = % = % = % = % = % = % = % = % = %

%     %     % Obtaining EUV
%     onCe = [onCe; on.ECeuvValue(idx)./(0.26*0.92*(on.ECpem1Value(idx)+on.ECpem2Value(idx)))*100];
%     onCeMean=mean(on.ECeuvValue(idx)./(0.26*0.92*(on.ECpem1Value(idx)+on.ECpem2Value(idx)))*100);
%     onEuvC = [onEuvC; (0.26*0.92*(tempCo2)) .* onCeMean / 100];

%Co2 compensated EUV
    A = mean(onEuv./onCo2);
%     A = 1; % conversion efficiency constant
    idx = ismember(onTime,onTimeCtrl);
    EuvBar = onEuv(idx) - A*(onCo2(idx) - onCo2Ctrl);


    % Compute PSD in burst
    [temp,onf] = PsdLite(on.ECpem1Value(idxCtrl),res,fs);
    onPsdCo2(:,kk) = temp;
    [temp,onf] = PsdLite(tempCo2,res,fs);
    onPsdCo2Ctrl(:,kk) = temp;

    [temp,onf] = PsdLite(onEuv,res,fs);
    onPsdEuv(:,kk) = temp;
    [temp,onf] = PsdLite(EuvBar,res,fs);
    onPsdEuvCtrl(:,kk) = temp;

    


end

co2 = struct;
co2.onCo2 = onCo2;
co2.onPsdCo2 =onPsdCo2;
co2.onCo2Ctrl = onCo2Ctrl;
co2.onPsdCo2Ctrl = onPsdCo2Ctrl;


euv = struct;
euv.onEuv = onEuv;
euv.EuvBar = EuvBar;
euv.onPsdEuv = onPsdEuv;
euv.onPsdEuvCtrl = onPsdEuvCtrl;


misc = struct;
misc.onf = onf;
misc.onTime = onTime;
misc.onTimeCtrl = onTimeCtrl;


end
