#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

String server = "http://maker.ifttt.com";
String eventName = "temp_data";              // Logs data to Google Sheet / Excel
String eventNametemp30 = "temp_datatemp30";  // Sends Email Alert if temp > 29°C
String IFTTT_Key = "YOUR_IFTTT_KEY";
String IFTTT_Keytemp30 = "YOUR_IFTTT_KEY";

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

  int httpCode = http.GET();
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}

void sendDataToSheettemp30(void) {
  String url = server + "/trigger/" + eventNametemp30 + "/with/key/" + IFTTT_Keytemp30 + "?value1=" + String((int)value1) + "&value2=" + String((int)value2);  
  Serial.println(url);
  HTTPClient http;
  http.begin(url);

  int httpCode = http.GET();
  if (httpCode > 0) {
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

  if (value2 > 29) {
    Serial.println("ALERT: Temperature exceeded threshold! Sending Email Alert...");
    sendDataToSheettemp30(); // Trigger Email Alert
    sendDataToSheet();       // Log to Spreadsheet
    delay(30000);
  } else {
    sendDataToSheet();       // Normal logging
  }

  Serial.print("Values: Humidity=");
  Serial.print(value1);
  Serial.print("% Temperature=");
  Serial.print(value2);
  Serial.println("°C");

  delay(30000); // Send every 30 seconds
}
