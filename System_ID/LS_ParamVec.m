function [ v, y, Ruu, Ryu, Ryy, theta, thetaR ] = LS_ParamVec( N, G0, H0, lambda, u )

% Least Squares to find theta(hat) estimate

% lambda is noise level

ynf=lsim(G0,u);

if lambda==0
    v = zeros(size(ynf));
else
    e=sqrt(lambda)*randn(N,1);
    v=lsim(H0,e);
end

y=ynf+v;

Ruu=xcorr(u,u,N/2);
Ryu=xcorr(y,u,N/2);
Ryy=xcorr(y,y,N/2);

RU=toeplitz(Ruu(N/2+1:N/2+1+3));
RY=toeplitz(Ryy(N/2+1:N/2+1+2));
RYU=toeplitz(-Ryu(N/2+1-1:N/2+1+2),-Ryu(N/2+1-1:-1:N/2+1-3));
fYU=Ryu(N/2+1:N/2+1+3);
fY=-Ryy(N/2+2:N/2+2+2);

% estim param using LS xcorr
theta=[RU RYU;RYU' RY]\[fYU;fY]; 
% estim param using direct regression
thetaR=[u(4:N) u(3:N-1) u(2:N-2) u(1:N-3) -y(3:N-1) -y(2:N-2) -y(1:N-3)]\y(4:N);

end

