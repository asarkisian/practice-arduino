#include <Servo.h>

Servo s1;

void setup() {
  s1.attach(3);
}

void loop() {
  for (int i = 0; i < 180; i++) {
    s1.write(i);
    delay(15);
  }

  for (int i = 180; i > -1; i--) {
    s1.write(i);
    delay(15);
  }
}
