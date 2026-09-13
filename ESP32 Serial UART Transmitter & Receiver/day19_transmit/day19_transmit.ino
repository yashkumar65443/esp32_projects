// ESP32 / Arduino Serial UART Transmitter
// Transmits delimited string packets periodically over Hardware Serial / UART

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
}

void loop() {
  // Transmit payload with carriage return ('\r') packet delimiter
  Serial.print("CAT\r");

  // Send packet every 1 second
  delay(1000);
}
