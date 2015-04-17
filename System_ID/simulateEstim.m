function  [y,t,eigEstim]=simulateEstim(sys,F,N,Xo)
% simulate state estimator feedback using observer designed
t=0:N;

[A,B,C,D]=ssdata(sys);
L= place(A',C',[0.5 0.45 0.4])';

y=zeros(length(t),1);
x=Xo;
xhat=zeros(size(x));
yhat=C*xhat;%zeros(length(t),1);
y(1)=C*Xo;
    
eigEstim=zeros(size(N));
for n=1:N  
     
    yhat(n+1)=C*xhat; 
    xhat=(A-B*F{n})*xhat+L*(y(n)-yhat(n));
    
    u=-F{n}*xhat;  % find control
    x=A*x+B*u;% simulate
    y(n+1)=C*x;
        
    eigEstim(n)=max(abs(eig(A-B*F{n}))');
        
end

end

