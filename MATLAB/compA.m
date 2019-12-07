function a = compA(rss)
% Computes the prediciton coefficients of clean speech
% Input     :   rss     :   autocorrelation coefficients of clean speech
% Output    :   a       :   prediction coefficients of clean speech

    a = levinson(rss);
end

