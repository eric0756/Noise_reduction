function rss = compRss(iss)
% Computes the autocorrelation coefficients of the clean signal from Iss
% Input     :   iss     :   Array representing the periodogram of clean signal
% Output    :   rss     :   Array representing the autocorrelation coefficients
%                           of clean signal

    rss = (length(iss) / 2) * ifft(iss);
    
    %figure(2);
    %plot(1:length(rss), rss);
    %title("Rss");
end

