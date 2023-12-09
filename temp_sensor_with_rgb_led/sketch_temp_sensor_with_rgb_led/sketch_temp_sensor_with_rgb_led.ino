#include <Streaming.h>

const int TEMP_SENSOR_PIN = A0;
const int LED_RGB_RED_PIN = 3; // PWM
const int LED_RGB_GREEN_PIN = 5; // PWM
const int LED_RGB_BLUE_PIN = 6; // PWM

void setup() {
  Serial.begin(9600);

  pinMode(TEMP_SENSOR_PIN, INPUT);

  pinMode(LED_RGB_RED_PIN, OUTPUT);
  pinMode(LED_RGB_GREEN_PIN, OUTPUT);
  pinMode(LED_RGB_BLUE_PIN, OUTPUT);
}

void setColor(int redAmount, int greenAmount, int blueAmount) {
  analogWrite(LED_RGB_RED_PIN, redAmount);
  analogWrite(LED_RGB_GREEN_PIN, greenAmount);
  analogWrite(LED_RGB_BLUE_PIN, blueAmount);
}

void loop() {
  float voltage = analogRead(TEMP_SENSOR_PIN) * (5.0 / 1024.0);
  float temperatureC = ((voltage) - 0.5) * 100;
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;

  if (temperatureF >= 79.0 && temperatureF < 79.9) {
    setColor(255, 0, 0);
    delay(250);
  } else if (temperatureF >= 80.00 && temperatureF < 80.9) {
    setColor(0, 255, 0);
    delay(250);
  } else if (temperatureF >= 81.00) {
    setColor(0, 0, 255);
    delay(250);
  }

  Serial << "Temperature (C): " << temperatureC << endl;
  Serial << "Temperature (F): " << temperatureF << endl;

  delay(250);
}