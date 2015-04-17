clc;clear all; close all;


N=1024; % Number of samples
f=2; % Frequency of the sinewave
FS = 200; % Sampling Frequency
wn = (2*pi*f/FS);
k=0:N-1; % Sample index numbers
u=sin(wn*k); % Generate the signal, u(k)
[Ruu,lags]=xcorr(u,'coeff'); % Estimate its autocorrelation
tau = lags*f/FS;
t =[1:N]*(1/FS); % Prepare a time axis 


figure(1)
% Plot
subplot(2,2,1); % Signal 
plot(t,u,'LineWidth',2); 
title('Sinewave of frequency 1000Hz [FS=8000Hz]');
xlabel('Time, [s]');
ylabel('Amplitude');
grid;

subplot(2,2,2); % Autocorrelation
plot(tau,Ruu,'LineWidth',2);
grid;
title(' Biased autocorrelation func of signal');
xlabel('lags');
ylabel('Autocorrelation');


subplot(2,2,3); % Periodogram psd
psd(spectrum.periodogram,u,'Fs',FS);

subplot(2,2,4); % Welch psd, use default of 8 sections, 50% overlap, Hamming window
pwelch(u,128,64,128,FS);