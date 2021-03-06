
%% MAE 283a Final Project : System Identification Course
% Ground Wing Vibration DataSet
delete('/home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig1.eps',...
    '/home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig2.eps',...
    '/home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig3.eps',...
    '/home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig20.eps',...
    '/home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig30.eps',...
    '/home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig4.eps',...
    '/home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig5.eps',...
    '/home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig6.eps',...
    '/home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig7.eps',...
    '/home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig8.eps',...
    '/home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig9.eps',...
    '/home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig10.eps')

clc; close all; %clear all
set(0,'DefaultFigureWindowStyle','docked')
dbstop if error


load flight.mat
u=u(1:end-1);y=y(1:end-1);t=t(1:end-1);
% u=detrend(u(1:end-1));y=detrend(y(1:end-1));t=t(1:end-1);
N=length(u);
Wing = struct('Ts', Ts, 'y',y,'u',u, 't',t,'N',N);
clear Ts y u t n

% t: 	time signal
%
% u: 	input signal into the PZT patches;
% 	sine sweep of 5-35 Hz;
% 	9.0 Volt input signal is actually 180 V after amplification;
%
% y: 	output signal of the accelerometer located in the boom of the wing
%
% Ts:	sampling time
%
% N:	length of data sample

%% Figure(1) - Auto Correlation of input, Ruu
figure(1)
max_lag=300;
Ruu=xcorr(Wing.u,max_lag,'biased');
plot([0:max_lag],Ruu(max_lag+1:end),'LineWidth',2)
h=legend('$$\hat{R_u^N}(\tau)$$');
set(h,'Interpreter','latex')
title('Biased estimate of Input auto-correlation function')
print -depsc /home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig1

%% Figure(2) - Spectrum of input, Puu
figure(2)
subplot(311); % Periodogram psd
psd(spectrum.periodogram,Wing.u,'Fs',1/Wing.Ts);

subplot(312); % Welch psd, use default of 8 sections, 50% overlap, Hamming window
pwelch(Wing.u,128,64,128,1/Wing.Ts);
title('Estimate of Spectrum of Input using Welch PSD, 50% overlap, Hanning Window, default 8 sections')

%% Figure (3) - SPA Estimate

% w = logspace(-2,1.8,1e3); % from 0 to 40

n = 8; % Decimate or downsample rate
t = downsample(Wing.t,n);
Ts= t(2)-t(1);
N = length(t);
Wing = struct('Ts', Ts, 'y',decimate(Wing.y,n),'u',decimate(Wing.u,n), 't',t,'N',N);
clear Ts h max_lag n t Ruu

subplot(313)
psd(spectrum.periodogram,Wing.u,'Fs',1/Wing.Ts);
title('10x Decimated: Estimate of Spectrum of Input');
print -depsc /home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig2


gamma=100; % Change amount of Averaging : window size for LS estimate
W=[zeros((N-gamma)/2,1);hanning(gamma+1);zeros((N-gamma)/2,1)];

Ruu=1/N*xcorr(Wing.u,N/2);
Ryu=1/N*xcorr(Wing.y,Wing.u,N/2);
Ruu_weighted = Ruu.*W;
Ryu_weighted = Ryu.*W;
% make it suitable for fft
Suu=1/N*fft([Ruu_weighted(N/2+1:N);Ruu_weighted(1:N/2)]);
Syu=1/N*fft([Ryu_weighted(N/2+1:N);Ryu_weighted(1:N/2)]);

% check if it went O.K.
if max(abs(imag(Suu)))>1e-13,
    error('FFT must be real valued')
end
Suu=real(Suu);

% spectral estimate
P=Suu(1:N/2+1).\Syu(1:N/2+1); % SPA estimate

% below is my own code for Gspa graph, similar to the matlab SPA
w = logspace(-2,1.8,length(P)); % from 0 to 40

