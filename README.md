# ESP32 and IoT Projects

A portfolio-style collection of ESP32, embedded systems, wireless communication, cloud telemetry, computer vision, and edge intelligence projects.

<p align="left">
  <img alt="ESP32" src="https://img.shields.io/badge/ESP32-222222?style=for-the-badge&logo=espressif&logoColor=white">
  <img alt="Arduino" src="https://img.shields.io/badge/Arduino%20IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white">
  <img alt="C++" src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white">
  <img alt="IoT" src="https://img.shields.io/badge/IoT-Cloud%20Telemetry-0A66C2?style=for-the-badge">
</p>

## Highlights

- ESP32 projects for Wi-Fi monitoring, packet detection, RSSI analysis, CSI capture, and security learning
- Cloud-connected telemetry examples using ThingSpeak, Blynk, AWS IoT Core, Azure IoT Hub, IFTTT, and OpenWeatherMap
- Sensor and automation builds with DHT sensors, ESP32-CAM, UART communication, camera streaming, and alert workflows
- MATLAB and edge analytics experiments for traffic monitoring, neural classification, and predictive maintenance

## Project Index

| Project | Area | What it demonstrates |
|---|---|---|
| [CSI Gesture Recognition](<./CSI Gesture Recognition/>) | Wireless sensing | Wi-Fi Channel State Information capture for contactless gesture experiments |
| [DeauthDetector](<./DeauthDetector/>) | Wi-Fi security | Passive detection of 802.11 deauthentication and disassociation frames |
| [ProbeTracker](<./ProbeTracker/>) | Wi-Fi monitoring | Probe request sniffing and MAC presence logging |
| [Wifi Signal Strength Meter (RSSI Monitor)](<./Wifi Signal Strength Meter (RSSI Monitor)/>) | Wi-Fi diagnostics | Real-time RSSI monitoring and signal strength analysis |
| [ESP32 DHT22 Weather Station](<./ESP32 DHT22 Weather Station/>) | Sensor telemetry | Temperature and humidity monitoring with ThingSpeak integration |
| [Traffic Density Monitoring System](<./Traffic Density Monitoring System/>) | Computer vision | 4-way traffic density analysis with MATLAB image processing and telemetry |
| [IoT Neural Network Classification (ThingSpeak)](<./IoT Neural Network Classification (ThingSpeak)/>) | Machine learning | Edge-to-cloud classification workflow using MATLAB and ThingSpeak |
| [ESP32 OpenWeatherMap to ThingSpeak Gateway](<./ESP32 OpenWeatherMap to ThingSpeak Gateway/>) | Cloud gateway | REST data ingestion from OpenWeatherMap and publishing to ThingSpeak |
| [IoT Smart Alert System (ThingSpeak + IFTTT)](<./IoT Smart Alert System (ThingSpeak + IFTTT)/>) | Alerts and automation | ThingSpeak analysis with IFTTT notification triggers |
| [ESP32 Azure IoT Hub Telemetry](<./ESP32 Azure IoT Hub Telemetry/>) | Azure IoT | MQTT telemetry streaming from ESP32 to Azure IoT Hub |
| [ESP32 Blynk 2.0 Cloud Controller](<./ESP32 Blynk 2.0 Cloud Controller/>) | Mobile IoT control | Bidirectional Blynk Cloud control with virtual pins and telemetry |
| [ESP32 IFTTT Email Alert and Excel Logger](<./ESP32 IFTTT Email Alert & Excel Logger/>) | Logging and alerts | Environmental data logging to sheets plus email alerts through IFTTT |
| [ESP32-CAM Blynk Photo Capture](<./ESP32-CAM Blynk Photo Capture/>) | Camera IoT | ESP32-CAM image capture and mobile dashboard integration |
| [ESP32 Serial UART Transmitter and Receiver](<./ESP32 Serial UART Transmitter & Receiver/>) | Serial communication | Packet-style UART communication between devices |
| [ESP32 IoT Predictive Maintenance System](<./ESP32 IoT Predictive Maintenance System/>) | Industrial IoT | Vibration sampling, cloud analytics, and maintenance alerts |
| [ESP32 AWS IoT Core Telemetry (SPIFFS mTLS)](<./ESP32 AWS IoT Core Telemetry (SPIFFS mTLS)/>) | AWS IoT security | MQTT telemetry over mTLS using certificate files stored in SPIFFS |
| [ESP32 AWS IoT Core MQTT Telemetry (PROGMEM mTLS)](<./ESP32 AWS IoT Core MQTT Telemetry (PROGMEM mTLS)/>) | AWS IoT MQTT | mTLS MQTT telemetry with credentials stored in program memory |
| [ESP32 AWS IoT Core HTTPS REST Telemetry (PROGMEM mTLS)](<./ESP32 AWS IoT Core HTTPS REST Telemetry (PROGMEM mTLS)/>) | AWS IoT HTTPS | Certificate-based HTTPS REST publishing to AWS IoT Core |
| [ESP32 AWS IoT Analytics Streamer (PROGMEM mTLS)](<./ESP32 AWS IoT Analytics Streamer (PROGMEM mTLS)/>) | IoT analytics | Structured telemetry pipeline for AWS IoT Analytics and dashboards |

## Getting Started

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Add ESP32 board support through Arduino IDE Board Manager.
3. Open the project folder and read its local README before wiring or uploading.
4. Install any listed libraries or cloud SDK dependencies.
5. Replace all placeholder Wi-Fi credentials, API keys, certificates, and tokens with your own local values.
6. Upload the sketch to an ESP32 board and use Serial Monitor for setup/debug output.

## Common Tools and Platforms

| Category | Examples |
|---|---|
| Boards | ESP32 DevKit, ESP32-CAM |
| Languages | C/C++, MATLAB, Python |
| Protocols | Wi-Fi, MQTT, HTTPS REST, UART, I2C |
| Cloud | AWS IoT Core, Azure IoT Hub, ThingSpeak, Blynk, IFTTT, OpenWeatherMap |
| Sensors and modules | DHT11/DHT22, camera module, wireless radio, UART devices, traffic image datasets |

## Security Note

Never commit real Wi-Fi passwords, private keys, API tokens, or production certificates. If any real credential was ever pushed to a public repository, rotate it immediately and replace it with a safe placeholder before using the project again.

## Repository Notes

- Each folder is a standalone project with its own sketch, setup notes, and dependencies where needed.
- Cloud examples are intended as learning templates and should be customized before deployment.
- Wireless security projects are for education and authorized testing only.

