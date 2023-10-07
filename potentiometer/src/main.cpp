#include <Arduino.h>

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void measure() {
  int sensor1 = analogRead(A0);
  if (sensor1 < 500) {
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
  } else {
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
  }
}

void loop() {
  measure();
}
