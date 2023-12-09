#include <Servo.h>
#include <Streaming.h>

const int LED_GREEN_PIN = 9; // PWM
const int SERVO_PIN = 10; // PWM
const int FLEX_SENSOR_PIN = A0;

Servo s1;

void setup() {
  Serial.begin(9600);

  s1.attach(SERVO_PIN);
  s1.write(0);

  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(FLEX_SENSOR_PIN, INPUT);
}

void loop() {
  int flexSensorRead = analogRead(FLEX_SENSOR_PIN);
  int flexAmount = map(flexSensorRead, 600, 900, 0, 180);

  Serial << "Flex Sensor Read: " << flexSensorRead << endl;
  Serial << "Flex Amount: " << flexAmount << endl;

  if (flexAmount > 170) {
    digitalWrite(LED_GREEN_PIN, HIGH);
  } else {
    digitalWrite(LED_GREEN_PIN, LOW);
  }
  
  s1.write(flexAmount);

  delay(100);
}