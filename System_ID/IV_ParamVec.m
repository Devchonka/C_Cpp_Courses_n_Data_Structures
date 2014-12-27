function [ theta, thetaR ] = IV_ParamVec( N, G0hat, u )

% instrument variable estimation, similar to LS
% noiseless

yhat = lsim(G0hat,u);

Ruu=xcorr(u,u,N/2);
Ryu=xcorr(yhat,u,N/2);
Ryy=xcorr(yhat,yhat,N/2);

RU=toeplitz(Ruu(N/2+1:N/2+1+3));
RY=toeplitz(Ryy(N/2+1:N/2+1+2));
RYU=toeplitz(-Ryu(N/2+1-1:N/2+1+2),-Ryu(N/2+1-1:-1:N/2+1-3));
fYU=Ryu(N/2+1:N/2+1+3);
fY=-Ryy(N/2+2:N/2+2+2);

% estim param using LS xcorr
theta=[RU RYU;RYU' RY]\[fYU;fY]; 
% estim param using direct regression: using eta and instrument var
thetaR=[u(4:N) u(3:N-1) u(2:N-2) u(1:N-3) -yhat(3:N-1) -yhat(2:N-2) -yhat(1:N-3)]\yhat(4:N);

end

