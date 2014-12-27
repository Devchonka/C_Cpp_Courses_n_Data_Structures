function [ P, H, Ruu_weighted, Ryu_weighted, W ] = LS_SPA( N, gamma, Ruu, Ryu, Ryy)

% Function to find P, Spectral Analysis Estimate

% P = G(hat)_SPA (w)

% Averaging with the window of width gamma
W=[zeros((N-gamma)/2,1);hanning(gamma+1);zeros((N-gamma)/2,1)];

Ruu_weighted = Ruu.*W;
Ryu_weighted = Ryu.*W;


if nargin < 5
    Ryy_weighted = zeros(size(Ryu));
else
    Ryy_weighted = Ryy.*W;
end

% make it suitable for fft
Suu=1/N*fft([Ruu_weighted(N/2+1:N);Ruu_weighted(1:N/2)]);
Syu=1/N*fft([Ryu_weighted(N/2+1:N);Ryu_weighted(1:N/2)]);
Syy=1/N*fft([Ryy_weighted(N/2+1:N);Ryy_weighted(1:N/2)]);

% spectral estimate
P=Suu(1:N/2+1).\Syu(1:N/2+1); % SPA estimate
H=Syy(1:N/2+1)-Suu(1:N/2+1).\(abs(Syu(1:N/2+1)).^2);
end

