# ESP32 AWS IoT Core HTTPS REST Telemetry (PROGMEM mTLS)

Secure, certificate-authenticated telemetry publisher streaming JSON sensor payloads to **AWS IoT Core** using native **HTTPS REST (HTTP POST)** on TCP port `8443`, without requiring the PubSubClient or any MQTT client library.

---

## 📌 Architecture & Overview

AWS IoT Core exposes a RESTful HTTP message interface allowing IoT devices to publish messages directly to MQTT topics over HTTPS.

```
+------------------+                   HTTPS POST (Port 8443)                   +----------------------+
|                  | ---------------------------------------------------------> |                      |
|      ESP32       |   POST /topics/outTopic?qos=1                              |     AWS IoT Core     |
| (WiFiClientSecure|   Host: <endpoint>:8443                                    |   (REST Message API) |
|   Raw HTTP/1.1)  |   Content-Type: application/json                           |                      |
|                  |   mTLS X.509 Authentication                                +----------------------+
+------------------+
```

### Why Use HTTPS REST Instead of MQTT?
1. **Stateless / Battery-Optimized:** The ESP32 doesn't need to maintain a continuous keep-alive socket ping. It wakes up from Deep Sleep, connects, pushes an HTTP POST in milliseconds, and returns to sleep.
2. **No Third-Party MQTT Library:** Uses only built-in ESP32 core networking (`WiFiClientSecure`), keeping binary footprint small.
3. **Firewall & Proxy Friendly:** Useful in enterprise or campus networks where MQTT port `8883` is strictly blocked.

### Port Comparison in AWS IoT Core

| Protocol | Port | Authentication | Use Case |
| :--- | :--- | :--- | :--- |
| **MQTT** | `8883` | X.509 Client Certificate (mTLS) | Real-time bidirectional streaming |
| **HTTPS REST** | `8443` | **X.509 Client Certificate (mTLS)** | Direct REST POST with hardware certs (This Project) |
| **HTTPS REST** | `443` | AWS SigV4 (IAM Keys) or ALPN | Web application integrations |

> **Crucial Note on Port 8443:** AWS IoT Core specifically mandates port `8443` when authenticating HTTPS requests using X.509 client certificates. Standard HTTPS port `443` will reject client-certificate mTLS unless ALPN (Application-Layer Protocol Negotiation) with protocol `x-amzn-http-ca` is negotiated.

---

## 🔧 Hardware & Software Prerequisites

### Hardware
* **ESP32 Development Board** (NodeMCU-32S, ESP32 DevKit v1, etc.)
* Micro-USB or Type-C cable.

### Software & Libraries
* **Arduino IDE** (v1.8.x or v2.x)
* **ESP32 Board Package** (`esp32` by Espressif Systems)
* **Zero external libraries needed!** Built entirely using the native `WiFiClientSecure` library included with the ESP32 core.

---

## ☁️ AWS IoT Core Setup

1. **Create Thing & Certificate:**
   * In the AWS IoT Core console, create your Thing and generate X.509 certificates.
   * Download `*-certificate.pem.crt`, `*-private.pem.key`, and `AmazonRootCA1.pem`.
2. **Attach IoT Policy:**
   * Ensure your policy allows publishing to the target topic:
     ```json
     {
       "Version": "2012-10-17",
       "Statement": [
         {
           "Effect": "Allow",
           "Action": "iot:Publish",
           "Resource": "arn:aws:iot:*:*:topic/outTopic"
         }
       ]
     }
     ```
3. **Obtain Endpoint:**
   * Found in AWS IoT Core console $\rightarrow$ **Settings** (e.g. `xxxxxxxxxxxxxx-ats.iot.ap-south-1.amazonaws.com`).

---

## 🚀 Configuration & Execution

1. Open `http.ino` in Arduino IDE.
2. Update Wi-Fi and Endpoint settings:
   ```cpp
   const char* ssid = "YOUR_WIFI_SSID";
   const char* password = "YOUR_WIFI_PASSWORD";
   const char* host = "xxxxxxxxxxxxxx-ats.iot.ap-south-1.amazonaws.com";
   const int Port = 8443;
   const char *uri = "/topics/outTopic?qos=1";
   ```
3. Paste your certificate and RSA private key in `certificate_pem_crt` and `private_pem_key` strings.
4. Select board **ESP32 Dev Module** and upload.
5. Open **Serial Monitor** at `115200 baud`.

---

## 🔍 Verification & Testing

1. In AWS IoT Core Console, navigate to **Test $\rightarrow$ MQTT test client**.
2. **Subscribe to Topic:**
   * Topic filter: `outTopic`
   * Click **Subscribe**.
3. As the ESP32 issues HTTP POST requests, AWS IoT Core translates each HTTPS request into an MQTT message and displays it in the console:
   ```json
   {
     "uptime": 20,
     "temp": 61.50,
     "humid": 88.30
   }
   ```