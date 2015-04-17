
function Leg_Names = legend_names(var,r1)

% Leg_Names = cell(size(r1));
% 
% for i = 1:numel(r1)
%     Leg_Names{i} = sprintf('y for r = %0.1f',r1(i));
% end

Leg_Names = cellfun(@(x) sprintf('%s for r = %0.1f',var,x),num2cell(r1),'UniformOutput',0);
end
