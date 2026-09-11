% ThingSpeak MATLAB Analysis - Automated Alert Notification System via IFTTT
% Reads real-time telemetry from ThingSpeak and triggers IFTTT Webhooks for notifications.

% --- CONFIGURATION ---
channelID   = 0000000;                      % Replace with your ThingSpeak Channel ID
readAPIKey  = 'YOUR_THINGSPEAK_READ_KEY';   % Replace with your ThingSpeak Read API Key
iftttKey    = 'YOUR_IFTTT_WEBHOOK_KEY';     % Replace with your IFTTT Webhook Key
eventName   = 'dht11';                      % Replace with your IFTTT Event Name

% Construct API Endpoints
iftttURL       = strcat('https://maker.ifttt.com/trigger/', eventName, '/with/key/', iftttKey);
thingSpeakURL  = strcat('https://api.thingspeak.com/channels/', string(channelID), '/fields/1/last.txt');
thingSpeakURLL = strcat('https://api.thingspeak.com/channels/', string(channelID), '/fields/2/last.txt');

% --- FETCH TELEMETRY ---
lastValue  = str2double(webread(thingSpeakURL, 'api_key', readAPIKey));   % Field 1: Humidity
lastValue1 = str2double(webread(thingSpeakURLL, 'api_key', readAPIKey));  % Field 2: Temperature

% --- HUMIDITY THRESHOLD CHECK ---
if (lastValue < 75)
    disp(lastValue);
    Message = 'HUMIDITY is normal';
    disp(Message);
    webwrite(iftttURL, 'value1', lastValue, 'value2', Message);
else
    disp(lastValue);
    Message = 'HUMIDITY is Abnormal';
    disp(Message);
    webwrite(iftttURL, 'value1', lastValue, 'value2', Message);
end

% --- TEMPERATURE THRESHOLD CHECK ---
if (lastValue1 > 34)
    disp(lastValue1);
    Message = 'Temperature value is abnormal';
    disp(Message);
    webwrite(iftttURL, 'value1', lastValue1, 'value2', Message);
else
    disp(lastValue1);
    Message = 'Temperature value is normal';
    disp(Message);
    webwrite(iftttURL, 'value1', lastValue1, 'value2', Message);
end
