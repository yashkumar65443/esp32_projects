# ESP32 WiFi Signal Strength Meter (RSSI Monitor)

## Overview
This project turns a standard ESP32 development board into a live, continuous WiFi signal strength monitor. By actively connecting to a target wireless network, the ESP32 measures the **Received Signal Strength Indicator (RSSI)** in real-time. The live data is then streamed to the serial monitor, accompanied by an easy-to-read ASCII bar graph, allowing you to visually track network performance and signal degradation as environmental factors change.

## How It Works
Instead of using complex time-of-flight hardware like 802.11mc FTM (which is unsupported on the base ESP32), this project uses radio frequency power measurement. The ESP32 constantly polls the router for the active connection strength. The closer the RSSI value is to zero (e.g., `-30` dBm), the stronger the signal. As the signal degrades (e.g., `-80` dBm), the visual bar graph shrinks, warning of potential connection drops.

## Practical Uses
This tool is incredibly useful for network diagnostics and smart home optimization:

* **Mapping WiFi Dead Zones:** Walk around your house with the ESP32 and a power bank to map out exactly where your router's signal drops off and identify where you might need a WiFi extender.
* **Optimizing Router Placement:** Move your router around and use the live serial readout to see if adjusting the antennas or moving it away from a wall improves coverage.
* **Proximity Detection (Basic):** Use the fluctuating RSSI values as a rudimentary proximity sensor. You can trigger other smart home events (like turning on a light) when your phone or ESP32 crosses a specific signal strength threshold.
* **Interference Testing:** Test how much signal is lost when doors are closed, or when placing the ESP32 behind appliances, metal objects, or thick walls. 
* **Antenna Testing:** If you are building custom IoT enclosures, use this code to test if your 3D printed case or metal housing is suffocating the ESP32's onboard WiFi antenna.

## Getting Started
1. Open `WiFi_Signal_Meter.ino` in your Arduino IDE.
2. Change the `ssid` and `password` variables at the top of the code to match your WiFi network.
3. Flash the code to your ESP32.
4. Open the Serial Monitor and set the baud rate to `115200`.
