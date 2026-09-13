# ESP32 to AWS IoT Core Telemetry (SPIFFS mTLS)

An enterprise-grade secure IoT telemetry node connecting an **ESP32** microcontroller to **Amazon Web Services (AWS) IoT Core** over encrypted **MQTT (Port 8883)** using **Mutual TLS (mTLS)**. Instead of embedding large certificates directly into the source code, this firmware dynamically mounts and loads the **Amazon Root CA**, **Device Certificate**, and **RSA Private Key** from the ESP32's internal **SPIFFS flash filesystem**.

---

## 📌 Architecture

```text
┌───────────────────────────────┐
│     ESP32 Flash (SPIFFS)      │
│  • /AmazonRootCA1.pem         │
│  • /ad-certificate.pem.crt    │
│  • /ad-private.pem.key        │
└──────────────┬────────────────┘
               │  Loads certificates into WiFiClientSecure
               ▼
┌───────────────────────────────┐        mTLS over Port 8883        ┌───────────────────────────────┐
│         ESP32 Device          ├──────────────────────────────────►│       AWS IoT Core Broker     │
│   • Reads DHT11 on GPIO 4     │                                   │ (ap-south-1.amazonaws.com)    │
│   • Retrieves Device MAC ID   │◄──────────────────────────────────┤                               │
└───────────────────────────────┘        Subscribes to "ei_in"      └──────────────┬────────────────┘
               │                                                                   │
               └───────────────── Publishes JSON to "ei_out" ──────────────────────┘
```

---

## 📊 Telemetry Payload Format
The ESP32 publishes formatted JSON telemetry packets to the AWS topic **`ei_out`**:
```json
{
  "mac_Id": "24:6f:28:XX:XX:XX",
  "Temprature": "28.40",
  "Humidity": "65.00"
}
```

---

## 📂 Project Structure

```text
├── demoiot/
│   ├── demoiot.ino              # Main ESP32 firmware with PubSubClient & WiFiClientSecure
│   └── data/                    # SPIFFS folder containing X.509 certificates
│       ├── AmazonRootCA1.pem    # Amazon Root CA 1
│       ├── ad-certificate.pem.crt # AWS Device Certificate template
│       └── ad-private.pem.key   # RSA Device Private Key template
└── README.md                    # Setup and AWS configuration guide
```

---

## 🛠️ Hardware Requirements & Pinout

| DHT11 Pin | Description | ESP32 GPIO |
| :--- | :--- | :--- |
| **Pin 1 (VCC)** | Power Supply | 3.3V |
| **Pin 2 (DATA)**| Sensor Signal | **GPIO 4** (with 10kΩ pull-up to 3.3V) |
| **Pin 3 (NC)**  | Not Connected | N/A |
| **Pin 4 (GND)** | Ground | GND |

---

## 💻 Arduino IDE Libraries Required
Install the following libraries via **Tools** $\rightarrow$ **Manage Libraries...**:
1. **PubSubClient** (by Nick O'Leary)
2. **DHT sensor library** (by Adafruit)
3. **Adafruit Unified Sensor** (by Adafruit)

---

## 🚀 AWS IoT Core Setup Guide

### 1. Create a "Thing" in AWS IoT Core
1. Open the [AWS IoT Core Console](https://console.aws.amazon.com/iot).
2. Go to **Manage** $\rightarrow$ **All devices** $\rightarrow$ **Things** $\rightarrow$ **Create things**.
3. Choose **Create single thing**, name your Thing (e.g., `ESP32_Device`), and proceed.
4. Under **Device Certificate**, select **Auto-generate a new certificate (recommended)**.
5. Download:
   * **Device certificate** $\rightarrow$ save as `data/ad-certificate.pem.crt`.
   * **Private key file** $\rightarrow$ save as `data/ad-private.pem.key`.
   * **RSA 2048 bit key: Amazon Root CA 1** $\rightarrow$ save as `data/AmazonRootCA1.pem`.

### 2. Create and Attach an IoT Policy
1. Go to **Security** $\rightarrow$ **Policies** $\rightarrow$ **Create Policy**.
2. Add statements allowing:
   * `iot:Connect`
   * `iot:Publish` (Resource: `arn:aws:iot:*:*:topic/ei_out`)
   * `iot:Subscribe` (Resource: `arn:aws:iot:*:*:topicfilter/ei_in`)
   * `iot:Receive`
3. Attach this policy to your newly created certificate and **Activate** the certificate.

### 3. Copy Your AWS Endpoint
1. Go to **Settings** in the AWS IoT Core console.
2. Under **Device data endpoint**, copy your unique endpoint:
   `xxxxxxxxxxxxxx-ats.iot.<region>.amazonaws.com`

---

## 💾 Uploading Certificates to ESP32 Flash (SPIFFS)

1. Place your 3 downloaded certificate files inside the sketch's **`data/`** directory.
2. In Arduino IDE, click **Tools** $\rightarrow$ **ESP32 Sketch Data Upload** to flash the certificates into the onboard SPIFFS filesystem.
3. Open `demoiot.ino`, enter your Wi-Fi credentials and AWS MQTT endpoint, and upload the sketch.

---

## 🔍 Verifying Live Telemetry in AWS IoT Console
1. In the AWS IoT Core console, navigate to **Test** $\rightarrow$ **MQTT test client**.
2. In the **Subscribe to a topic** tab:
   * **Topic filter**: `ei_out`
   * Click **Subscribe**.
3. Live JSON telemetry containing your ESP32 MAC address and DHT11 readings will stream in real time!
