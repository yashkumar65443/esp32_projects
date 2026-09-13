# ESP32 AWS IoT Analytics Streamer (PROGMEM mTLS)

An enterprise-ready IoT edge telemetry streamer transmitting indexed sensor packets (`DeviceID`, `temperature`, `humidity`) over secure mTLS (Port 8883) to **AWS IoT Core**, structured specifically for automated ingestion by **AWS IoT Analytics**, **AWS IoT Rules Engine**, and **Amazon QuickSight**.

---

## 📌 Architecture & Overview

In advanced cloud analytics architectures, incoming raw MQTT packets must contain deterministic record identifiers or sequence counters. This sketch tags each measurement sample with an incrementing integer `DeviceID` / sequence counter before publishing to a dedicated analytics topic (`outTopicESP32Analyticsdemo`).

```
+------------------+                   mTLS (Port 8883)                    +-----------------------+
|      ESP32       | ----------------------------------------------------> |     AWS IoT Core      |
| (WiFiClientSecure|   Topic: "outTopicESP32Analyticsdemo"                 |    (Message Broker)   |
|  + PubSubClient) |   Payload: {"DeviceID":1,"temperature":..,"humidity":..} +-----------+-----------+
+------------------+                                                                   |
                                                                              IoT SQL Rules Engine
                                                                         SELECT * FROM 'outTopicESP32Analyticsdemo'
                                                                                       |
                                                                                       v
                                                                           +-----------------------+
                                                                           |   AWS IoT Analytics   |
                                                                           | +-------------------+ |
                                                                           | |  Channel          | |
                                                                           | +---------+---------+ |
                                                                           |           v           |
                                                                           | |  Pipeline (Filter)| |
                                                                           | +---------+---------+ |
                                                                           |           v           |
                                                                           | |  Data Store       | |
                                                                           | +---------+---------+ |
                                                                           |           v           |
                                                                           | |  SQL Dataset      | |
                                                                           | +-------------------+ |
                                                                           +-----------+-----------+
                                                                                       |
                                                                                       v
                                                                           +-----------------------+
                                                                           |   Amazon QuickSight   |
                                                                           |  (BI Cloud Dashboard) |
                                                                           +-----------------------+
```

### Why Sequence ID (`DeviceID`) Matters in Cloud Analytics
* **Deduplication:** Prevents duplicate metrics during network retries or QoS 1 republishes.
* **Packet Loss Tracking:** Missing integer IDs reveal packet delivery gaps or Wi-Fi dropouts.
* **SQL Time-Series Partitioning:** Provides a primary sorting key in AWS Athena, IoT Analytics Data Stores, and DynamoDB.

---

## 🔧 Hardware & Software Prerequisites

### Hardware
* **ESP32 Development Board** (ESP32 DevKit v1, NodeMCU-32S, etc.)
* Micro-USB / Type-C data cable.

### Software & Libraries
* **Arduino IDE** (v1.8.x or v2.x)
* **ESP32 Board Package** by Espressif Systems
* **PubSubClient** by Nick O'Leary (v2.6.0+ via Library Manager)

---

## ☁️ AWS IoT Core & Analytics Setup

1. **AWS IoT Core Policy:**
   Ensure the policy attached to your device certificate allows publishing to the analytics topic:
   ```json
   {
     "Version": "2012-10-17",
     "Statement": [
       {
         "Effect": "Allow",
         "Action": ["iot:Connect", "iot:Publish", "iot:Subscribe", "iot:Receive"],
         "Resource": ["*"]
       }
     ]
   }
   ```
2. **AWS IoT Core Rule for IoT Analytics (Optional / Production):**
   * In AWS IoT Core, navigate to **Message routing $\rightarrow$ Rules**.
   * Create a rule with SQL query:
     ```sql
     SELECT * FROM 'outTopicESP32Analyticsdemo'
     ```
   * Add Action: **Send a message to an IoT Analytics channel** (create a new channel, pipeline, and data store).
3. **AWS IoT Analytics Pipeline:**
   * Create an automated SQL dataset running queries such as:
     ```sql
     SELECT DeviceID, temperature, humidity, __timestamp__ FROM esp32_analytics_datastore ORDER BY DeviceID ASC
     ```
   * Visualize real-time machine telemetry on **Amazon QuickSight**.

---

## 🚀 Configuration & Execution

1. Open `Deviceid.ino` in Arduino IDE.
2. Update Wi-Fi and Endpoint variables:
   ```cpp
   const char* ssid = "YOUR_WIFI_SSID";
   const char* password = "YOUR_WIFI_PASSWORD";
   const char* awsEndpoint = "xxxxxxxxxxxxxx-ats.iot.<your-region>.amazonaws.com";
   ```
3. Paste your AWS certificate and private key strings into `certificate_pem_crt` and `private_pem_key`.
4. Upload the sketch to your ESP32.
5. Open **Serial Monitor** at `115200 baud`.

---

## 🔍 Verification & Testing

1. Open AWS IoT Core Console $\rightarrow$ **Test $\rightarrow$ MQTT test client**.
2. Subscribe to `outTopicESP32Analyticsdemo`.
3. Verify incoming structured packets with incrementing sequence IDs:
   ```json
   {"DeviceID": 1, "temperature": 84.15, "humidity": 89.60}
   {"DeviceID": 2, "temperature": 79.40, "humidity": 92.10}
   {"DeviceID": 3, "temperature": 88.05, "humidity": 80.25}
   ```