#include <LedControl.h>

const int JOYSTICK1_X = A0;
const int JOYSTICK1_Y = A1;
const int JOYSTICK1_Z = 2;

LedControl lc = LedControl(12, 10, 11, 1);
const byte X[] = { B10000001, B01000010, B00100100, B00011000, B00011000, B00100100, B01000010, B10000001 };

void setup() {
  Serial.begin(9600);

  pinMode(JOYSTICK1_X, INPUT);
  pinMode(JOYSTICK1_Y, INPUT);
  pinMode(JOYSTICK1_Z, INPUT_PULLUP);

  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  Serial.println("Setup complete");
}

void loop() {
  const int joystick1_x = analogRead(JOYSTICK1_X);
  const int joystick1_y = analogRead(JOYSTICK1_Y);
  const int joystick1_z = digitalRead(JOYSTICK1_Z);
  static bool buttonToggle = false;

  if (joystick1_x > 550) {
    for (int i = 0; i < 8; i++) {
      lc.setColumn(0, i, B11111111);
      delay(100);
      lc.clearDisplay(0);
    }
  } else if (joystick1_x < 380) {
    for (int i = 7; i > -1; i--) {
      lc.setColumn(0, i, B11111111);
      delay(100);
      lc.clearDisplay(0);
    }
  }
  
  if (joystick1_y > 550) {
    for (int i = 0; i < 8; i++) {
      lc.setRow(0, i, B11111111);
      delay(100);
      lc.clearDisplay(0);
    }
  } else if (joystick1_y < 380) {
    for (int i = 7; i > -1; i--) {
      lc.setRow(0, i, B11111111);
      delay(100);
      lc.clearDisplay(0);
    }
  }

  if (joystick1_z == 0) {
    buttonToggle = !buttonToggle;
    delay(100);
  }

  if (buttonToggle == true) {
    for (int i = 7; i > -1; i--) {
      lc.setRow(0, i, X[i]);
    }
  } else {
    lc.clearDisplay(0);
  }

  delay(100);
}