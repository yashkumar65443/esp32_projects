# ESP32 to Microsoft Azure IoT Hub Telemetry (MQTT)

An enterprise IoT telemetry application connecting an **ESP32** microcontroller directly to **Microsoft Azure IoT Hub** over encrypted **MQTT**. It streams ambient temperature and relative humidity telemetry from a **DHT11** sensor in real time.

---

## 📌 Architecture

```text
┌─────────────────┐
│  DHT11 Sensor   │
└────────┬────────┘
         │ (GPIO 4)
         ▼
┌─────────────────┐       MQTT over TLS (Port 8883)       ┌────────────────────────┐
│      ESP32      ├──────────────────────────────────────►│ Microsoft Azure IoT Hub │
└─────────────────┘                                       └───────────┬────────────┘
         ▲                                                            │
         └───────────── Delivery Confirmation ACK ────────────────────┘
```

---

## 📊 Telemetry Payload Format
Telemetry packets are formatted as JSON objects:
```json
{
  "deviceId": "ESP32DEVICELIVE",
  "messageId": 1,
  "Temperature": 27.8,
  "Humidity": 62.0
}
```

---

## 🛠️ Hardware Requirements & Pinout

| Component Pin | Connection | ESP32 Pin |
| :--- | :--- | :--- |
| **DHT11 Pin 1 (VCC)** | Power Supply | 3.3V |
| **DHT11 Pin 2 (DATA)**| Signal Line  | **GPIO 4** (with 10kΩ pull-up resistor to 3.3V) |
| **DHT11 Pin 3 (NC)**  | Not Connected| N/A |
| **DHT11 Pin 4 (GND)** | Ground       | GND |

---

## 💻 Arduino IDE Libraries Required
Install the following libraries via the Arduino Library Manager:
1. **AzureIoTHub** (by Microsoft)
2. **Esp32MQTTClient**
3. **DHT sensor library** (by Adafruit)
4. **Adafruit Unified Sensor** (by Adafruit)

---

## 🚀 Setup & Azure Configuration

### 1. Register Device in Azure IoT Hub
1. Log in to the [Azure Portal](https://portal.azure.com).
2. Navigate to your **IoT Hub** $\rightarrow$ **Device management** $\rightarrow$ **Devices**.
3. Click **+ Add Device**, specify a `Device ID` (e.g., `ESP32DEVICELIVE`), and click **Save**.
4. Click on the created device and copy the **Primary Connection String**:
   ```text
   HostName=<YOUR_HUB>.azure-devices.net;DeviceId=<YOUR_DEVICE>;SharedAccessKey=<YOUR_KEY>=
   ```

### 2. Configure Sketch
Open `DAY12AZURE1/DAY12AZURE1.ino` and replace the credentials:
```cpp
// Wi-Fi Credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Azure IoT Hub Device Connection String
static const char* connectionString = "HostName=YOUR_IOTHUB_NAME.azure-devices.net;DeviceId=YOUR_DEVICE_ID;SharedAccessKey=YOUR_SHARED_ACCESS_KEY=";
```

### 3. Flash & Monitor
1. Select your ESP32 board and COM port in Arduino IDE.
2. Click **Upload** and open the Serial Monitor at **115200 baud**.
3. You should see:
   * Wi-Fi connected with assigned IP address.
   * IoT Hub MQTT connection established.
   * Periodic telemetry packets dispatched with receipt acknowledgments (`Send Confirmation Callback finished.`).

---

## 🔍 Monitoring Telemetry on Azure
To verify live messages in real time:
* **Via Azure CLI**:
  ```bash
  az iot hub monitor-events --hub-name <YOUR_HUB_NAME> --device-id <YOUR_DEVICE_ID>
  ```
* **Via Azure IoT Explorer**: Install the [Azure IoT Explorer desktop tool](https://github.com/Azure/azure-iot-explorer) to view live telemetry graphs and incoming payloads.
