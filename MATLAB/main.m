%% Shapping of input signal
clear;      % Clear command window
clc;        % Clear workspace

% noisy_sig is a colon vector of length 19559
load("noisy_sig.mat", "noisy_sig");
y = noisy_sig;
%load("1z88153a8.mat", "sigd");
%y = sigd;

Fs = 8000;                  % Sample frequency
Ts = 1/Fs;                  % Sample time
L = length(y);              
frame_size = 0.01;          % Size of a frame in seconds

% Resize the input signal to be a multiple of the frame size
y = y(1 : round((L-1)*Ts, 1) * Fs);

L = length(y);              % Update length of input signal             
t = 0 : Ts : (L-1)*Ts;      % Time domaine

% Signal in the time domain
figure(1)
plot(t, y);
title("Input signal in time domain");
xlabel("Time (s)");
ylabel("Amplitude");

% Shape the matrix into 240 10ms-long frames
x = reshape(y, [round((L-1)*Ts, 1)/frame_size frame_size*Fs]);

%% Initialization

[lin, col] = size(x);
Rxx = zeros(lin, col);
Ixx = zeros(lin, col);
Inn = zeros(lin, col);
Iss = zeros(lin, col);
complex_Iss = zeros(lin, col);
Rss = zeros(lin, col);
a   = zeros(lin, col);

Eth = 2.5;                      % Energy threshold
ref_inn(1:3, 1:col) = 1000;     % Voluntarily big to force the update at the beginning

%% Loop over the frames
for i = 1 : length(x)
    
    Rxx(i, 1:end) = compRxx(x(i, 1:end));
    Rxx(i, 1:end) = Rxx(i, 1:end) / Rxx(i, 1);								% Normalize the values
    
    Ixx(i, 1:end) = fft(Rxx(i, 1:end));                                     % Ixx is complex
    
    Inn(i, 1:end) = compInn(x(i, 1:end), Eth, ref_inn, abs(Ixx(i, 1:end)));	% Inn is real and represents its module
    
    ref_inn = updateRefInn(ref_inn, Inn(i, 1:end));
    
    Iss(i, 1:end) = compIss(abs(Ixx(i, 1:end)), Inn(i, 1:end));				% Iss is real and represents its module
    complex_Iss = Iss(i, 1:end) .* exp(1j * angle(Ixx(i, 1:end)));			% Iss is now complex for the inverse fft
																			% It is built with the module of itself and the angle of Ixx 
    
    Rss(i, 1:end) = compRss(complex_Iss);									% Rss is complex
    Rss(i, 1:end) = Rss(i, 1:end) / Rss(i, 1);								% Normalize the values
    
    a(i, 1:end) = compA(real(Rss(i, 1:end)));								% Use the real part of Rss because the signal we want is real
    a(i, 1:end) = a(i, 1:end) / a(i, 1);									% Normalize the values
    
end

%% Plot the prediction coefficients

a = a';				% Transpose the matrix
vecta = a(:);		% Transform the matrix into a colon vector

figure(2);
plot(vecta);
title("Prediction coefficients");
xlabel("Coefficient number");
ylabel("a");

%% Plot the estimated signal

vecta = vecta';         % Transpose the vector
est_x = filter([0 -vecta(2:end)], 1, y);        % Filter the signal

figure(3);
plot(t, est_x);
title("Estimated signal in time domain");
xlabel("Time (s)");
ylabel("Amplitude");



