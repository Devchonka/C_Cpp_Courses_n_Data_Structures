function  [y,t,eigen]=simulateNoEstim(sys,F,N,Xo)
% simulate state without estimator

[A,B,C,D]=ssdata(sys);

t=0:N;
y=zeros(length(t),1);
x=Xo;
y(1)=C*Xo;

eigen=zeros(size(N));
for n=1:N
    u=-F{n}*x;  % find control
    y(n+1)=C*x;
    x=A*x+B*u;% simulate
    
    eigen(n)=max(abs(eig(A-B*F{n}))');
    
end

end

