#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "YOUR_WIFI_SSID";   // your network SSID (name) 
const char* password = "YOUR_WIFI_PASSWORD";   // your network password
WiFiClient  client;

unsigned long myChannelNumber = 000000; // your ThingSpeak Channel Number
const char * myWriteAPIKey = "YOUR_WRITE_API_KEY"; // your ThingSpeak Write API Key

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

// Variable to hold temperature readings
float temperatureC;
float humidity;


void setup() {
  Serial.begin(115200);  //Initialize serial
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }

    // Get a new temperature reading
    temperatureC = 30;
     humidity=40;

   ThingSpeak.setField(1, temperatureC);
    //ThingSpeak.setField(1, temperatureF);
    ThingSpeak.setField(2, humidity);
    
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    
    
    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
}
