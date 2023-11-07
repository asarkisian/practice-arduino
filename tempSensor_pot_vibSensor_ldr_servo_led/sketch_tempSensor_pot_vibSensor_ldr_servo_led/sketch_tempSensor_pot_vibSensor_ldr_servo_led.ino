#include <Servo.h>

Servo s1;

const int POT_SERVO_PIN = A0;
const int LDR_PIN = A1;
const int TEMP_SEN_PIN = A2;
const int LED_WHITE = 12;
const int LED_YELLOW = 11; // PWM
const int SERVO_PIN = 10; // PWM
const int VIB_SENSOR_PIN = 9; // PWM

const int LDR_THRESHOLD = 750;
const int VIBRATION_THRESHOLD = 50;

void setup() {
  // engage serial communication
  Serial.begin(9600);

  // set servo
  s1.attach(SERVO_PIN);
  s1.write(0);

  // set pins (input)
  pinMode(POT_SERVO_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(TEMP_SEN_PIN, INPUT);
  pinMode(VIB_SENSOR_PIN, INPUT);

  // set pins (output)
  pinMode(LED_YELLOW, OUTPUT);
}

void loop() {
  float voltage = analogRead(TEMP_SEN_PIN) * 0.004882813; // convert analog reading (0-1023)back to voltage from 0-5v

  float degreesC = (voltage - 0.5) * 100.0; // convert to celcius
  float degreesF = degreesC * (9.0 / 5.0) + 32.0; // convert to fahrenheit

  int potServoRead = analogRead(POT_SERVO_PIN);
  int ldrRead = analogRead(LDR_PIN);
  int vibSensorRead = pulseIn(VIB_SENSOR_PIN, HIGH);

  int servoAmount = map(potServoRead, 0, 1023, 0, 180);

  s1.write(servoAmount);

  if (vibSensorRead > VIBRATION_THRESHOLD) {
    digitalWrite(LED_WHITE, HIGH);
  } else {
    digitalWrite(LED_WHITE, LOW);
  }

  if (ldrRead < LDR_THRESHOLD) {
    digitalWrite(LED_YELLOW, HIGH);

    Serial.print("Temperature C: ");
    Serial.println(degreesC);

    Serial.print("Temperature F: ");
    Serial.println(degreesF);
  } else {
    digitalWrite(LED_YELLOW, LOW);
  }

  delay(100);
}