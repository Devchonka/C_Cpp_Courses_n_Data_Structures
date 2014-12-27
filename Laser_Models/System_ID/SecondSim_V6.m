% Simulation for Droplet position to EUV energy model
% has K_bar (Kb) to help simulations be equivalent
clc; clear; 
dbstop if error
delete('C:\Elena\Daniel\Daniel2.mat')

tic
%% Basic Parameters

tau=1.1e-3; % 1.1 msec delay
p = -1600; % pole at 1600 rad/sec in LHP
fs = 50e3; % Sampling freq
% ts = 1/fs; % Sampling time
nd = tau*fs; % # samples to delay
Nsamples = 1000; % simulation samples
% tTotal = Nsamples*ts; % simulation time
TimeSim = linspace(0,Nsamples/fs,Nsamples); % time vector
sigma = 10;
a = 1.5;
b = 1/(sigma)^2;
Kb = 0.997;
clear sigma

%% Feedback Loop - for figure(1)
% r1 = linspace(-10,10,6); % Droplet y position relative to focus
% r1 is the initial alignment of the laser to droplet
r1 = [-10 -6 0 3 5 10];
[Uy,Y] = Second_dropletLoop_V6(Kb,r1,a,b);

%% Input Gaissian ParamID & r2 Square wave - for figure (2)
[fig2u,fig2y] = GaussianCurve(a,b,Nsamples,25); % 20 um wide beam, 1.5mJ peak
r2 = double((mod(1:Nsamples,60) > 30)); % External wave for r2 switch

%% Lowpass Filter - for figure (7)
G = tf(p,[1 p],'InputDelay',tau);

%% PSD vectors - for figure(3)
psdUy = zeros(2^9 /2 +1,size(Uy,1));
psdfy = zeros(2^9 /2 +1,size(Uy,1));
psdY = zeros(2^9 /2 +1,size(Y,1));
psdfY = zeros(2^9 /2 +1,size(Y,1));

for i = 1: size(Uy,1)
    [psdUy(:,i),psdfy(:,i)] = PsdLite(Uy(i,:),2^9,fs);
    [psdY(:,i),psdfY(:,i)] = PsdLite(Y(i,:),2^9,fs);
end

%% Save to struct
Daniel2 = struct;
Daniel2.time2 = TimeSim;
Daniel2.Uy2 = Uy;
save C:\Elena\Daniel\Daniel2.mat -struct Daniel2;

%% Plots

h= figure(8);
set(h,'Color','w','Name','Input,u & Output,y','WindowStyle', 'docked');
plot(TimeSim,Uy(3,:),'r','LineWidth',2.5);hold on
plot(TimeSim,Y(3,:),'b','LineWidth',2.5)
legend ('Droplet Position, u_y [um]',...
    'EUV, y [mJ]',0)
xlabel('Time [s]'); ylabel('u_x, u_y, and EUV'); grid on
title('Droplet Position U vs EUV energy Y','FontSize',16)
print -depsc C:\Elena\Daniel\Latex\DropPosition2EUV\SingleDropPos_bar

h= figure(9);
set(h,'Color','w','Name','Input Gaussian & Square wave','WindowStyle', 'docked');
plot(fig2u,fig2y,'LineWidth',2.5)
xlabel('Droplet Position [um]'); ylabel('EUV energy [mJ]'); grid on
title('Droplet Position, U vs EUV energy, Y','FontSize',16)

h= figure(10);
set(h,'Color','w','Name','Time: Droplet positioning for Different References','WindowStyle', 'docked');
plot(TimeSim,Y','LineWidth',2)
xlabel('Time [s]'); ylabel('EUV Energy [mJ]'); grid on
title('EUV energy, y for a Given Reference, r1','FontSize',16)
legend (legend_names('y',r1),0)
print -depsc C:\Elena\Daniel\Latex\DropPosition2EUV\euv_bar

h= figure(11);
set(h,'Color','w','Name','Time: Droplet positioning for Different References','WindowStyle', 'docked');
plot(TimeSim,Uy','LineWidth',2)
xlabel('Time [s]'); ylabel('Droplet Position [um]'); grid on
title('u_y for a given r1','FontSize',16)
% legend (legend_names('u_y',r1),0)
print -depsc C:\Elena\Daniel\Latex\DropPosition2EUV\TimeU_bar

h= figure(12);
set(h,'Color','w','Name','Freq: Droplet Positions in y','WindowStyle', 'docked');
subplot (1,2,1)
plot(psdfy,20*log(psdUy),'LineWidth',2,'Marker','*');
xlabel('Frequency [Hz]'); ylabel('Content Intensity'); grid on
title('PSD of Droplet Y Positions','FontSize',16)
axis([0 1500 -800 -100])
subplot (1,2,2)
plot(psdfY,20*log(psdY),'LineWidth',2,'Marker','*');
xlabel('Frequency [Hz]'); ylabel('Content Intensity'); grid on
title('PSD of EUV','FontSize',16)
axis([0 1500 -800 -100])
print -depsc C:\Elena\Daniel\Latex\DropPosition2EUV\FreqUy_bar


h= figure(13);
set(h,'Color','w','Name','Square wave','WindowStyle', 'docked');
plot(TimeSim,r2,'r');
xlabel('Time [s]'); ylabel('Square Wave'); grid on
title('Square Wave','FontSize',16)

h= figure(14);
set(h,'Color','w','Name','Lowpass Filter Bode','WindowStyle', 'docked');
bode(G)
h = findobj(gcf,'type','line');
set(h,'linewidth',2.5);
grid on
title('Lowpass Filter with a 1.1 ms delay','FontSize',16)

%% Coparison of Full Model vs Condensed Model
Comparison_4_FirstSim_V6(r1);

% save('C:\Elena\Daniel\dev.mat','dev11','-append');
load('C:\Elena\Daniel\dev.mat')
Dev = [dev0;dev03;dev05;dev07;dev09;dev095;dev0994;dev0995;...
    dev0996;dev0997;dev0998;dev0999;dev1];
Dev = Dev( :,[1:3,5:6])';
K = [0,0.3,0.5,0.7,0.9,0.95,0.994,0.995,0.996,0.997,0.998,0.999,1];
h= figure(16);
set(h,'Color','w','Name','Variance Analysis','WindowStyle', 'docked');
subplot(121)
contourf(K,r1(:,[1:3,5:6]),Dev,50)
colorbar
AvgVar = mean(Dev)';
xlabel('Gain Kbar [s]'); ylabel('Input r_1'); grid on
xlim([0.8 1])
title('Variance of difference vectors in U_y','FontSize',16)
subplot(122)
plot(K,Dev,'Marker','*','LineWidth',1.5)
legend (legend_names('var',r1(:,[1:3,5:6])),0)
xlim([0.8 1])
print -depsc C:\Elena\Daniel\Latex\DropPosition2EUV\Kbar

% %% Plots continued
% h= figure(17);
% set(h,'Color','w','Name','Gain','WindowStyle', 'docked');
% plot(K,AvgVar,'Marker','*','LineWidth',1.5)
% xlabel('Gain Kbar [s]'); ylabel('Mean (over all inputs) Variance of difference vectors in U_y'); grid on
% title('Mean (over all inputs) Variance of difference vectors in U_y','FontSize',16)
% % axis ([0.99 1 0 5])
% xlim([0.6 1])

toc
clear h i
