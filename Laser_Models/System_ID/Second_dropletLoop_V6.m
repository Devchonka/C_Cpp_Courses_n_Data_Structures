% K_bar that simplifies controller
% Loops are simplified
function [Uy,Y] = Second_dropletLoop_V6(Kb,r1,a,b)

% Basic Parameters
tau=1.1e-3; % 1.1 msec delay
p = -1600; % pole at 1100 rad/sec
fs = 50e3; % Sampling freq
ts = 1/fs; % Sampling time
nd = tau/ts; % # samples to delay
Nsamples=1000; % simulation samples

Ad = exp(p*ts);
Bd = 1-Ad;

% Initialize for Loop
Y = zeros(length(r1),Nsamples); Yp = zeros(length(r1),Nsamples);
Uy = zeros(length(r1),Nsamples);
Upy = zeros(length(r1),Nsamples);

% Heart of the Model
for kk = 1:length(r1)
    for k = 1:Nsamples

        % Droplet y position to EUV
        Y(kk,k) = a*exp(-b*((r1(kk)-Upy(kk,k))^2)); % Equation (1)
        Yp(kk,k) = saturFun(Y(kk,k),-2,8); % Equation (3)
        if k == Nsamples;break;end
             
        % EUV to droplet y position
        if k > nd % after delay of nd
            Upy(kk,k+1) = Kb*(Ad*Upy(kk,k)+Bd*Yp(kk,k-nd)); % Equation (4)
        end
        Uy(kk,k+1) = r1(kk)-Upy(kk,k+1); % for plotting
    end
end
end