% MAE 283A Hwk 1 Prob 3

% u is a piezo voltage excitation
% y is a displacement measurement
% input excitation is a white noise input w/ normalized var of 1

clear all; close all; clc;

load('\\acsnfs4.ucsd.edu\CifsHomes\274\ymenyayl\MATLAB\SystemID\set1data.mat');

%% Elena's Xcorr Version
% input is white noise

N = length(u); 
ru = zeros(N,1);
ruy = zeros(N,1);
for k=1:N+1
    for i=1:N-k+1
        ru(k)=ru(k)+u(i)*u(i+k-1);
        ruy(k)=ruy(k)+u(i)*y(i+k-1);
    end
end
ru = ru ./ N;
ruy = ruy ./ N;

Ru = toeplitz(ru(1:256));
g = Ru\ruy(1:256); % impulse resp coeff

% Fourier transform of impulse resp is the "TF" or freq resp
G = fft(g);
G = G(1:256/2);

mag = abs(G);
phase = unwrap(angle(G));

% freq vector
freq = (0:length(G)-1)*99/length(G)';


%% Matlabs's Xcorr Version
ruM = xcorr(u,'coeff');
ruyM = xcorr(u,y,'coeff');

ruM = ruM(16382/2+1:end);
ruyM = ruyM(16382/2+1:end);

RuM = toeplitz(ruM(1:256)); % first or last 256?
gM = RuM\ruyM(1:256); % first or last?


%% Plots
figure(1)
plot (u)
hold on
plot(y,'r')

figure(2)
subplot(221)
stem(0:255,g)
title ('Impulse Response Parameters');
xlabel('Samples'); ylabel('Markov Parameters');

subplot(222)
plot(freq,mag) 
grid on;
title('Magnitude');
ylabel('Magnitude (dB)')
set(gca,'XTick',[15 40 60 85]);

subplot(224)
plot(freq,phase*180/pi); 
grid on;
title('Phase');
set(gca,'XTick',[15 40 60 85]);
ylabel('Phase (deg))') 
xlabel('Frequency (Rad/s)') 

subplot(223)
stem(0:20,g(1:21))
title ('Elenas Version: Zoomed in');
xlabel('Samples'); ylabel('Markov Parameters');
