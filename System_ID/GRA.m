function [tfGRA,ssGRA ] = GRA( Wing )
% General Realization Algorithm to determine lowest order model best
% capturing system dynamics from general input


% detrend data
% Wing.u=detrend(Wing.u);
% Wing.y=detrend(Wing.y);

% cut off rank based on singular values plot
n=7;

% N1 = Wing.N/2-2;
N = length(Wing.u);

N1 = 860; % 850
N2 = 5238;  % N1*6

% Calculate Hy : Matrix of outputs
Hy = zeros(N1,N2);
for j=1:N2
    Hy(:,j)=Wing.y(j+1:N1+j);
end

% Calculate Hu : Matrix of inputs
Hu = zeros(N1+1,N2);
for j=1:N2
    Hu(:,j)=Wing.u(j+1:N1+1+j);
end

% Calculate Hu(orthogonal) : null projection by pseudoinverse
Huo = eye(size(Hu,2)) - Hu'*pinv(Hu*Hu')*Hu;

Q = Hy*Huo;
[U,S,V] = svd(Q);

Sigmas = diag(S);

% Plot the singular values so I can decide on smallest model rank, PROBLEM
% IS THAT MOST MY SINGULAR VALUES ARE ALMOST ZERO!!! So smthg is wrong
% before this :[
figure(6)
plot(1:20,Sigmas(1:20), 'r*', 'LineWidth',1.5);
title ('First 20 Singular Values from weighted Hankel matrix Q');
xlabel('# singular values'); ylabel('$\sigma$ ','interpreter','latex');
xlim([0 20]);
print -depsc /home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig6

S = S(1:n,1:n); V = V(1:end,1:n); U = U(1:end,1:n); % reduce rank
Q1 = U*S^.5;
% Q2 = S^.5*V'; do not need Q2
Q1left = (S^-.5)*U';
Q2left = V*(S^-.5);

% Find Qshift
Hy = zeros(N1+1,N2);
for j=1:N2
    Hy(:,j)=Wing.y(j+1:N1+j+1);
end

Hu = zeros(N1+2,N2);
for j=1:N2
    Hu(:,j)=Wing.u(j+1:N1+2+j);
end
Huo = eye(N2) - Hu'*pinv(Hu*Hu')*Hu;

Qshift = Hy*Huo;
Qshift = Qshift(2:end, :,:);

A = Q1left*Qshift*Q2left;
C = Q1(1,:);

% Calculate B, D via Least Squares

ny = size(Wing.y, 2);
nu = size(Wing.u, 2);
n = size(A, 1);
nk =0; % dont actually know how to know the number of delays for nk :[

% Calculate the regressor for B.
phiB = zeros(n*nu, ny*N);

ik = 1;
for i = 1:nu
    for j = 1:ny
        %             fprintf('\b\b\b\b%03d%%', round(ik/num*100));
        ik = ik+1;
        uk = [zeros(N, j-1), Wing.u(:, i), zeros(N, ny-j)];
        x = ltitr(A', C', uk);
        
        % Copy the state sequence into the regressor for B.
        for k = 1:N
            phiB(n*(i-1)+1:n*i, ny*(k-1)+j) = x(k, :)';
        end
    end
end

% Calculate the regressor for x0.
%     fprintf('Computing x0 regressor...\n\n');

phix0 = [];


% Calculate the regressor for D if needed.

if nk == 0
    phiD = zeros(nu*ny, ny*N);
    for k = 1:N % Kronecker product with identity
        for i = 1:nu
            phiD(ny*(i-1)+1:ny*i, ny*(k-1)+1:ny*k) = eye(ny)*Wing.u(k, i);
        end
    end
else
    phiD = [];
end

% Vectorize y to use in the least-squares problem.
y = Wing.y';
y = y(:);

% Find the least-squares solution for x0, B, D.
theta = [phiB', phix0', phiD']\y;

% Extract the parameters from theta.
B = reshape(theta(1:n*nu), n, nu);


if nk == 0
    
    D = reshape(theta(n*nu+1:end), ny, nu);
else
    D = zeros(ny, nu);
end

tfGRA = tf(ss(A,B,C,D,Wing.Ts));
ssGRA = ss(A,B,C,D,Wing.Ts);

impGRA = impulse (idtf(ssGRA));
figure(7)
stem(impGRA(1:21),'k*')
% axis([0 0.18 -2 2.5])
title ('Impulse Response of n=7 GRA Model');
% print -depsc /home/yelena/Desktop/ResumeTexmakerTrial\SystemID\fig7

end

