function [ P,a,b ] = ETFE(Case, N,sys)
% ETFE with non-zero initial and non-zero end conditions
P=[];
for k=1:100,
    if strcmp(num2str(Case),'NonZeroICEC')
        u=randn(N+50,1);
        y=lsim(sys,u);
        u=u(51:N+50);
        y=y(51:N+50);
    elseif strcmp(num2str(Case),'NonZeroICZeroEC')
        u=randn(N+50,1);
        u(N:N+50)=0*u(N:N+50);
        y=lsim(sys,u);
        u=u(51:N+50);
        y=y(51:N+50);
    elseif strcmp(num2str(Case),'ZeroICNonZeroEC')
        u=randn(N,1);
        u(1:50)=0*u(1:50);
        y=lsim(sys,u);
    elseif strcmp(num2str(Case),'ZeroICEC')
        u=randn(N,1);
        u(1:50)=0*u(1:50);
        u(N-50:N)=0*u(N-50:N);
        y=lsim(sys,u);
    elseif strcmp(num2str(Case),'PeriodicInput')
        u=randn(N,1);
        u=[u;u;u];
        y=lsim(sys,u);
        u=u(2*N+1:3*N);
        y=y(2*N+1:3*N);
    elseif strcmp(num2str(Case),'BurstInput')
        u=randn(N,1).*hanning(N);
        y=lsim(sys,u);
    elseif strcmp(num2str(Case),'BurstInput_OutputNoise')
        u=randn(N,1).*hanning(N);
        y=lsim(sys,u)+0.01*randn(length(u),1);
    end
    if k==1,
        a = u;
        b = y;
    end
    Y=fft(y);U=fft(u);
    P=[P U(1:N/2+1).\Y(1:N/2+1)]; % ETFE
end;
end
