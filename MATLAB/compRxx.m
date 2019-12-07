function rxx = compRxx(sig)
% Computes the auto-correlation coefficients of signal sig
% Input     :   sig    :    Vector representing the signal to compute
% Output    :   rxx    :    Vector representing the auto-correlation coefficients
%                           of signal sig

    rxx = zeros(length(sig) , 1); 

    % Sets the Rxx
    for i = 1 : length(sig)
        % Computes the Rxx
        for m = 1 : (length(sig) - abs(i))
           rxx(i) = rxx(i) + sig(m) * sig(m + abs(i));
        end
    end
end





