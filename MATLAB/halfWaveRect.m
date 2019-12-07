function rect_sig = halfWaveRect(sig)
% Applies an half-wave rectification to the input signal
% Input     :   sig         :   Signal on which to apply the half 
%                               wave rectification
% Output    :   rect_sig	:   The half wave rectified signal sig

    rect_sig = zeros(length(sig) , 1);
    
    for i = 1 : length(sig)
        rect_sig(i) = max(0, sig(i));   % If sig(i) is negative, takes value 0,
                                        % otherwise is unmodified
    end
end

