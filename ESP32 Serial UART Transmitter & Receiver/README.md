# ESP32 Serial UART Transmitter & Receiver

A peer-to-peer asynchronous serial communication architecture between two microcontrollers (ESP32, Arduino, or STM32) communicating at 9600 baud. It implements **delimiter-based packet framing** (`\r`) for reliable string transmission over wired or wireless serial bridges.

---

## 📌 Architecture

```text
┌───────────────────────────┐                     ┌───────────────────────────┐
│     Transmitter Node      │                     │       Receiver Node       │
│  (day19_transmit.ino)     │                     │   (day19_receive.ino)     │
│                           │   Serial Stream     │                           │
│   • Formats "CAT\r"       ├────────────────────►│   • Buffers incoming bytes│
│   • Transmits @ 9600 baud │  (Wired or RF / BT) │   • Detects '\r' delimiter│
│   • Sends every 1000ms    │                     │   • Flushes to Console    │
└───────────────────────────┘                     └───────────────────────────┘
```

---

## 📂 Included Sketches

| Folder | Sketch | Role |
| :--- | :--- | :--- |
| **`day19_transmit/`** | `day19_transmit.ino` | Periodically broadcasts the delimited string packet `"CAT\r"` at `9600` baud. |
| **`day19_receive/`** | `day19_receive.ino` | Listens for incoming bytes, stores them in an array, detects the `\r` delimiter, prints the string, and resets the buffer. |

---

## 🛠️ Wiring Configurations

### 1. Direct Wired Bridge (Two Boards)
Connect two ESP32 or Arduino boards directly:
| Transmitter Board Pin | Receiver Board Pin |
| :--- | :--- |
| **TX (GPIO 1 / TX0)** | **RX (GPIO 3 / RX0)** |
| **GND** | **GND (Common Ground)** |

> ⚠️ **Note on Hardware Serial:**  
> When connecting directly to the default `Serial` pins (GPIO 1 & 3 on ESP32 / Pins 0 & 1 on Arduino Uno), disconnect the TX/RX wires while uploading code via USB to prevent flashing conflicts.

---

### 2. Transparent Wireless RF Bridge (HC-12 433MHz)
Transmit wirelessly over several hundred meters:
* **Transmitter Board TX** $\rightarrow$ **HC-12 Module 1 RX**
* **Receiver Board RX** $\leftarrow$ **HC-12 Module 2 TX**
* Both HC-12 modules powered by `3.3V`–`5V` and `GND`.

---

### 3. Transparent Bluetooth Bridge (HC-05 / HC-06)
* Set up HC-05 as Master (Transmitter) and HC-06 as Slave (Receiver).
* Transmits serial packets over Bluetooth SPP transparently.

---

## 💡 Buffer Management & Packet Framing
In packet-based serial communication, bytes arrive one at a time. The receiver uses a delimiter (`\r` - ASCII 13) to know when the message ends:
```cpp
if (c == '\r') {
  buff[indx] = '\0';      // Null-terminate C-string
  Serial.println(buff);   // Print complete packet
  indx = 0;               // Reset index for the next message
}
```
This ensures messages don't merge together and prevents memory buffer overflows.
