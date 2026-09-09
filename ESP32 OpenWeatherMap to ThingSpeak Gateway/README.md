# ESP32 OpenWeatherMap to ThingSpeak IoT Gateway

An ESP32-based cloud-to-cloud weather telemetry bridge. It periodically queries the **OpenWeatherMap REST API** for live weather data of any designated city, parses the JSON payload using **`Arduino_JSON`**, and forwards the metrics to the **ThingSpeak IoT Cloud**.

---

## ?? Features
* **Zero Physical Sensors Needed**: Pulls live atmospheric data directly from online meteorological stations via REST API.
* **JSON Deserialization**: Uses the lightweight `Arduino_JSON` library to extract nested weather parameters.
* **Kelvin to Celsius Conversion**: Automatically normalizes OpenWeatherMap temperature data.
* **Multi-Field Cloud Telemetry**: Pushes 4 live data streams in a single HTTP request to ThingSpeak.
* **Non-Blocking Timer**: Employs `millis()` intervals to respect API polling limits.

---

## ?? Telemetry Fields on ThingSpeak

| Channel Field | Metric | Unit | Source JSON Key |
| :--- | :--- | :--- | :--- |
| **Field 1** | Ambient Temperature | °C | `myObject["main"]["temp"] - 273` |
| **Field 2** | Atmospheric Pressure | hPa | `myObject["main"]["pressure"]` |
| **Field 3** | Relative Humidity | % | `myObject["main"]["humidity"]` |
| **Field 4** | Wind Speed | m/s | `myObject["wind"]["speed"]` |

---

## ??? Requirements

### Hardware
* Any **ESP32 Development Board** (NodeMCU-32S, ESP32 WROOM, etc.)
* Micro-USB cable
* 2.4 GHz Wi-Fi Internet connection

### Arduino IDE Libraries
Install the following libraries before compiling:
1. **Arduino_JSON** (by Arduino) — available via *Library Manager* or installable via `.zip` (*Sketch* $\rightarrow$ *Include Library* $\rightarrow$ *Add .ZIP Library...* using the `Arduino_JSON-master.zip` release).
2. **ThingSpeak** (by MathWorks) — available via *Library Manager*.
3. **WiFi** & **HTTPClient** — built into the official ESP32 Arduino core.

---

## ?? Setup & Configuration

1. Open `httpget/httpget.ino` in Arduino IDE.
2. Configure your credentials and target location:
   ```cpp
   // Wi-Fi Credentials
   const char* ssid     = "YOUR_WIFI_SSID";
   const char* password = "YOUR_WIFI_PASSWORD";

   // ThingSpeak Configuration
   unsigned long myChannelNumber = 0000000;
   const char * myWriteAPIKey    = "YOUR_THINGSPEAK_WRITE_KEY";

   // OpenWeatherMap Configuration
   String openWeatherMapApiKey = "YOUR_OPENWEATHERMAP_API_KEY";
   String city = "Chennai";     // Set your desired city
   String countryCode = "IN";   // ISO 3166-1 country code
   ```
3. Select your ESP32 board and COM port, then click **Upload**.
4. Open the Serial Monitor at **115200 baud** to view real-time API responses and upload statuses.
