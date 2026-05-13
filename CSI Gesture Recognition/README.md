# ESP32 CSI Gesture Recognition & Wi-Fi Disturbance Monitor

This project turns an ESP32 microcontroller into a highly sensitive, camera-free motion detector using Wi-Fi Channel State Information (CSI). By analyzing microscopic distortions in Wi-Fi radio waves, this system can detect when a human or object moves between the ESP32 and a Wi-Fi hotspot.

## How It Works

Modern Wi-Fi devices constantly adjust to changes in the physical environment. When a Wi-Fi packet is received, the hardware calculates "Channel State Information" (CSI) to understand how the radio signal was distorted by bouncing off walls or passing through objects.

1. **The Ping-Pong Mechanism:** The ESP32 connects to a mobile hotspot and sends a dummy UDP packet to a closed port on the phone 50 times per second.
2. **The Reply:** The phone's OS instantly replies with an ICMP "Port Unreachable" error packet.
3. **Data Extraction:** The ESP32's promiscuous CSI engine intercepts that incoming packet and extracts the raw amplitude and phase data for all Wi-Fi subcarriers.
4. **Visualization:** A Python script reads this raw data stream over USB, calculates the physical amplitude of a specific subcarrier, and plots it in real-time using Matplotlib.

When the space between the phone and the ESP32 is clear, the plotted line remains flat. When a physical object passes between them, the radio waves are disrupted, causing massive visible spikes in the live graph!

## Requirements

### Hardware
* ESP32 Development Board
* A smartphone to act as a Mobile Wi-Fi Hotspot
* Micro-USB or USB-C cable (with data transfer capabilities)

### Software
* [Arduino IDE](https://www.arduino.cc/en/software) (with ESP32 board definitions installed)
* Python 3.x
* Python Libraries: `pyserial`, `matplotlib`, `numpy`

## Setup & Usage

### 1. Configure the ESP32
1. Open `CSI_Gesture_Recogniton.ino` in the Arduino IDE.
2. Edit the following lines to match your smartphone's Wi-Fi Hotspot credentials:
   ```cpp
   const char* ssid = "YOUR_HOTSPOT_NAME";
   const char* password = "YOUR_HOTSPOT_PASSWORD";
   ```
3. Compile and flash the code to your ESP32.
4. Ensure your phone's hotspot is turned on. You can open the Arduino Serial Monitor (set to **921600 baud**) to verify it connects and begins printing `CSI,...` data lines.
5. **IMPORTANT:** Close the Arduino Serial Monitor before running the Python script. Only one program can read from the COM port at a time!

### 2. Run the Python Visualizer
1. Install the required Python dependencies:
   ```bash
   pip install pyserial matplotlib numpy
   ```
2. Open `plot_csi.py`.
3. Check the `PORT` variable at the top of the file and ensure it matches the COM port your ESP32 is connected to (e.g., `COM8`, `/dev/ttyUSB0`).
   ```python
   PORT = 'COM8' # Change this to match your ESP32
   ```
4. Run the script!
   ```bash
   python plot_csi.py
   ```
5. A dark-themed Matplotlib window will appear. Wave your hand between your phone and the ESP32 and watch the graph react!

## Customization
In `plot_csi.py`, you can change which specific Wi-Fi subcarrier you want to monitor by modifying:
```python
SUBCARRIER_TO_PLOT = 15
```
*(Standard 20MHz Wi-Fi channels have 52 usable subcarriers. Different subcarriers may react differently to movements depending on multipath fading!)*
