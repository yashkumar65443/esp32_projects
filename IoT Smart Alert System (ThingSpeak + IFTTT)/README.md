# IoT Smart Alert System (ThingSpeak + IFTTT Webhooks)

An automated cloud notification and alerting bridge. This system monitors real-time environmental telemetry (such as Temperature and Humidity from an ESP32 DHT11/DHT22 sensor) stored on **ThingSpeak**, analyzes the readings against defined thresholds using **MATLAB Analysis**, and dispatches instant alerts to smartphones or email using **IFTTT Webhooks**.

---

## 📌 Architecture

```text
[ESP32 / IoT Sensor]
        │  (HTTP POST telemetry)
        ▼
[ThingSpeak Cloud Channel] (Field 1 = Humidity, Field 2 = Temperature)
        │
        ▼ (Scheduled / Triggered via TimeControl or React)
[ThingSpeak MATLAB Analysis] (ifttt_alert.m)
        │  • Reads latest data via webread()
        │  • Evaluates thresholds (Normal vs Abnormal)
        │  • Dispatches event payload via webwrite()
        ▼
[IFTTT Webhook Service] (maker.ifttt.com)
        │
        ▼
[User Notifications] (Push Notification / Email / SMS)
```

---

## 📂 Project Structure

```text
├── ifttt_alert.m   # Production MATLAB Analysis script
├── matlab.txt      # Text version for easy copy-pasting into ThingSpeak web editor
├── .gitignore      # Ignores MATLAB autosave and OS files
└── README.md       # Project setup and documentation
```

---

## 🛠️ Step-by-Step Setup Guide

### 1. Configure IFTTT (If This Then That)
1. Go to [ifttt.com](https://ifttt.com) and click **Create**.
2. **If This (Trigger)**:
   * Search for **Webhooks** $\rightarrow$ select **Receive a web request**.
   * Enter **Event Name** (e.g., `dht11`).
3. **Then That (Action)**:
   * Select **Notifications** (*"Send a notification from the IFTTT app"*) or **Email** (*"Send me an email"*).
   * In the message body, include ingredients:
     * `Value1` = Numeric reading (temperature or humidity).
     * `Value2` = Status message (e.g., *"HUMIDITY is Abnormal"*).
4. Retrieve your **IFTTT Key** from [ifttt.com/maker_webhooks/settings](https://ifttt.com/maker_webhooks/settings).

---

### 2. Configure ThingSpeak MATLAB Analysis
1. Log in to [ThingSpeak](https://thingspeak.com) and go to **Apps** $\rightarrow$ **MATLAB Analysis**.
2. Click **New**, choose **Custom (no starter code)**, and click **Create**.
3. Copy the code from `ifttt_alert.m` (or `matlab.txt`) and paste it into the editor.
4. Replace the configuration placeholders:
   ```matlab
   channelID   = 1234567;                    % Your ThingSpeak Channel ID
   readAPIKey  = 'YOUR_THINGSPEAK_READ_KEY'; % Your Channel Read API Key
   iftttKey    = 'YOUR_IFTTT_KEY';           % Your Webhook Key from IFTTT
   eventName   = 'dht11';                    % Your IFTTT Event Name
   ```
5. Click **Save and Run** to test the webhook dispatch.

---

### 3. Automate Execution (TimeControl / React)
To run the analysis automatically:
* Go to **Apps** $\rightarrow$ **TimeControl**.
* Set frequency (e.g., *Every 5 minutes* or *Every 15 minutes*).
* Action: Run **MATLAB Analysis** $\rightarrow$ select your alert script.

---

## ⚙️ Customizing Thresholds

You can adjust the boundary conditions in `ifttt_alert.m` according to your specific sensor range:
```matlab
% Humidity Threshold
if (lastValue < 75)
    Message = 'HUMIDITY is normal';
else
    Message = 'HUMIDITY is Abnormal';
end

% Temperature Threshold (°C)
if (lastValue1 > 34)
    Message = 'Temperature value is abnormal';
else
    Message = 'Temperature value is normal';
end
```
