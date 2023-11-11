#include <Streaming.h>

const int WATER_SENSOR_PIN = A0;
const int THRESHOLD = 50;

void setup() {
  Serial.begin(9600);

  pinMode(WATER_SENSOR_PIN, INPUT);
}

void loop() {
  int waterSensorRead = analogRead(WATER_SENSOR_PIN);

  if (waterSensorRead > THRESHOLD) {
    Serial << "Water detected!" << endl;
  } else {
    Serial << "No water detected!" << endl;
  }

  delay(500);
}