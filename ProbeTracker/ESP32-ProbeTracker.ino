#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include <map>

// Track MACs with timestamps for deduplication
std::map<String, unsigned long> seen_macs;
const unsigned long COOLDOWN_MS = 30000; // same MAC counts again after 30s
int people_count = 0;
int current_channel = 1;

void wifi_sniffer_cb(void* buf, wifi_promiscuous_pkt_type_t type) {
  if (type != WIFI_PKT_MGMT) return;

  wifi_promiscuous_pkt_t* pkt = (wifi_promiscuous_pkt_t*)buf;
  uint8_t* payload = pkt->payload;

  // 802.11 frame control: type bits [3:2], subtype bits [7:4]
  uint8_t frame_type    = (payload[0] & 0x0C) >> 2;
  uint8_t frame_subtype = (payload[0] & 0xF0) >> 4;

  // Management frame (0) + Probe Request subtype (4)
  if (frame_type != 0 || frame_subtype != 4) return;

  // Source MAC is bytes 10–15
  char mac[18];
  snprintf(mac, sizeof(mac), "%02X:%02X:%02X:%02X:%02X:%02X",
    payload[10], payload[11], payload[12],
    payload[13], payload[14], payload[15]);

  String mac_str = String(mac);
  unsigned long now = millis();

  // Deduplicate: only count if MAC not seen recently
  if (seen_macs.find(mac_str) == seen_macs.end() ||
      now - seen_macs[mac_str] > COOLDOWN_MS) {
    seen_macs[mac_str] = now;
    people_count++;
    int8_t rssi = pkt->rx_ctrl.rssi;
    Serial.printf("[Ch %2d] #%d | %s | RSSI: %d dBm\n",
                  current_channel, people_count, mac, rssi);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("=== Probe Request Counter ===");

  nvs_flash_init();
  esp_netif_init();
  esp_event_loop_create_default();

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  esp_wifi_init(&cfg);
  esp_wifi_set_storage(WIFI_STORAGE_RAM);
  esp_wifi_set_mode(WIFI_MODE_NULL);
  esp_wifi_start();
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_promiscuous_rx_cb(&wifi_sniffer_cb);

  esp_wifi_set_channel(current_channel, WIFI_SECOND_CHAN_NONE);
  Serial.println("Listening...\n");
}

void loop() {
  // Hop channels 1–13 every 500ms so you catch all probe requests
  delay(500);
  current_channel = (current_channel % 13) + 1;
  esp_wifi_set_channel(current_channel, WIFI_SECOND_CHAN_NONE);
}