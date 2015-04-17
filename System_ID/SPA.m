function [ P,u,y, ruu, ruu_weighted, ryu, ryu_weighted ] = SPA(N,sys,gamma)
% ETFE with averaging aka SPA
P=[];
ruu=[];
ruu_weigted=[];
ryu=[];
ryu_weighted=[];
Ruu=[];
Ruu_weigted=[];
Ryu=[];
Ryu_weighted=[];
Suu = [];
Syu = [];
for k=1:100,
    u=randn(N,1).*hanning(N);
    y=lsim(sys,u)+0.01*randn(length(u),1);
    if k==1,
        a = u;
        b = y;
    end;

    
    % Compute Ruu
    Ruu=xcorr(u,u,N/2);
    Ryu=xcorr(y,u,N/2);
    
%     % NOTE, ALTERNATIVE:
%     Ruu=real(ifft(fft(u).*conj(fft(u))));
%     Ruu=Ruu([N/2+1:N 1:N/2+1]);    
%     Ryu=real(ifft(fft(y).*conj(fft(u))));
%     Ryu=Ryu([N/2+1:N 1:N/2+1]);
    
    
    % multiply with hanning window of size gamma
    W = [zeros((N-gamma)/2,1);hanning(gamma+1);zeros((N-gamma)/2,1)];
    Ruu_weighted = Ruu.*W;    
    Ryu_weighted = Ryu.*W;    
    
    % plot Ruu and weighted Ruu
    if k==1,
        ruu = Ruu;
        ruu_weighted = Ruu_weighted;
        ryu = Ryu;
        ryu_weighted = Ryu_weighted;
    end
    % make it suitable for fft
    Suu=1/N*fft([Ruu_weighted(N/2+1:N);Ruu_weighted(1:N/2)]);
    Syu=1/N*fft([Ryu_weighted(N/2+1:N);Ryu_weighted(1:N/2)]);
    
    % check if it went O.K.
    if max(abs(imag(Suu)))>1e-13,
        error('FFT must be real valued')
    end    
    Suu=real(Suu);
    
    
    P=[P Suu(1:N/2+1).\Syu(1:N/2+1)];
end;

end





