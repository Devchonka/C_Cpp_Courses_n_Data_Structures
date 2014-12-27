function [ freq, mag, phase, g] = EstimBode( N,sys )

% Hwk 1 : Elena M.

ru = zeros(N,1);
ruy = zeros(N,1);
for k=1:100, 
    u=randn(N,1).*hanning(N);
    u(1:50)=0*u(1:50);
    u(N-50:N)=0*u(N-50:N);
    y=lsim(sys,u);
end

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
freq=linspace(0,pi,length(mag));
end

