function iss = compIss(ixx, inn)
% Computes the value of Iss
% Inputs    :   ixx     :   noisy signal's periodogram
%               inn     :   noise periodogram
% Output    :   iss     :   clean signal's periodogram

    iss = max(0, mean(ixx) - mean(inn));
end