figure(3)
subplot(211)
loglog(w,abs(P),'b-','LineWidth',1.5);
title(['SPA Amplitude, Hanning window of width ' num2str(gamma) ])
ylabel('SPA Mag  [db]')
xlabel('w  [rad/s]');
legend('G_s_p_a',0)
xlim([0 40 ]);
subplot(212)
% semilogx(w,180/pi*unwrap(angle(P)),'b-','LineWidth',1.5);
semilogx(w,180/pi*angle(P),'b-','LineWidth',1.5);
xlim([0 40 ]);
ylabel('SPA Phase  [deg]');
xlabel('w  [rad/s]');
print -depsc /home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig3

clear P Puu Ruu Ruu_weighted Ryu Ryu_weighted Ryy Ryy_weighted Suu Syu Syy W gamma w n


%% Figure(4) - nth order FIR model via Least Squares min
n=10; % least squares FIR model order

Wing.Gfir = impulseest(iddata(Wing.y,Wing.u,Wing.Ts),n);

% nf= 15; % model order
% nb = 6; % 15 !!
% nc = 2; % 2
% nd = 3; % 3
% nk = 0; % 0
% Wing.Gbj = bj(iddata(Wing.y,Wing.u,Wing.Ts),[nb nc nd nf nk]); % BJ model
% 
% impF=impulse(Wing.Gfir);
% impBJ=impulse(Wing.Gbj);
% impBJ=impBJ(1:length(impF));
% 
% 
% f=fit(impF,impBJ,'poly2');
% plot(f,impF,impBJ)
% ci = confint(f,0.99); % confidence bounds with 99% confidence

figure(4)
impulse(Wing.Gfir);
% showConfidence(h); 
xlim([0 2*(n-1)*Wing.Ts])
print -depsc /home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig4

% WingError= Wing.y-lsim(Wing.Gfir, Wing.u, Wing.t);
% figure(6)
% crosscorr(WingError,Wing.u);
% title('Cross-correlation between input and FIR model error, 99% confidence bounds');
% xlim([0 2*(n-1)*Wing.Ts])


% Just do Least squares to get FIR model, start with order n = N/10

% Ruu=xcorr(Wing.u,Wing.u,N/2);
% Ryu=xcorr(Wing.y,Wing.u,N/2);
% Ryy=xcorr(Wing.y,Wing.y,N/2);
% 
% RU=toeplitz(Ruu(N/2+1:N/2+1+n));
% RY=toeplitz(Ryy(N/2+1:N/2+1+n-1));
% RYU=toeplitz(-Ryu(N/2+1-1:N/2+1+n-1),-Ryu(N/2+1-1:-1:N/2+1-n));
% fYU=Ryu(N/2+1:N/2+1+n);
% fY=-Ryy(N/2+2:N/2+2+n-1);
% 
% % estim param using LS xcorr
% theta=[RU RYU;RYU' RY]\[fYU;fY]; 
% Gls=tf(theta(1:n+1)',[1 theta(n+2:end)'],Wing.Ts);
% Wing.Gls=Gls;
% 
% figure(4)
% imp = impulse(Gls);
% stem(0:n-1,imp(1:n),'b*','LineWidth',1.5);
% title(['Impulse Response Coefficients of G_L_S']);
% ylabel('Markov Parameters')
% xlabel('Sample');
% legend('Impulse Reponse of G_L_S',0);
% xlim([0 n+1]);



% alpha=0.01; % for 99% conf intervals
% X0 = zeros(n,1);    % initial conditions of the 6 states
% ysim=lsim(Wing.Gls, Wing.u, Wing.t, X0);
% WingError= Wing.y-ysim;
% data = [WingError,Wing.u];
% [muhat,sigmahat,muci,sigmaci] = normfit(data,alpha)
clear RU RY RYU Ruu Ryu Ryy fY fYU imp theta Gls


%% Figure(5) - Xcorr of error with input, with confidence bounds

figure(5)
resid(Wing.Gfir,iddata(detrend(Wing.y),detrend(Wing.u),Wing.Ts),'Corr'); % detrending for FIR?
title('Cross correlation between input and residuals of output')
xlabel('Lag');
xlim([-1 20]);
print -depsc /home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig5


