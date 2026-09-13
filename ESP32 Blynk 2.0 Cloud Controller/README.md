# ESP32 Blynk 2.0 IoT Cloud Controller

A connected IoT application integrating an **ESP32** microcontroller with the **Blynk 2.0 (Blynk.Cloud)** platform. It enables bidirectional remote control, real-time telemetry streaming, and dynamic dashboard feedback via the Blynk Mobile App (iOS / Android) and Web Dashboard.

---

## 📌 Architecture

```text
┌───────────────────────────────┐
│   Blynk Mobile / Web App      │
│  (Button V0, LED V1, Gauges)  │
└──────────────┬────────────────┘
               │  Blynk IoT Protocol (Port 443/80)
               ▼
┌───────────────────────────────┐
│     blynk.cloud Server        │
└──────────────┬────────────────┘
               │  Bi-directional Keep-Alive Connection
               ▼
┌───────────────────────────────┐
│         ESP32 Device          │
│   • V0: Inbound Control       │
│   • V1: State Confirmation    │
│   • V2: Non-blocking Uptime   │
│   • V3: Cloud Connection Hook │
└───────────────────────────────┘
```

---

## 📊 Virtual Pin Mapping

| Virtual Pin | Direction | Type | Function |
| :--- | :--- | :--- | :--- |
| **V0** | App $\rightarrow$ ESP32 | Integer (0/1) | Input control switch or button trigger. |
| **V1** | ESP32 $\rightarrow$ App | Integer (0/1) | State confirmation / Virtual LED indicator. |
| **V2** | ESP32 $\rightarrow$ App | Integer | Live device uptime in seconds (streamed every 1s via `BlynkTimer`). |
| **V3** | ESP32 $\rightarrow$ App | String / URL | Triggered on `BLYNK_CONNECTED()` to update dashboard image and link properties. |

---

## 🛠️ Requirements

### Hardware
* Any **ESP32 Development Board** (NodeMCU-32S, ESP32 WROOM, etc.)
* Micro-USB cable
* 2.4 GHz Wi-Fi network

### Arduino IDE Libraries
Install via **Tools** $\rightarrow$ **Manage Libraries...**:
1. **Blynk** (by Volodymyr Shymanskyy)
2. **WiFi** (built into the official ESP32 Arduino core)

---

## 🚀 Step-by-Step Setup Guide

### 1. Configure Blynk.Cloud
1. Log in to [blynk.cloud](https://blynk.cloud).
2. Go to **Templates** $\rightarrow$ **+ New Template**:
   * **Name**: ESP32 Controller
   * **Hardware**: ESP32
   * **Connection Type**: WiFi
3. Click the **Datastreams** tab and add the following:
   * **V0**: Virtual Pin, Integer, Min: 0, Max: 1
   * **V1**: Virtual Pin, Integer, Min: 0, Max: 1
   * **V2**: Virtual Pin, Integer (Uptime)
4. Design your **Web Dashboard** or **Mobile App Dashboard**:
   * Add a **Switch** widget assigned to **V0**.
   * Add an **LED** widget assigned to **V1**.
   * Add a **Value Display** or **Gauge** assigned to **V2**.
5. Go to **Search** $\rightarrow$ **+ New Device** $\rightarrow$ **From Template** and copy your **Blynk Auth Token**.

---

### 2. Configure the Sketch
Open `firmware/firmware.ino` and replace the placeholder credentials:
```cpp
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";
```

---

### 3. Flash & Monitor
1. Select your ESP32 board and COM port in Arduino IDE.
2. Click **Upload** and open the Serial Monitor at **115200 baud**.
3. You will see the Blynk ASCII banner and IP address confirmation once connected:
   ```text
   [523] Connecting to WarriorsWay_2G
   [2541] Connected to WiFi
   [2541] IP: 192.168.1.50
   [2541] Ready (ping: 42ms).
   ```
4. Toggle the switch on your mobile app: the state will instantly synchronize with the ESP32 and reflect on widget V1!
