# ESP32 IoT Weather Station (DHT22 + ThingSpeak)

A real-time environmental telemetry station built with an **ESP32** and a **DHT22** (AM2302) sensor that streams live temperature and humidity metrics to the **ThingSpeak IoT Cloud**.

---

## ?? Features
* Measures Ambient Temperature (°C / °F) and Relative Humidity (%RH).
* Calculates Heat Index (perceived temperature).
* Connects via Wi-Fi with automatic auto-reconnect logic.
* Pushes multi-field sensor telemetry to ThingSpeak every 30 seconds using non-blocking timers (`millis()`).

---

## ??? Hardware Requirements & Pinout

| Component | Pin / Connection | ESP32 GPIO |
| :--- | :--- | :--- |
| **DHT22 Pin 1 (VCC)** | Power | 3.3V |
| **DHT22 Pin 2 (DATA)** | Data Line | **GPIO 4** (with 10kO pull-up to 3.3V) |
| **DHT22 Pin 3 (NC)** | Not Connected | N/A |
| **DHT22 Pin 4 (GND)** | Ground | GND |

---

## ?? Arduino IDE Libraries Required
Install the following libraries via the Arduino Library Manager:
1. **DHT sensor library** (by Adafruit)
2. **Adafruit Unified Sensor** (by Adafruit)
3. **ThingSpeak** (by MathWorks)

---

## ?? Sketches in this Folder
* **`dhtada/dhtada.ino`**: Standalone sensor unit test to verify DHT22 wiring and readings.
* **`thinhspeaktestsingle/thinhspeaktestsingle.ino`**: Unit test for ESP32 Wi-Fi connection and single-field ThingSpeak transmission.
* **`thinhspeaktestmulyiple/thinhspeaktestmulyiple.ino`**: Unit test for simultaneous multi-field updates.
* **`final/final.ino`**: Production firmware integrating DHT22 sensor readings with ThingSpeak multi-field uploads.

---

## ?? Setup & Configuration
Before flashing `final/final.ino`, update your network and ThingSpeak credentials:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

unsigned long myChannelNumber = YOUR_CHANNEL_NUMBER;
const char * myWriteAPIKey = "YOUR_WRITE_API_KEY";
```
