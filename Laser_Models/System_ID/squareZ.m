function squareZ(M,N,duty)
% M is the number of periods, N is the samples per period, and duty is the
% duty cycle.
squareZ = @(M, N, duty)repmat([ones(floor(N*duty/100), 1); -ones(ceil(N*(100-duty)/100), 1)], M, 1);
end