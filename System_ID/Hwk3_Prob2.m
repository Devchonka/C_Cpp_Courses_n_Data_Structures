% MAE 283 Hwk 3 Problem 2
clc; clear all; close all;
% set(0,'DefaultFigureWindowStyle','docked') 
dbstop if error

% Question 2.1 : System ID from step response and white noise I/O data

load R333_STEP_data.mat
Step = struct('Ts', Ts, 'y',y);
tStep = Ts*[0:length(Step.y)-1]';
clear Ts y

% Observ, Control matrix size: for n=N1+N2, # singular vals=rank(R)
N1=248; 
N2=N1;
n = 6; % model order

TgHu = repmat(Step.y(1:N1), 1,N2);
Hy = zeros(N1,N2);
for j=1:N2
    Hy(:,j)=Step.y(j+1:N1+j);
end

% Find Weighted Hankel matrix, R and its Singular Vals
R = Hy-TgHu; 
[U,S,V] = svd(R);
clear j TgHu Hy 

Sigmas = diag(S);
%% Figure (1) - Singular Values from Step resp
figure(1)
semilogy(1:20,Sigmas(1:20), 'r*', 'LineWidth',1.5);
title ('First 20 Singular Values from weghted Hankel matrix R');
xlabel('# singular values'); ylabel('$\sigma$ ','interpreter','latex');

%% Find State Space model
S = S(1:n,1:n); V = V(1:end,1:n); U = U(1:end,1:n); % reduce rank
R1 = U*S^.5;
R2 = S^.5*V'; 
R1left = (S^-.5)*U';
R2left = V*(S^-.5);

% Find Rshift
TgHu = repmat(Step.y(1:N1+1), 1,N2);
Hy = zeros(N1+1,N2);
for j=1:N2
    Hy(:,j)=Step.y(j+1:N1+j+1);
end
Rshift = Hy-TgHu; 
Rshift = Rshift(2:end, :,:);

A = R1left*Rshift*R2left;
B = R2(:,1);
C = R1(1,:);
D = Step.y(1); % actually do least squares but here sys has at least 1 time step delay
Step.tf = tf(ss(A,B,C,D,Step.Ts));
Step.ss = ss(A,B,C,D,Step.Ts);

% [num,den]=ss2tf(A,B,C,D);

%% Figure (2) - Measured vs Approximated step response
figure(2)
plot(tStep,step(Step.tf,tStep(end)), 'ro', 'LineWidth',1.5);hold on
plot(tStep,Step.y, 'b*', 'LineWidth',1.5);
title ('Real vs GRA Algorithm Simulated step resp'); 
axis([0 5 0 5e3]); legend('GRA Simulated', 'Actual');
xlabel('Time [s]'); ylabel('Step Response');

clear Hy N1 N2 R R1 R1left Rshift R2 R2left S Sigmas n TgHu U V j A B C D sys


%% Question 2.2 : using I/O data  with noise model to estimate model by min 1-step ahead Predic Error (usual LS!)

load R333_PRPS_data.mat;
Prps = struct('Ts', Ts, 'u', u, 'y',y);
N = length(u);
Prps.N = length(u);

% Using Matlab routine bj()
nb = 7;
nc = 4;
nd = 1;
nf= 8;
nk = 0;
% Box- Jenins model: G=B/F and H = C/D
sysPrps = bj(iddata(Prps.y,Prps.u,Prps.Ts),[nb nc nd nf nk]);
Prps.tf = sysPrps;
clear sysPrps nc nd nf nb nk u y Ts

%% Figure (3)- bode plots

w=linspace(0,pi/Prps.Ts,N/2+1);
[m,p] = bode(Prps.tf,w);
[mS,pS] = bode(Step.tf,w);

Step.tf
Prps.tf

figure(3)
subplot(211)
loglog(w,abs(m(:)),'r--','LineWidth',1.5);hold on
hold on; loglog(w,abs(mS(:)),'k-', 'LineWidth',1.5);
title(['\bf Amplitude Bode plot of BJ model'])
ylabel('mag  [gain]')
xlabel('w  [rad/s]');
legend('G_b_j from Prps','G_h_a_t From Step',3)

