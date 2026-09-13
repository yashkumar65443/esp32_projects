// ESP32 / Arduino Serial UART Receiver
// Buffers incoming bytes until packet delimiter ('\r') is received

char buff[50];
volatile byte indx = 0;

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    byte c = Serial.read();

    // Prevent buffer overflow (leaving room for null terminator)
    if (indx < sizeof(buff) - 1) {
      buff[indx++] = c; // Append character to buffer

      // Check for packet delimiter ('\r')
      if (c == '\r') {
        buff[indx] = '\0';      // Null-terminate string
        Serial.println(buff);   // Print complete packet
        indx = 0;               // Reset index for next incoming packet
        delay(1000);
      }
    } else {
      // If buffer overflows without delimiter, reset buffer safely
      indx = 0;
    }
  }
}