% X0 = zeros(1,n);    % initial conditions of the 6 states
%  
% WingError= Wing.y-lsim(Wing.Gls, Wing.u, Wing.t, X0);
% figure(5)
% crosscorr(WingError,Wing.u);
% title('Cross-correlation between input and FIR model error, 99% confidence bounds');
% xlim([0 2*n])
% print -depsc /home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig5

clear X0 WingError 

%% Figure(6) - Singular Values && Figure(7) - Impulse response

[tfGRA,ssGRA ] = GRA( Wing ); 
Wing.tfGRA=tfGRA;
Wing.ssGRA=ssGRA;

 % n order model Based on GRA Hankel singular values plot, I chose 7th order model
        
%% Figure(8) - Model validation by xcorr with confidence bounds

figure(8)

resid(idtf(Wing.ssGRA),iddata(Wing.y,Wing.u,Wing.Ts),'Corr');
title('Cross correlation between input and residuals of output of G_G_R_A')
xlabel('Lag');
xlim([-1 20]);

 
 
% X0 = zeros(1,7);    % initial conditions of the 7 states of GRA
% 
% WingError= Wing.y-lsim(Wing.ssGRA, Wing.u, Wing.t, X0);
% crosscorr(WingError,Wing.u);
% xlim([0 2*7])
print -depsc /home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig8

clear tfGRA ssGRA n
%% Figure(9) - BJ model : G = B/F , H = C/D

nf= 6; % model order
nb = 15; % 15 !!
nc = 2; % 2
nd = 3; % 3
nk = 0; % 0
Wing.Gbj = bj(iddata(Wing.y,Wing.u,Wing.Ts),[nb nc nd nf nk]);

 
% plots for step responses
sbj=step(Wing.Gbj,Wing.t(end));
sgra=step(Wing.ssGRA,Wing.t(end));

figure(90)
plot(Wing.t(1:length(sgra)),sgra, Wing.t(1:length(sbj)),sbj)
legend('GRA Sim (Step)','BJ Sim');
title ('Contrasting GRA and BJ Model'); 
% axis([0 5 0 5e3]);
xlabel('Time [s]'); ylabel('Step Response');


figure(9)

resid(idtf(Wing.Gbj),iddata(Wing.y,Wing.u,Wing.Ts),'Corr');
title('Cross correlation between input and residuals of output of G_B_J')
xlabel('Lag');
xlim([-1 20]);
 
% X0 = zeros(1,nf);    % initial conditions of the 7 states
% 
% WingError= Wing.y-lsim(Wing.Gbj, Wing.u, Wing.t, X0);
% crosscorr(WingError,Wing.u);
% xlim([0 2*nf])
% title('Cross-correlation between BJ output Error and input')
print -depsc /home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig9

clear nk X0 ysim 
%% Figure (10) - Measured vs simulated output

% Simulated (G only)
paramBJ = getpvec(Wing.Gbj);
% Gbj = idtf(tf(paramBJ(1:nb)',[1 paramBJ(end-nf:end)'],Wing.Ts));

% Predicted (G and H) 1-15, 16-17,18-20,21-26


Gp = tf(paramBJ(1:nb)',[1 paramBJ(end-nf:end)'],Wing.Ts);
Hp = tf(paramBJ(nb+1:nb+nc)',[1 paramBJ(nb+nc+1:nb+nc+nd)'],Wing.Ts);

yPred=lsim(inv(Hp)*Gp,Wing.u,Wing.t)+lsim((1-inv(Hp)),Wing.y,Wing.t);

ysimP= lsim(Wing.Gbj, Wing.u, Wing.t);


% ysimS= lsim(Gbj, Wing.u, Wing.t);

figure(10)
plot(Wing.t,Wing.y,Wing.t,yPred,Wing.t,ysimP);
legend('Measured output','Simulated BJ output','Predicted BJ output')
title('Comparison of Simulated, Predicted, and Measured Outputs','FontSize',16)
print -depsc /home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig10

% figure(11)
% bode(Wing.ssGRA)
% title('GRA')
% figure(12)
% bode(Wing.Gfir)
% title('FIR')
% figure(13)
% bode(Wing.Gbj)
% title('BJ')


clear X0 ysim Gbj nb nf

