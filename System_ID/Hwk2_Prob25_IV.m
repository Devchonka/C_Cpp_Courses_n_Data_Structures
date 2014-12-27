% MAE 283A, Hwk 2, prob 2.5
% Estimate G using instrumental variables


clc; close all; clear all
set(0,'DefaultFigureWindowStyle','docked') 

Ts = 1;
G0=tf([0.8 -0.5 0.6 0.5],[1 -0.1 0.6 0.1],Ts); % real system
N= 2048;
u=randn(N,1); % input white noise

lambda = .5; % noise level
H0=tf([1],[1],1); % Generating noisy data with OE structure (white noise output noise)
[ ~, y, ~, ~, ~, theta, thetaR ] = LS_ParamVec( N, G0, H0, lambda, u );

G0hat = tf(thetaR(1:4)',[1 thetaR(5:7)'],1);

[ theta, thetaR ] = IV_ParamVec( N, G0hat, u );

Ghat=tf(thetaR(1:4)',[1 thetaR(5:7)'],1);

figure(10)
w=linspace(0,pi,N/2+1);
[mghat,pghat]=bode(Ghat,w);
[m,p]=bode(G0,w);

subplot(211)
l=loglog(w,mghat(:),'g-',w,m(:),'r');
set(l,'linewidth',2);
%axis([1e-2 1e1 1e-2 1])
title(['\bf Amplitude Bode plot of OE model vs Real Sys using IV'])
ylabel('mag  [gain]')
xlabel('w  [rad/s]');
legend('G_I_V','G_0',3)
axis([1e-3 10 1e-1 1e1])

subplot(212)
l=semilogx(w,pghat(:),'g-',w,p(:),'r');
set(l,'linewidth',2);
ylabel('phase  [deg]');
xlabel('w  [rad/s]');
title(['\bf Phase Bode plot of OE model vs Real Sys using IV'])