subplot(212)
l=semilogx(w,p(:),'r--', w,pS(:),'k-');
set(l,'linewidth',1.5);
ylabel('phase  [deg]');
xlabel('w  [rad/s]');

%% Figure (4) - Measured vs Approximated step response
figure(4)
plot(tStep,step(Step.tf,tStep(end)), 'k', 'LineWidth',1.5);
hold on; plot(tStep,step(Prps.tf,tStep(end)), 'r--', 'LineWidth',1.5)
legend('GRA Sim (Step)','bj() Sim (Prps)');
title ('Contrasting Matlab bj() func'); 
axis([0 5 0 5e3]);
xlabel('Time [s]'); ylabel('Step Response');

clear l m mS p pS N

%% Question 2.3 : Model validation


X0 = zeros(1,6);    % initial conditions of the 6 states
ysim=lsim(Prps.tf, Prps.u(1:500), tStep, X0);

% [ysim,~,~] = lsim(Step.ss,Prps.u',tStep); 
PrpsError= Prps.y(1:500)-ysim;
Rei=xcorr(PrpsError,Prps.u,length(PrpsError)/2);

figure(5)
plot(tStep,Rei(1:500))
title ('Xcorr of simulation error with Prps input on BJ model'); 
% axis([0 500 0 5e3]);
xlabel('Time [s]'); ylabel('Xcorr of sim error and Prps input');


% Step.u = ones(size(Step.y));
% Step.N = length(Step.y);
% GRA(Step)



% %% Estimated LS: ARX model
% 
% H0=tf([1],num,Prps.Ts);
% lambda=50;% noise level
% 
% ynf=Prps.y;
% 
% e=sqrt(lambda)*randn(N,1);
% v=lsim(H0,e);
% 
% y=ynf+v;
% 
% Ruu=xcorr(Prps.u,Prps.u,N/2);
% Ryu=xcorr(Prps.y,Prps.u,N/2);
% Ryy=xcorr(Prps.y,Prps.y,N/2);
% 
% RU=toeplitz(Ruu(N/2+1:N/2+1+5)); % 6 u's
% RY=toeplitz(Ryy(N/2+1:N/2+1+5)); % 6 y's
% RYU=toeplitz(-Ryu(N/2+1-1:N/2+1+4),-Ryu(N/2+1-1:-1:N/2+1-6));
% fYU=Ryu(N/2+1:N/2+1+5);
% fY=-Ryy(N/2+2:N/2+2+5);
% 
% theta=[RU RYU;RYU' RY]\[fYU;fY];
% Ghat=tf(theta(1:6)',[1 theta(7:12)'],Prps.Ts);
% 
% for i = 2:10
%     ynf=lsim(Ghat,Prps.u);
%     
%     e=sqrt(lambda)*randn(N,1);
%     v=lsim(H0,e);
%     
%     y=ynf+v;
%     
%     Ruu=xcorr(Prps.u,Prps.u,N/2);
%     Ryu=xcorr(Prps.y,Prps.u,N/2);
%     Ryy=xcorr(Prps.y,Prps.y,N/2);
%     
%     RU=toeplitz(Ruu(N/2+1:N/2+1+5)); % 6 u's
%     RY=toeplitz(Ryy(N/2+1:N/2+1+5)); % 6 y's
%     RYU=toeplitz(-Ryu(N/2+1-1:N/2+1+4),-Ryu(N/2+1-1:-1:N/2+1-6));
%     fYU=Ryu(N/2+1:N/2+1+5);
%     fY=-Ryy(N/2+2:N/2+2+5);
%     
%     theta=[RU RYU;RYU' RY]\[fYU;fY];
%     Ghat=tf(theta(1:6)',[1 theta(7:12)'],Prps.Ts);
% end
% 
% clear theta Ruu Ryu Ryy RU RY RYU fYU fY na nb nk
% 
% w=linspace(0,pi/Prps.Ts,N/2+1);
% 
% [m,p] = bode(Ghat,w);
% [mS,pS] = bode(Step.tf,w);