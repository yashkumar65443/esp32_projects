# ESP32-CAM Blynk Smart Photo Capture & Video Stream

An IoT-connected smart surveillance and photography node built with an **AI-Thinker ESP32-CAM** (OV2640 camera sensor) and the **Blynk IoT Platform**. It hosts an embedded streaming web server, illuminates low-light scenes with the onboard high-power flash LED, and pushes live snapshots directly to the Blynk Mobile App.

---

## 📌 Architecture

```text
┌─────────────────────────────────┐
│  Physical Trigger (GPIO 14)     │
└──────────────┬──────────────────┘
               │  digitalRead(PHOTO) == HIGH
               ▼
┌─────────────────────────────────┐
│        AI-Thinker ESP32-CAM     │
│   • Lights Onboard Flash (GPIO 4│
│   • Captures Frame via OV2640   │
│   • Generates Snapshot URL      │
└──────────────┬──────────────────┘
               │  Blynk.setProperty(V1, "urls", ...)
               ▼
┌─────────────────────────────────┐
│     Blynk IoT Cloud             │
└──────────────┬──────────────────┘
               │  Syncs Virtual Pin V1
               ▼
┌─────────────────────────────────┐
│  📱 Blynk App (Image Widget)    │
│  Displays captured photo live   │
└─────────────────────────────────┘
```

---

## 📂 Project Structure

```text
├── ESP32CAM_Blynk_TakePhoto/
│   ├── ESP32CAM_Blynk_TakePhoto.ino  # Main application firmware
│   ├── app_httpd.cpp                 # Embedded MJPEG & Still HTTP server
│   ├── camera_pins.h                 # AI-Thinker pinout mapping
│   └── camera_index.h                # Web UI frontend assets (gzip)
└── README.md                         # Setup and flashing instructions
```

---

## 🛠️ Hardware Requirements

* **AI-Thinker ESP32-CAM Board** (with OV2640 camera sensor module)
* **FTDI USB-to-TTL Serial Programmer** (set to 5V power jumper)
* Jumper wires
* External pushbutton / PIR sensor (optional, connected to **GPIO 14**)

---

## ⚡ Flashing the ESP32-CAM via FTDI

Because the ESP32-CAM board does not include an onboard USB chip, you must use an external FTDI programmer to flash the code:

### Wiring Table:
| FTDI Programmer | ESP32-CAM Pin |
| :--- | :--- |
| **VCC (5V)** | **5V** |
| **GND** | **GND** |
| **TX** | **U0R (GPIO 3)** |
| **RX** | **U0T (GPIO 1)** |
| **GND** | **GPIO 0 (Flashing Jumper)** |

> ⚠️ **CRITICAL FLASHING STEP:**  
> Connect **GPIO 0 to GND** before powering up the board. This forces the ESP32 into bootloader/flashing mode. After the upload completes successfully, **disconnect GPIO 0 from GND** and press the **RST** button to start normal execution.

---

## 💻 Arduino IDE Configuration

1. Under **Tools** $\rightarrow$ **Board**, select: **AI Thinker ESP32-CAM**.
2. Set the following board options:
   * **CPU Frequency**: 240MHz (WiFi/BT)
   * **Flash Frequency**: 80MHz
   * **Flash Mode**: QIO
   * **Partition Scheme**: Huge APP (3MB No OTA/1MB SPIFFS)
   * **Core Debug Level**: None
   * **PSRAM**: **Enabled**
3. Install the **Blynk library** via **Tools** $\rightarrow$ **Manage Libraries...**.

---

## 🚀 Blynk App Configuration

1. In your Blynk mobile app or web dashboard, add an **Image Gallery** or **Image Widget**.
2. Assign the Datastream / Virtual Pin to **`V1`**.
3. In `ESP32CAM_Blynk_TakePhoto.ino`, replace the placeholders:
   ```cpp
   const char* ssid = "YOUR_WIFI_SSID";
   const char* password = "YOUR_WIFI_PASSWORD";

   char auth[] = "YOUR_BLYNK_AUTH_TOKEN";
   ```
4. Flash the board, disconnect GPIO 0 from GND, and press Reset.
5. Open Serial Monitor at **115200 baud** to see the local IP assigned to the camera web server.
6. Trigger **GPIO 14** (or connect GPIO 14 to 3.3V) $\rightarrow$ the flash LED fires, captures a snapshot, and displays the image live in your Blynk mobile app!
