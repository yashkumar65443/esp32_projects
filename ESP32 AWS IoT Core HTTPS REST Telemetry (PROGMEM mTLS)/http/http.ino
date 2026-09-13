#include <WiFiClientSecure.h>

const char* ssid = "YOUR_WIFI_SSID";         // Provide your SSID
const char* password = "YOUR_WIFI_PASSWORD"; // Provide Password

const char* host = "YOUR_AWS_ENDPOINT-ats.iot.YOUR_REGION.amazonaws.com"; // AWS IoT Core --> Settings (Device data endpoint)
const int Port = 8443;  // AWS IoT Core uses 8443 for HTTPS with X.509 Client Certificate authentication

// AWS IoT Topic: Publish to topic "outTopic"
const char *uri = "/topics/outTopic?qos=1";  // See https://docs.aws.amazon.com/iot/latest/developerguide/http.html

// Device Certificate (xxxxxxxxxx-certificate.pem.crt)
static const char certificate_pem_crt[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
<PASTE_YOUR_AWS_DEVICE_CERTIFICATE_HERE>
-----END CERTIFICATE-----
)KEY";

// Device Private Key (xxxxxxxxxx-private.pem.key)
static const char private_pem_key[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
<PASTE_YOUR_AWS_PRIVATE_KEY_HERE>
-----END RSA PRIVATE KEY-----
)KEY";

/* Root CA: Amazon Root CA 1
   https://www.amazontrust.com/repository/AmazonRootCA1.pem
*/
static const char rootCA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

WiFiClientSecure myClient;

void setup() {
  Serial.begin(115200); delay(50); Serial.println();
  Serial.println("ESP32 AWS IoT HTTPS REST PROGMEM Example");
  Serial.printf("SDK version: %s\n", ESP.getSdkVersion());

  Serial.print("Connecting to "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print(", WiFi connected, IP address: "); Serial.println(WiFi.localIP());

  myClient.setCACert(rootCA);
  myClient.setCertificate(certificate_pem_crt);
  myClient.setPrivateKey(private_pem_key);
}

void loop() {
  Serial.println(host);
  myClient.setTimeout(15000); // 15 Seconds timeout
  delay(1000);
  
  Serial.print("HTTPS Connecting to AWS IoT Core\n");
  int r = 0; // retry counter
  while ((!myClient.connect(host, Port)) && (r < 30)) {
    delay(100);
    Serial.print(".");
    r++;
  }
  if (r == 30) {
    Serial.println("Connection failed");
  } else {
    Serial.println("Connected");
  }

  char fakeData[256]; 
  float temperature = random(55, 77); // simulated temperature
  float humidity = random(77, 99);    // simulated humidity

  sprintf(fakeData, "{\"uptime\":%lu,\"temp\":%.2f,\"humid\":%.2f}", millis() / 1000, temperature, humidity);

  char postStr[64];
  sprintf(postStr, "POST %s HTTP/1.1", uri); // Construct HTTP POST line
  
  Serial.println("request is sending");
  
  myClient.println(postStr);
  myClient.print("Host: ");
  myClient.println(host);
  myClient.println("Content-Type: application/json");
  myClient.print("Content-Length: "); 
  myClient.println(strlen(fakeData));
  myClient.println(); // extra CRLF separating HTTP header and body
  myClient.println(fakeData);          

  Serial.println(fakeData);
  Serial.println("request sent");
  
  delay(10000);   // Keep socket open briefly to complete transmission
  myClient.stop(); // Close TLS socket to free heap memory
}