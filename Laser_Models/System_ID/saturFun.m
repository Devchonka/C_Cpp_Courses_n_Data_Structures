function OutVector=saturFun(InVector,lowLim,UpLim)

% OutVector = zeros(size(InVector));

% for i  = 1: length(InVector)
%     OutVector(i) = max(lowLim,min(UpLim,16*InVector(i)-19));
%     
% end

OutVector= max(lowLim,min(UpLim,16*InVector-19));

end