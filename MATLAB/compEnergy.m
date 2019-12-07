function energy = compEnergy(sig)
% Computes the energy of signal sig
% Input     :   sig     :   Array representing the signal to compute
% Output    :   energy 	:   Value representing the energy of sig

    energy = sum(sig(1 : length(sig)).^2);
end

