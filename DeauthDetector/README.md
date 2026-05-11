# 📡 ESP32 Wi-Fi Deauth Frame Detector 🛡️


Welcome to the **ESP32 Deauth Frame Detector**! This project turns an ordinary ESP32 microcontroller into a powerful, passive Wi-Fi security monitor. It constantly scans the airwaves around you, hunting for malicious **Deauthentication** and **Disassociation** frames used by hackers and Wi-Fi kickers! 🥷📻

---

## ⚙️ How It Works (The Magic) 🪄

Wi-Fi networks use "Management Frames" to keep things organized. When you want to disconnect from a router, your device sends a **Deauthentication (Deauth)** frame. However, hackers can spoof your MAC address and send fake deauth frames to the router, forcing you offline! 

This ESP32 project defeats that stealthy attack by watching everything in the air:

1. **🕵️‍♂️ Promiscuous Mode:** The ESP32 is placed into a special "monitor mode" where it can see *all* raw wireless traffic flying through the air, not just its own.
2. **🦘 Channel Hopping:** Wi-Fi operates on 13 different channels. The ESP32 rapidly hops through channels 1 to 13 (200ms per channel) to ensure no attacker slips by unnoticed.
3. **🎯 Packet Sniffing:** Every single packet is caught and inspected. If the ESP32 spots a Management frame with **Subtype 12** (Deauth) or **Subtype 10** (Disassoc), the alarm is tripped!
4. **🚨 Alert System:** When an attack is spotted, the ESP32 flashes its built-in LED and dumps the exact MAC addresses of the Attacker, the Target, and the Router directly to your Serial Monitor.

---

## 🛠️ Uses & Applications 🚀

Why would you need this? Here are some awesome ways to use your detector:

*   **🔒 Network Security Auditing:** Test if your home or office network is vulnerable to deauthentication attacks and ensure your router's "Management Frame Protection" (802.11w) is working.
*   **🏨 Hotel / Conference Defense:** Worried about someone kicking you off public Wi-Fi? Keep this running next to your laptop to know immediately if someone is tampering with the network.
*   **🎓 Educational Tool:** Learn the inner workings of the 802.11 Wi-Fi protocol, packet sniffing, and the C++ Espressif IDF API without needing a bulky Linux laptop.
*   **🎮 Drone Protection:** Drone pilots use Wi-Fi to control their aircraft. A deauth attack can drop a drone from the sky! Use this to detect interference before taking off.

---

## 🚀 Getting Started

### 📋 Prerequisites
* An **ESP32** Development Board 📟
* A Micro-USB or USB-C cable 🔌
* The **Arduino IDE** installed on your computer 💻

### 🏃‍♂️ Running the Code
1. Open the `.ino` file in your Arduino IDE.
2. Make sure you have the ESP32 board manager installed.
3. Select your ESP32 board and the correct COM port from the `Tools` menu.
4. Hit **Upload**! 🚀
5. Open the **Serial Monitor** and set the baud rate to `115200`.
6. Press the **EN** or **RST** button on the ESP32 to restart it. 
7. *Watch the magic happen!* ✨

---

## ⚠️ Disclaimer
**For Educational Use Only.** This tool is designed to *detect* attacks and improve security. Do not use deauth tools to attack networks you do not own or do not have explicit permission to test. Stay ethical! 😇⚖️

---
*Built with ❤️ and C++*
