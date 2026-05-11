#include <WiFi.h>
#include <esp_wifi.h>

// Built-in LED pin for ESP32 Dev Boards (change if using a different board)
const int ALERT_LED = 2; 

unsigned long lastAlertTime = 0;
const unsigned long ALERT_DURATION_MS = 1000; // LED stays on for 1 second after detection

// Helper function to format MAC addresses
String macToString(const uint8_t* mac) {
  char buf[18];
  snprintf(buf, sizeof(buf), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(buf);
}

// Promiscuous mode callback function
void sniffer(void *buf, wifi_promiscuous_pkt_type_t type) {
  // We only care about management frames for this purpose
  if (type != WIFI_PKT_MGMT) return;

  wifi_promiscuous_pkt_t *pkt = (wifi_promiscuous_pkt_t *)buf;
  uint8_t *payload = pkt->payload;
  
  // payload[0] contains the Frame Control byte 0 (Protocol Version, Type, Subtype)
  // Type 0 (Management). 
  // Subtype 12 (0xC) -> Byte 0 is 0xC0 (Deauthentication)
  // Subtype 10 (0xA) -> Byte 0 is 0xA0 (Disassociation)
  if (payload[0] == 0xC0 || payload[0] == 0xA0) {
    const uint8_t* destMac = &payload[4];
    const uint8_t* srcMac = &payload[10];
    const uint8_t* bssid = &payload[16];

    // Check if the destination is a broadcast address (common in deauth attacks)
    bool isBroadcast = true;
    for (int i=0; i<6; i++) {
        if (destMac[i] != 0xFF) isBroadcast = false;
    }

    Serial.println("===============================");
    Serial.println("⚠️ DEAUTH/DISASSOC DETECTED ⚠️");
    Serial.print("Type: ");
    Serial.println((payload[0] == 0xC0) ? "Deauthentication" : "Disassociation");
    
    Serial.print("Target (Dest): ");
    Serial.print(macToString(destMac));
    if (isBroadcast) Serial.println(" (BROADCAST)");
    else Serial.println();
    
    Serial.print("Attacker/AP (Src): ");
    Serial.println(macToString(srcMac));
    Serial.print("BSSID: ");
    Serial.println(macToString(bssid));
    Serial.println("===============================\n");
    
    // Trigger the alert (turn on LED)
    digitalWrite(ALERT_LED, HIGH);
    lastAlertTime = millis();
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000); // Give Serial time to initialize
  
  pinMode(ALERT_LED, OUTPUT);
  digitalWrite(ALERT_LED, LOW);
  
  Serial.println("\nESP32 Deauth Frame Detector Starting...");

  // Put Wi-Fi into Station mode and disconnect from any network
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Enable promiscuous mode
  esp_err_t err = esp_wifi_set_promiscuous(true);
  if (err != ESP_OK) {
    Serial.printf("Failed to set promiscuous mode! ESP_ERR: %d\n", err);
    return;
  }
  
  // Set the sniffer callback function
  err = esp_wifi_set_promiscuous_rx_cb(&sniffer);
  if (err != ESP_OK) {
    Serial.printf("Failed to set sniffer callback! ESP_ERR: %d\n", err);
    return;
  }

  Serial.println("Monitoring for Deauth/Disassoc frames...");
  Serial.println("Hopping through channels 1-13...");
}

void loop() {
  // Channel hopping logic
  // Wi-Fi 2.4GHz channels are 1-13 in most regions
  for (int channel = 1; channel <= 13; channel++) {
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
    
    // Listen on the current channel for a short period
    // Since we're hopping, we wait to catch frames flying by
    unsigned long startWait = millis();
    while (millis() - startWait < 200) { // 200ms per channel
        // Check if we need to turn off the alert LED
        if (digitalRead(ALERT_LED) == HIGH && (millis() - lastAlertTime > ALERT_DURATION_MS)) {
            digitalWrite(ALERT_LED, LOW);
        }
        delay(1); 
    }
  }
}
