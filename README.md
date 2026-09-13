# ESP32 & IoT Projects Repository

A collection of embedded systems, ESP32, and IoT projects spanning wireless communication, security, sensor telemetry, computer vision, and machine learning.

---

## 📂 Projects Included

1. **[CSI Gesture Recognition](./CSI%20Gesture%20Recognition/)**
   * Wi-Fi Channel State Information (CSI) extraction for contactless gesture recognition.
2. **[DeauthDetector](./DeauthDetector/)**
   * Wi-Fi 802.11 deauthentication frame detection and alert system.
3. **[ProbeTracker](./ProbeTracker/)**
   * Wi-Fi probe request packet sniffer and MAC presence logger.
4. **[Wifi Signal Strength Meter (RSSI Monitor)](./Wifi%20Signal%20Strength%20Meter%20(RSSI%20Monitor)/)**
   * Real-time Wi-Fi signal monitor and strength analyzer.
5. **[ESP32 DHT22 Weather Station](./ESP32%20DHT22%20Weather%20Station/)**
   * Real-time environmental monitoring station with DHT22 sensor and ThingSpeak Cloud integration.
6. **[Traffic Density Monitoring System](./Traffic%20Density%20Monitoring%20System/)**
   * Vision-based 4-way intersection traffic density monitoring with background subtraction and ThingSpeak telemetry.
7. **[IoT Neural Network Classification (ThingSpeak)](./IoT%20Neural%20Network%20Classification%20(ThingSpeak)/)**
   * Distributed edge-to-cloud machine learning pipeline classifying Iris features using MATLAB Deep Learning & ThingSpeak Analysis.
8. **[ESP32 OpenWeatherMap to ThingSpeak Gateway](./ESP32%20OpenWeatherMap%20to%20ThingSpeak%20Gateway/)**
   * Cloud-to-cloud weather telemetry bridge fetching OpenWeatherMap REST API data and publishing to ThingSpeak via Arduino_JSON.
9. **[IoT Smart Alert System (ThingSpeak + IFTTT)](./IoT%20Smart%20Alert%20System%20(ThingSpeak%20+%20IFTTT)/)**
   * Automated cloud notification bridge analyzing ThingSpeak environmental telemetry and triggering push notifications via IFTTT Webhooks.
10. **[ESP32 Azure IoT Hub Telemetry](./ESP32%20Azure%20IoT%20Hub%20Telemetry/)**
    * Direct enterprise IoT telemetry streaming from ESP32 + DHT11 to Microsoft Azure IoT Hub over MQTT.
11. **[ESP32 Blynk 2.0 Cloud Controller](./ESP32%20Blynk%202.0%20Cloud%20Controller/)**
    * Bidirectional smart IoT controller connecting ESP32 to Blynk 2.0 (Blynk.Cloud) with virtual pins, dynamic telemetry, and app dashboard control.
12. **[ESP32 IFTTT Email Alert & Excel Logger](./ESP32%20IFTTT%20Email%20Alert%20&%20Excel%20Logger/)**
    * Automated environmental logger and threshold alert system streaming DHT11 telemetry to Google Sheets / Excel Online and Gmail via IFTTT Webhooks.
13. **[ESP32-CAM Blynk Photo Capture](./ESP32-CAM%20Blynk%20Photo%20Capture/)**
    * Smart camera node utilizing AI-Thinker ESP32-CAM (OV2640), embedded HTTP streaming server, flash illumination, and snapshot display on Blynk mobile app.
14. **[ESP32 Serial UART Transmitter & Receiver](./ESP32%20Serial%20UART%20Transmitter%20&%20Receiver/)**
    * Asynchronous peer-to-peer serial communication implementing delimiter-based packet framing over wired, HC-12 RF, or Bluetooth links.
15. **[ESP32 IoT Predictive Maintenance System](./ESP32%20IoT%20Predictive%20Maintenance%20System/)**
    * Industrial machine health monitoring integrating ESP32 vibration window sampling with a cloud Radial Basis Function (RBF) neural network and IFTTT alerts.
16. **[ESP32 AWS IoT Core Telemetry (SPIFFS mTLS)](./ESP32%20AWS%20IoT%20Core%20Telemetry%20(SPIFFS%20mTLS)/)**
    * Secure AWS IoT Core telemetry over encrypted MQTT (Port 8883) loading X.509 device certificates and private keys from the onboard SPIFFS filesystem.
17. **[ESP32 AWS IoT Core MQTT Telemetry (PROGMEM mTLS)](./ESP32%20AWS%20IoT%20Core%20MQTT%20Telemetry%20(PROGMEM%20mTLS)/)**
    * Encrypted mutual TLS (mTLS) MQTT telemetry on port 8883 storing X.509 device certificates, RSA private keys, and Amazon Root CA directly in ESP32 Flash memory (`PROGMEM`) without SPIFFS.
18. **[ESP32 AWS IoT Core HTTPS REST Telemetry (PROGMEM mTLS)](./ESP32%20AWS%20IoT%20Core%20HTTPS%20REST%20Telemetry%20(PROGMEM%20mTLS)/)**
    * Certificate-based HTTPS REST publisher streaming JSON payloads to AWS IoT topic endpoints on port 8443 using raw HTTP POST requests without an MQTT broker client library.
19. **[ESP32 AWS IoT Analytics Streamer (PROGMEM mTLS)](./ESP32%20AWS%20IoT%20Analytics%20Streamer%20(PROGMEM%20mTLS)/)**
    * Structured telemetry pipeline streaming sequenced JSON records (`DeviceID`, `temperature`, `humidity`) to AWS IoT Analytics and Amazon QuickSight over mTLS (Port 8883).


