# ESP32 AWS IoT Core MQTT Telemetry (PROGMEM mTLS)

Secure, bidirectional IoT telemetry between an ESP32 microcontroller and **Amazon Web Services (AWS) IoT Core** over encrypted MQTT using X.509 client certificates and RSA private keys stored directly in Flash memory (`PROGMEM`).

---

## 📌 Architecture & Overview

AWS IoT Core enforces industry-standard Mutual TLS (mTLS v1.2 / v1.3) authentication on TCP port `8883`. Both the client (ESP32) and server (AWS IoT Core) authenticate each other:
1. **Server Verification:** The ESP32 verifies AWS using the **Amazon Root CA 1** certificate.
2. **Client Authentication:** AWS IoT Core verifies the ESP32 using the provisioned **Device Certificate** (`.pem.crt`) and matching **RSA Private Key** (`.pem.key`).

```
+------------------+                    mTLS (Port 8883)                     +----------------------+
|                  | ------------------------------------------------------> |                      |
|      ESP32       |   Publishes telemetry JSON to "outTopic"                |     AWS IoT Core     |
| (WiFiClientSecure| <------------------------------------------------------ |   (Message Broker)   |
|  + PubSubClient) |   Subscribes to incoming commands on "inTopic"          |                      |
|                  |                                                         +----------------------+
+------------------+
```

### PROGMEM vs. SPIFFS Approach

| Feature | PROGMEM Approach (This Project) | SPIFFS Approach (Project 16) |
| :--- | :--- | :--- |
| **Storage Location** | Embedded C-strings in ESP32 Flash memory | Files stored in onboard SPIFFS flash partition |
| **Flashing Process** | Single compilation & upload in Arduino IDE | Requires SPIFFS tool (*ESP32 Sketch Data Upload*) |
| **RAM Footprint** | Extremely low (`PROGMEM` constants kept in flash) | Reads into heap buffers during initialization |
| **Portability** | Self-contained in a single `.ino` file | Requires external `data/` directory and file management |

---

## 🔧 Hardware & Software Prerequisites

### Hardware
* **ESP32 Development Board** (NodeMCU-32S, ESP32 DevKit v1, etc.)
* Micro-USB or Type-C cable for programming and power.

### Software & Libraries
* **Arduino IDE** (v1.8.x or v2.x)
* **ESP32 Board Package** (`esp32` by Espressif Systems)
* **PubSubClient** by Nick O'Leary (install via Arduino Library Manager, version 2.6.0+ recommended).
  > **Note:** If sending large JSON packets, check `#define MQTT_MAX_PACKET_SIZE` in `PubSubClient.h` (default is 128 bytes, can be increased to 256 or 512 bytes).

---

## ☁️ AWS IoT Core Setup

1. **Log in to AWS Console:** Navigate to **AWS IoT Core** in your target region (e.g., `ap-south-1`).
2. **Create a Thing:**
   * Go to **Manage $\rightarrow$ Things** and click **Create things**.
   * Choose **Create single thing**, name it (e.g., `ESP32_Thing`), and click **Next**.
3. **Generate X.509 Certificates:**
   * Choose **Auto-generate a new certificate (recommended)**.
   * Download:
     * Device certificate (`*-certificate.pem.crt`)
     * Private key file (`*-private.pem.key`)
     * Amazon Root CA 1 (`AmazonRootCA1.pem`)
4. **Create & Attach IoT Policy:**
   * Go to **Security $\rightarrow$ Policies $\rightarrow$ Create Policy**.
   * Under Policy document JSON, allow connect, publish, subscribe, and receive:
     ```json
     {
       "Version": "2012-10-17",
       "Statement": [
         {
           "Effect": "Allow",
           "Action": [
             "iot:Connect",
             "iot:Publish",
             "iot:Subscribe",
             "iot:Receive"
           ],
           "Resource": ["*"]
         }
       ]
     }
     ```
   * Attach this policy to your downloaded device certificate.
5. **Get Device Data Endpoint:**
   * Go to **Settings** in the AWS IoT Core console and copy your custom endpoint (format: `xxxxxxxxxxxxxx-ats.iot.<region>.amazonaws.com`).

---

## 🚀 Configuration & Execution

1. Open `MQTT.ino` in Arduino IDE.
2. Update Wi-Fi and Endpoint credentials:
   ```cpp
   const char* ssid = "YOUR_WIFI_SSID";
   const char* password = "YOUR_WIFI_PASSWORD";
   const char* awsEndpoint = "xxxxxxxxxxxxxx-ats.iot.ap-south-1.amazonaws.com";
   ```
3. Copy your downloaded certificate and private key text into the raw string literals:
   ```cpp
   static const char certificate_pem_crt[] PROGMEM = R"KEY(
   -----BEGIN CERTIFICATE-----
   ... [PASTE CERTIFICATE CONTENT] ...
   -----END CERTIFICATE-----
   )KEY";

   static const char private_pem_key[] PROGMEM = R"KEY(
   -----BEGIN RSA PRIVATE KEY-----
   ... [PASTE RSA PRIVATE KEY CONTENT] ...
   -----END RSA PRIVATE KEY-----
   )KEY";
   ```
4. Select board **ESP32 Dev Module**, choose the active COM port, and click **Upload**.
5. Open **Serial Monitor** at `115200 baud`.

---

## 🔍 Verification & Testing

1. In AWS IoT Core Console, open the **MQTT test client** under the **Test** menu.
2. **Subscribe to a topic:**
   * Topic filter: `outTopic`
   * Click **Subscribe**.
3. You will observe periodic JSON payloads streamed every 10 seconds:
   ```json
   {
     "uptime": 42,
     "temp": 64.21,
     "humid": 82.15
   }
   ```
4. **Publish to ESP32:**
   * Topic: `inTopic`
   * Message: `{"cmd": "LED_ON"}`
   * Click **Publish**.
   * The ESP32 Serial Monitor will trigger `msgReceived()` and print the incoming payload in real time!