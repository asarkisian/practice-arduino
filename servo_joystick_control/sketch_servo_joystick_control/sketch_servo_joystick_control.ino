#include <Servo.h>

const int JOYSTICK1_X = A0;
const int JOYSTICK1_Y = A1;
const int JOYSTICK1_Z = 13;

Servo s1;
Servo s2;

void setup() {
  // engage serial communication
  Serial.begin(9600);

  // setup pins (input)
  pinMode(JOYSTICK1_X, INPUT);
  pinMode(JOYSTICK1_Y, INPUT);
  pinMode(JOYSTICK1_Z, INPUT_PULLUP);  

  // setup servos
  s1.attach(11);
  s1.write(0);
  s2.attach(10);
  s2.write(0);
}

void loop() {
  int joystick1_x = analogRead(JOYSTICK1_X);
  int joystick1_y = analogRead(JOYSTICK1_Y);
  int joystick1_z = digitalRead(JOYSTICK1_Z);

  int joystick1_x_180 = map(joystick1_x, 0, 1023, 0, 180);
  int joystick1_y_180 = map(joystick1_y, 0, 1023, 0, 180);

  s1.write(joystick1_x_180);
  s2.write(joystick1_y_180);

  // start scanning if joystick z is pressed
  if (joystick1_z == 0) {
    s1.write(0);
    s2.write(0);
    for (int i = 0; i < 180; i++) {
      s1.write(i);
      s2.write(i);
      delay(15);
    }

    for (int i = 180; i >= 0; i--) {
      s1.write(i);
      s2.write(i);
      delay(15);
    }
  }

  delay(1000);
}