#include "WiFi.h"

// Replace these with your actual WiFi details
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Start the connection process
  WiFi.begin(ssid, password);

  // Wait until the ESP32 successfully connects
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi successfully connected!");
  Serial.println("Starting Signal Strength Monitor...");
  Serial.println("-----------------------------------");
}

void loop() {
  // Only measure if we are still connected
  if (WiFi.status() == WL_CONNECTED) {
    // Get the signal strength of the CURRENT connection
    int rssi = WiFi.RSSI();
    
    // Create the visual bar graph
    String bar = "";
    if (rssi >= -50)      bar = "██████ (Excellent)";
    else if (rssi >= -60) bar = "████░░ (Good)";
    else if (rssi >= -70) bar = "███░░░ (Fair)";
    else if (rssi >= -80) bar = "██░░░░ (Weak)";
    else                  bar = "█░░░░░ (Very Weak)";

    Serial.printf("Target: %-15s | RSSI: %-4d dBm | %s\n", ssid, rssi, bar.c_str());
  } else {
    // If the signal gets so weak it drops, try to reconnect
    Serial.println("Connection lost! Trying to reconnect...");
    WiFi.begin(ssid, password);
  }

  // Measure every 1 second
  delay(1000);
}
