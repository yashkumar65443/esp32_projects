# 📡 ESP32-ProbeCounter

> **Passive WiFi probe request sniffer & people counter — no connection required.**

The ESP32 silently listens to raw 802.11 management frames floating through the air and counts nearby devices — and by extension, people — without ever joining a network or sending a single packet.

---

## 🧠 How It Works

Every WiFi-enabled device — phone, laptop, tablet — constantly shouts into the air:

> *"Hey, is my saved network nearby?"*

These invisible shouts are called **probe requests**, and they happen even when your device isn't connected to anything. The ESP32 is placed into **promiscuous mode**, letting it hear every frame flying through the air without anyone knowing.

```
📱 Your Phone          🌊 The Air           📟 ESP32
      |                     |                   |
      |── Probe Request ──▶ |                   |
      |   [MAC address]     |──── sniffed ────▶ |
      |                     |    (passive 👻)   | → count++
```

By filtering for probe request frames and deduplicating by MAC address, we get a solid estimate of unique devices nearby — completely passively.

---

## ✨ Features

| | Feature |
|---|---|
| 👻 | **Fully passive** — zero packets sent, zero connections made |
| 📶 | **Channel hopping** across all 13 2.4GHz channels |
| 🔁 | **MAC deduplication** with a configurable cooldown window |
| 📏 | **RSSI per detection** — know how close the device is |
| 🖥️ | **Serial Monitor output** — ready to extend with OLED or web dashboard |

---

## 🛒 Hardware Required

| Component | Notes |
|---|---|
| 🟦 ESP32 Dev Board | Any variant — WROOM, WROVER, etc. |
| 🔌 USB Cable | For flashing and Serial Monitor |
| 🖵 OLED Display *(optional)* | SSD1306 I2C for standalone display |

> ✅ No external wiring needed for the base version — just plug in and flash.

---

## 💻 Software Requirements

- 🛠️ [Arduino IDE 2.x](https://www.arduino.cc/en/software)
- 📦 ESP32 Arduino Core — add this URL in Board Manager:

```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

> No extra libraries needed — uses ESP-IDF WiFi APIs built into the ESP32 core.

---

## 🚀 Installation

1. 📥 Clone or download this repository
2. 📂 Open `ESP32-ProbeCounter.ino` in Arduino IDE
3. 🔧 Select board: **Tools → Board → ESP32 Dev Module**
4. 🔌 Select the correct COM port
5. ⬆️ Upload the sketch
6. 📺 Open **Serial Monitor** at **115200 baud**

---

## 📺 Serial Monitor Output

```
=== ESP32-ProbeCounter ===
Listening...

[Ch  1] #1  | A4:C3:F0:12:34:56 | RSSI: -42 dBm
[Ch  6] #2  | 3E:7A:11:AB:CD:EF | RSSI: -71 dBm
[Ch 11] #3  | 9E:BE:63:99:2F:D5 | RSSI: -86 dBm
[Ch  4] #4  | CC:47:40:C6:F0:59 | RSSI: -86 dBm
```

Each line tells you: which channel it was caught on, the running count, the device's MAC address, and its signal strength.

---

## ⚙️ Configuration

| Constant | Default | Description |
|---|---|---|
| `COOLDOWN_MS` | `30000` | Time (ms) before the same MAC is counted again |

- ⬇️ **Lower** `COOLDOWN_MS` → more sensitive, catches repeat passers-by
- ⬆️ **Higher** `COOLDOWN_MS` → less noise in stationary environments like a room

---

## ⚠️ Limitations

| ⚠️ | Limitation | Detail |
|---|---|---|
| 🎭 | **MAC Randomization** | iOS 14+, Android 10+, Windows 10+ randomize probe request MACs. Individual tracking is gone — but unique device counting per time window still works fine. |
| 📻 | **2.4GHz Only** | Standard ESP32 doesn't sniff 5GHz. |
| 🤫 | **Passive Only** | This project sends zero frames. It only listens. |
| 📏 | **Range** | Typical detection range is 10–30 metres depending on environment and antenna. |

---

## 🔧 Possible Extensions

| 🔧 | Extension | What it adds |
|---|---|---|
| 🖵 | **OLED Display** | Show live count without needing a PC |
| 📏 | **RSSI Filtering** | Limit detection range by ignoring weak signals |
| 🌐 | **Web Dashboard** | Serve a live count page over WiFi via `AsyncWebServer` |
| 💾 | **SD Card Logging** | Timestamp every detection for offline analysis |
| 🤖 | **Telegram Alerts** | Push hourly summaries to a Telegram bot |

---

## 🔒 Privacy & Legal Notice

> ⚖️ Know before you deploy.

- 🤫 **Passive only** — no packets transmitted, no devices connected to
- 🇪🇺 **EU / GDPR** — even randomized MACs may count as personal data; don't deploy in public spaces without legal clarity
- 🇺🇸 **US / CFAA** — passive sniffing is a legal grey area; home use is fine, public deployment is not
- 🎓 This project is intended for **personal learning and RF education** — understanding 802.11 management frames, WiFi security, and promiscuous mode on embedded hardware

---

## 📄 License

MIT License — see `LICENSE` for details.

---

<div align="center">

**Built with ❤️ on an ESP32 | 📡 802.11 | 🔍 Promiscuous Mode | 👻 Passive Sniffing**

</div>
