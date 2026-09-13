#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

String server = "http://maker.ifttt.com";
String eventName = "temp_data";
String IFTTT_Key = "YOUR_IFTTT_KEY";

int value1; // Humidity
int value2; // Temperature

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected !!!");
}

void sendDataToSheet(void) {
  String url = server + "/trigger/" + eventName + "/with/key/" + IFTTT_Key + "?value1=" + String((int)value1) + "&value2=" + String((int)value2);  
  Serial.println(url);
  HTTPClient http;
  http.begin(url);

  Serial.print("[HTTP] GET...\n");
  int httpCode = http.GET();
  if (httpCode > 0) {
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}

void loop() {
  value1 = dht.readHumidity();
  value2 = dht.readTemperature();
  sendDataToSheet();
  Serial.print("Values: Humidity=");
  Serial.print(value1);
  Serial.print("% Temperature=");
  Serial.print(value2);
  Serial.println("°C");

  delay(10000); // Send every 10 seconds
}
