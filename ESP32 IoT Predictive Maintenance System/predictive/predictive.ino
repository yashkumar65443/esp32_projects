#include <WiFi.h>
#include "ThingSpeak.h"

WiFiClient client;

// --- CONFIGURATION ---
unsigned long myChannelNumber = 0000000;                      // Replace with your ThingSpeak Channel ID
const char * myWriteAPIKey    = "YOUR_THINGSPEAK_WRITE_KEY";  // Replace with your Write API Key
const char* ssid             = "YOUR_WIFI_SSID";             // Replace with your Wi-Fi SSID
const char* password         = "YOUR_WIFI_PASSWORD";         // Replace with your Wi-Fi Password

int vibrationsensor = 4;
int vibrationvalue = 0;
int sumvibrationvalue;

unsigned long lastTime = 0;
unsigned long timerDelay = 20000; // 20 seconds sampling interval

void setup() {
  Serial.begin(115200);
  pinMode(vibrationsensor, INPUT);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client); // Initialize ThingSpeak
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      sumvibrationvalue = 0;

      // Sample vibration pulses over a 256-cycle window
      for (int i = 0; i <= 255; i++) {
        vibrationvalue = digitalRead(vibrationsensor);
        sumvibrationvalue += vibrationvalue;
      }

      Serial.print("Vibration Intensity Score (0-255): ");
      Serial.println(sumvibrationvalue);

      // Upload vibration metric to ThingSpeak Field 1
      ThingSpeak.setField(1, sumvibrationvalue);
      int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

      if (x == 200) {
        Serial.println("ThingSpeak channel update successful.");
      } else {
        Serial.println("Problem updating channel. HTTP error code: " + String(x));
      }
    } else {
      Serial.println("WiFi Disconnected!");
    }
    lastTime = millis();
  }
}
