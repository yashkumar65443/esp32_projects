# ESP32 IFTTT Email Alert & Excel / Google Sheets Logger

An automated IoT notification and data-logging system using an **ESP32** and a **DHT11** sensor integrated with **IFTTT Webhooks**. It automatically appends environmental telemetry to an **Excel / Google Sheets spreadsheet** and sends instant **Email Alerts** when temperatures exceed safe limits.

---

## 📌 Architecture

```text
┌─────────────────────────┐
│  ESP32 + DHT11 (GPIO 4) │
└────────────┬────────────┘
             │  HTTP GET to maker.ifttt.com
             ▼
┌─────────────────────────┐
│     IFTTT Webhooks      │
└────────────┬────────────┘
             ├── Event "temp_data" ────────► [Google Sheets / Excel] (New row logged)
             └── Event "temp_datatemp30" ──► [Email Alert Service]   (Triggered if Temp > 29°C)
```

---

## 📂 Included Sketches

| Sketch Folder | Features | Trigger Interval |
| :--- | :--- | :--- |
| **`iotexcel/`** | Streams Temperature & Humidity directly to a Google Sheets / Excel spreadsheet. | Every 10 seconds |
| **`sendemail/`** | Dual-event firmware: logs to spreadsheet continuously, and sends an **instant Email alert** whenever temperature exceeds **29°C**. | Every 30 seconds |

---

## 🛠️ Hardware Wiring (DHT11 to ESP32)

| DHT11 Pin | Description | ESP32 GPIO |
| :--- | :--- | :--- |
| **Pin 1 (VCC)** | Power Supply | 3.3V |
| **Pin 2 (DATA)**| Sensor Signal | **GPIO 4** (with a 10kΩ pull-up resistor to 3.3V) |
| **Pin 3 (NC)**  | Not Connected | N/A |
| **Pin 4 (GND)** | Ground | GND |

---

## 💻 Arduino IDE Libraries Required
Install the following libraries via **Tools** $\rightarrow$ **Manage Libraries...**:
1. **DHT sensor library** (by Adafruit)
2. **Adafruit Unified Sensor** (by Adafruit)
3. **WiFi** & **HTTPClient** (built into the official ESP32 Arduino core)

---

## 🚀 IFTTT Configuration Guide

### 1. Spreadsheet Logger Applet (`temp_data`)
1. Go to [ifttt.com/create](https://ifttt.com/create).
2. **If This**: Search for **Webhooks** $\rightarrow$ select **Receive a web request**.
   * **Event Name**: `temp_data`
3. **Then That**: Search for **Google Sheets** $\rightarrow$ select **Add row to spreadsheet**.
   * **Spreadsheet name**: `ESP32_DHT11_Log`
   * **Formatted row**: `{{OccurredAt}} ||| {{Value1}} ||| {{Value2}}`
4. Click **Create Action** $\rightarrow$ **Finish**.

---

### 2. Email Alert Applet (`temp_datatemp30`)
1. Click [ifttt.com/create](https://ifttt.com/create).
2. **If This**: Select **Webhooks** $\rightarrow$ **Receive a web request**.
   * **Event Name**: `temp_datatemp30`
3. **Then That**: Select **Email** $\rightarrow$ **Send me an email** (or **Gmail**).
   * **Subject**: `🚨 WARNING: High Temperature Detected! ({{Value2}}°C)`
   * **Body**: `Alert: The current temperature has exceeded safe thresholds.<br>Temperature: {{Value2}}°C<br>Humidity: {{Value1}}%<br>Time: {{OccurredAt}}`
4. Click **Create Action** $\rightarrow$ **Finish**.

---

### 3. Retrieve Your Webhook Key
* Open [ifttt.com/maker_webhooks/settings](https://ifttt.com/maker_webhooks/settings) and copy the key from the end of the URL:
  `https://maker.ifttt.com/use/YOUR_IFTTT_KEY`

---

## 🔧 Configuring the Sketch
Open either sketch and replace the placeholders:
```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

String IFTTT_Key = "YOUR_IFTTT_KEY";
```
Upload the sketch to your ESP32 at **115200 baud**!
