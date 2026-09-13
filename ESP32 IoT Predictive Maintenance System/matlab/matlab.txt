% ThingSpeak MATLAB Analysis - Predictive Maintenance & Vibration Classifier
% Uses an Artificial Neural Network (RBF) to classify machine health and fire IFTTT alerts.

% --- CONFIGURATION ---
channelID   = 0000000;                     % Replace with your ThingSpeak Channel ID
readAPIKey  = 'YOUR_THINGSPEAK_READ_KEY';  % Replace with your ThingSpeak Read API Key
iftttKey    = 'YOUR_IFTTT_KEY';            % Replace with your IFTTT Webhook Key
eventName   = 'test';                      % Replace with your IFTTT Event Name

% Construct API URLs
iftttURL      = strcat('https://maker.ifttt.com/trigger/', eventName, '/with/key/', iftttKey);
thingSpeakURL = strcat('https://api.thingspeak.com/channels/', string(channelID), '/fields/1/last.txt');

% --- DATA ACQUISITION ---
lastValue = str2double(webread(thingSpeakURL, 'api_key', readAPIKey));
disp('Latest Vibration Intensity Value:');
disp(lastValue);

% --- NEURAL NETWORK INFERENCE ---
net = neuralnet;
Y = net(lastValue);
Y = round(Y);
disp('Predicted Machine Health State:');
disp(Y);

% --- CLASSIFICATION & ALERT DISPATCH ---
switch Y
    case 1
        Message = 'Machine is Normal';
        disp(Message);
        webwrite(iftttURL, 'value1', lastValue, 'value2', Message);
    case 2
        Message = 'Machine is Medium (Warning: Early Wear Detected)';
        disp(Message);
        webwrite(iftttURL, 'value1', lastValue, 'value2', Message);
    case 3
        Message = 'Machine is Abnormal (Critical Failure Risk!)';
        disp(Message);
        webwrite(iftttURL, 'value1', lastValue, 'value2', Message);
    otherwise
        disp('Unknown State');
end

% --- RBF NEURAL NETWORK DEFINITION ---
function net = neuralnet
    X = [0:254];
    TC1 = 1;
    for i = 1:254
        if i < 75
            TC1 = [TC1 1];
        elseif i >= 75 && i <= 150
            TC1 = [TC1 2];
        else
            TC1 = [TC1 3];
        end
    end
    net = newrbe(X, TC1); % Exact radial basis neural network
end
