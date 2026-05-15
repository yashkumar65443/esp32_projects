#include <WiFi.h>
#include <WiFiUdp.h>
#include <esp_wifi.h>

// --- Configuration ---
const char* ssid = "WIFI NAME";       // Change this!
const char* password = "PASSWORD"; // Change this!

WiFiUDP udp;
IPAddress gateway;

// This is the core function. It runs automatically in the background 
// EVERY time the ESP32 receives a Wi-Fi packet.
void csi_callback(void *ctx, wifi_csi_info_t *info) {
  // Safety check: Ignore empty packets
  if (!info || !info->buf || info->mac == nullptr || info->len == 0) {
    return;
  }

  // Cast the raw buffer to an array of integers
  int8_t *csi_data = (int8_t *)info->buf;
  int csi_len = info->len;

  // We start the line with "CSI," so our future Python script knows this is a data row
  Serial.print("CSI,");

  // Print the MAC address of the sender (Your phone's hotspot)
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X", info->mac[i]);
    if (i < 5) Serial.print(":");
  }
  Serial.print(",");

  // Print the RSSI (Overall Signal Strength in dBm)
  Serial.print(info->rx_ctrl.rssi);
  Serial.print(",");

  // Print the raw CSI data (The subcarrier amplitudes and phases)
  // These are the numbers that will spike when you wave your hand!
  for (int i = 0; i < csi_len; i++) {
    Serial.print(csi_data[i]);
    if (i < csi_len - 1) {
      Serial.print(",");
    }
  }
  Serial.println(); // End of line
}

void setup() {
  // Use a very high baud rate. CSI data generates thousands of numbers per second.
  Serial.begin(921600);
  delay(1000);

  Serial.println("\n--- ESP32 CSI Capture Initializing ---");

  // 1. Connect to the Hotspot
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to Hotspot: ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected Successfully!");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());
  
  gateway = WiFi.gatewayIP(); // This is your phone's IP address
  Serial.print("Gateway (Phone) IP: ");
  Serial.println(gateway);

  // 2. Configure the hidden Espressif CSI parameters
  wifi_csi_config_t csi_config = {
      .lltf_en           = true,
      .htltf_en          = true,
      .stbc_htltf2_en    = true,
      .ltf_merge_en      = true,
      .channel_filter_en = true,
      .manu_scale        = false,
      .shift             = false,
  };
  
  ESP_ERROR_CHECK(esp_wifi_set_csi_config(&csi_config));
  
  // 3. Register our callback function
  ESP_ERROR_CHECK(esp_wifi_set_csi_rx_cb(&csi_callback, NULL));
  
  // 4. Turn on the CSI engine
  ESP_ERROR_CHECK(esp_wifi_set_csi(true));
  
  Serial.println("\nCSI Engine Enabled. You should start seeing data below...\n");
}

void loop() {
  // To get high-resolution gesture data, we need about 50 packets per second.
  // By sending a tiny, dummy UDP packet to a random closed port on your phone, 
  // your phone's operating system will instantly reply with an ICMP error packet.
  // That returning error packet is what triggers our CSI callback!
  
  if (WiFi.status() == WL_CONNECTED) {
    udp.beginPacket(gateway, 33333); // Port 33333 is arbitrary and usually closed
    udp.write((const uint8_t*)"hi", 2);
    udp.endPacket();
  }
  
  // Wait 20 milliseconds before asking again (This gives us roughly 50 Hz sampling rate)
  delay(20); 
}
