function new_ref_inn = updateRefInn(ref_inn, inn)
% Updates the three last values of Inn. ref_inn(1) is the most recent value 
% while ref_inn(3) is the least recent. 
% Inputs    :   ref_inn         :   Matrix with the three last values of Inn
%           :   inn             :   Vector representing the new value of Inn
% Output    :   new_ref_inn     :   Matrix with the updated three last values of Inn

    new_ref_inn = zeros(3, length(ref_inn));
    new_ref_inn(1, 1 : end) = inn;
    new_ref_inn(2, 1 : end) = ref_inn(1, 1 : end);
    new_ref_inn(3, 1 : end) = ref_inn(2, 1 : end);
end

