/*
#include <Wire.h>
#define SLAVE_ADDR 9
int analogPin = A3;
int val = 0;
void setup() {
  // Initialize I2C communications as Master
  Wire.begin();
}
void loop() {
  delay(50);
  // Read pot value
  // Map to range of 1-255 for flash rate
  val = map(analogRead(analogPin), 0, 1023, 255, 1);
  // Write a charatre to the Slave
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(val);
  Wire.endTransmission();
}
*/
#include <Wire.h>
#define SLAVE_ADDR 9
int LED = 13;
int rd; // Variable for received data
int br; // Variable for blink rate

void setup() {
  pinMode(LED, OUTPUT);
  Wire.begin(SLAVE_ADDR);
  Wire.onReceive(receiveEvent); // Function to run when data received from master
  Serial.begin(9600);
}

void receiveEvent() {
  rd = Wire.read(); // read one character from the I2C
  Serial.println(rd); // Print value of incoming data
}

void loop() {
  delay(50);
  br = map(rd, 1, 255, 100, 2000); // Calculate blink value
  digitalWrite(LED, HIGH); delay(br);
  digitalWrite(LED, LOW); delay(br);
}
