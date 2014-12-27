% CO2 control
clear;close all;clc;
dbstop if error
tic

    Kp = 0.3;
    Ki = 0.5;
    
 [co2,euv,misc] = mainScript_V1(Kp,Ki);

 fprintf('CO_2 and EUV Cross Correlation Coefficient is %.3f \n',misc.corr);
%% Plots
at = [];
ax = [];

% h = figure(1); 
% set(h,'Color','w','Name',['Time Domain Forward CO2'],'WindowStyle', 'docked');
% plot(onTime,onFwd)
% title('Time Domain Forward CO_2','FontSize',16);

h = figure(1); 
set(h,'Color','w','Name',['Frequency Domain EUV'],'WindowStyle', 'docked');
plot(misc.A,'*r','LineWidth',2)
title('Conversion Efficiency per Burst','FontSize',16);
xlabel('Burst'); ylabel('CE (ratio)'); grid on

h = figure(2); 
set(h,'Color','w','Name',['Time Domain Amplified CO2'],'WindowStyle', 'docked');
subplot(211)
plot(misc.onTime,co2.onCo2,'b',misc.onTimeCtrl,co2.onCo2Ctrl,'r'); at = [at; gca];
title('Time Domain Amplified CO_2','FontSize',16);
xlabel('Time [s]'); ylabel('CO_2 [mJ]'); grid on
legend ('Open Loop','Closed Loop',0)
subplot(212)
plot(misc.onTime,euv.onEuv,'b',misc.onTimeCtrl,euv.EuvBar,'r'); at = [at; gca];
title('Effect of CO_2 compensated EUV')
xlabel('Time [s]'); ylabel('EUV [mJ]'); grid on
legend ('Data Euv','CO2 compensated EUV',0)

h = figure(3); 
set(h,'Color','w','Name',['Frequency Domain CO2'],'WindowStyle', 'docked');
subplot(211); plot(misc.onf,20*log(mean(co2.onPsdCo2,2)),'b',...
    misc.onf,20*log(mean(co2.onPsdCo2Ctrl,2)),'r'); ax = [ax; gca];
legend ('Open Loop','Closed Loop',0)
title('CO_2 PSD','FontSize',16);
xlabel('Frequency [Hz]'); ylabel('Amplitude CO_2 [dB]'); grid on
subplot(212); plot(misc.onf,cumsum(mean(co2.onPsdCo2,2)),'b',...
    misc.onf,cumsum(mean(co2.onPsdCo2Ctrl,2)),'r'); ax = [ax; gca];
title('CO_2 Cummulative PSD','FontSize',16);
xlabel('Frequency [Hz]'); ylabel('Amplitude CO_2 [dB]'); grid on
legend ('Open Loop','Closed Loop',0)

h = figure(4); 
set(h,'Color','w','Name',['Frequency Domain EUV'],'WindowStyle', 'docked');
subplot(211); plot(misc.onf,20*log(mean(euv.onPsdEuv,2)),'b',...
    misc.onf,20*log(mean(euv.onPsdEuvCtrl,2)),'r'); ax = [ax; gca];
legend ('Open-Loop-Co2 EUV','CO_2 compensated EUV',0)
title('EUV PSD','FontSize',16);
xlabel('Frequency [Hz]'); ylabel('Amplitude EUV [dB]'); grid on
subplot(212); plot(misc.onf,cumsum(mean(euv.onPsdEuv,2)),'b',...
    misc.onf,cumsum(mean(euv.onPsdEuvCtrl,2)),'r'); ax = [ax; gca];
legend ('Open-Loop-Co2 EUV','CO_2 compensated EUV',0)
title('EUV Cummulative PSD','FontSize',16);
xlabel('Frequency [Hz]'); ylabel('Amplitude EUV [dB]'); grid on

h = figure(5); 
set(h,'Color','w','Name',['EUV- CO_2 Cross-correlation'],'WindowStyle', 'docked');
plot(misc.AcFreq,20*log(mean(misc.onPsdAc,2)),'b')
title('Psd of Cross-correlation of CO_2 & EUV','FontSize',16);
xlabel('Frequency [Hz]'); ylabel('Amplitude Cross-correlation [dB]'); grid on
axis tight

h = figure(6); 
set(h,'Color','w','Name',['PID Bode Plot'],'WindowStyle', 'docked');
bode(misc.PIDtf)
h = findobj(gcf,'type','line');
set(h,'linewidth',2.5);
title('Bode plot for PI controller','FontSize',16);
grid on

% h = figure(7); 
% set(h,'Color','w','Name',['Checking Sim EUV'],'WindowStyle', 'docked');
% subplot(211)
% plot(misc.onf,20*log(mean(co2.onPsdCo2,2)),'k',...
%     misc.onf,20*log(mean(euv.onPsdEuv,2)),'g')
% title('Checking Simulated EUV','FontSize',16);
% legend('True Co2','True Euv')
% grid on
% % 
% % set(h,'Color','w','Name',['Checking Sim EUV'],'WindowStyle', 'docked');
% % subplot(212)
% % plot(misc.onf,20*log(mean(co2.onPsdCo2Sim,2)),'k',...
% %     misc.onf,20*log(mean(euv.onPsdEuvSim,2)),'g')
% % title('Checking Simulated EUV','FontSize',16);
% % legend('Sim Co2','Sim Euv')
% % grid on
% % 
% % 


% For presentation
h = figure(7); 
set(h,'Color','w','Name',['Time Domain Amplified CO2'],'WindowStyle', 'docked');
subplot(211)
plot(misc.onTime,co2.onCo2,'b',misc.onTimeCtrl,co2.onCo2Ctrl,'r'); at = [at; gca];
title('Time Domain CO_2','FontSize',16);
xlabel('Time [s]'); ylabel('CO_2 [mJ]'); grid on
legend ('Open Loop','Closed Loop',0)
axis([2 5 200 400])

subplot(212); plot(misc.onf,20*log(mean(co2.onPsdCo2,2)),'b',...
    misc.onf,20*log(mean(co2.onPsdCo2Ctrl,2)),'r'); ax = [ax; gca];
title('Frequency Domain CO_2 (PSD)','FontSize',16);
xlabel('Frequency [Hz]'); ylabel('Amplitude CO_2 [dB]'); grid on
% subplot(313); plot(misc.onf,cumsum(mean(co2.onPsdCo2,2)),'b',...
%     misc.onf,cumsum(mean(co2.onPsdCo2Ctrl,2)),'r'); ax = [ax; gca];
% title('Frequency Domain CO_2 (Cummulative PSD)','FontSize',16);
% xlabel('Frequency [Hz]'); ylabel('Amplitude CO_2 [dB]'); grid on


linkaxes(ax,'x');
linkaxes(at,'x');
xlim([0 5000]);
toc

clear at ax h
