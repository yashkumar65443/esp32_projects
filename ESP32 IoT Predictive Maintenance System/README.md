# ESP32 IoT Predictive Maintenance System (Vibration Analysis + Neural Network)

An industrial IoT predictive maintenance and machine health monitoring solution. It samples vibration signals using an **ESP32** and a digital vibration sensor, transmits cumulative vibration intensity to **ThingSpeak**, and executes an **Artificial Neural Network (Radial Basis Function - RBF)** in the cloud to predict mechanical failure risk and dispatch real-time alerts via **IFTTT Webhooks**.

---

## 📌 Architecture

```text
┌─────────────────────────────────┐
│ ESP32 + Vibration Sensor (GPIO 4│
│  • Samples 256-cycle pulse train│
│  • Calculates Intensity (0–255) │
└──────────────┬──────────────────┘
               │  HTTP POST to ThingSpeak (Field 1)
               ▼
┌─────────────────────────────────┐
│     ThingSpeak IoT Channel      │
└──────────────┬──────────────────┘
               │  Periodic Execution via TimeControl
               ▼
┌─────────────────────────────────┐
│   ThingSpeak MATLAB Analysis    │
│  • Fetches latest vibration score│
│  • Evaluates RBF Neural Network │
│  • Classifies Health State      │
└──────────────┬──────────────────┘
               │  webwrite() to maker.ifttt.com
               ▼
┌─────────────────────────────────┐
│         IFTTT Webhooks          │
│   • "Machine is Normal"         │
│   • "Machine is Medium"         │
│   • "Machine is Abnormal"       │
└──────────────┬──────────────────┘
               │
               ▼
┌─────────────────────────────────┐
│   📱 Factory Operator Alert     │
│   (Push Notification / Email)   │
└─────────────────────────────────┘
```

---

## 📂 Project Structure

```text
├── predictive/
│   └── predictive.ino            # ESP32 vibration acquisition & cloud upload
├── matlab/
│   ├── predictive_maintenance.m  # Production MATLAB Analysis script
│   └── matlab.txt                # Copy-pasteable script for ThingSpeak Web Editor
└── README.md                     # Architecture, wiring & setup instructions
```

---

## 🛠️ Hardware Requirements & Pinout

| Component Pin | Connection | ESP32 GPIO |
| :--- | :--- | :--- |
| **SW-420 VCC** | Power Supply | 3.3V |
| **SW-420 GND** | Ground | GND |
| **SW-420 DO (Digital Out)** | Vibration Signal | **GPIO 4** |

---

## 🔬 Vibration Sampling & Machine Health States

### 1. Window Sampling Algorithm
Instead of measuring a single instantaneous pulse, the ESP32 samples 256 consecutive clock cycles:
$$\text{Vibration Score} = \sum_{i=0}^{255} \text{digitalRead}(\text{GPIO 4})$$
This yields an intensity score ranging from $0$ (stationary machine) to $255$ (severe continuous vibration).

### 2. RBF Neural Network Classification
The MATLAB script generates an exact Radial Basis Network (`newrbe`) that categorizes machine health into 3 distinct operational levels:

| Class ($Y$) | Vibration Score Range | Operational Health Status | Action Taken |
| :---: | :---: | :--- | :--- |
| **1** | $< 75$ | **Machine is Normal** | Optimal operating conditions. |
| **2** | $75 \le \text{Score} \le 150$ | **Machine is Medium (Warning)** | Early mechanical wear or loose mounting detected. Schedule inspection. |
| **3** | $> 150$ | **Machine is Abnormal (Critical)** | High probability of imminent bearing/motor failure. Urgent operator intervention required. |

---

## 🚀 Setup & Configuration

### 1. ThingSpeak Configuration
1. Create a channel on [ThingSpeak](https://thingspeak.com) with **Field 1** named `Vibration Intensity`.
2. Open `predictive/predictive.ino` and enter your Wi-Fi credentials, Channel ID, and Write API Key.
3. Flash the sketch to your ESP32 at **115200 baud**.

### 2. MATLAB Analysis & IFTTT Setup
1. In ThingSpeak, go to **Apps** $\rightarrow$ **MATLAB Analysis** $\rightarrow$ **New**.
2. Paste the code from `matlab/predictive_maintenance.m`.
3. In [IFTTT](https://ifttt.com), create an applet:
   * **If This**: Webhooks $\rightarrow$ Receive a web request (Event name: `test`).
   * **Then That**: Notifications (*"Send a notification from the IFTTT app"*) or Email.
4. Replace `channelID`, `readAPIKey`, and `iftttKey` in the script.
5. Attach a **TimeControl** app to run the analysis automatically every 5 to 15 minutes!
