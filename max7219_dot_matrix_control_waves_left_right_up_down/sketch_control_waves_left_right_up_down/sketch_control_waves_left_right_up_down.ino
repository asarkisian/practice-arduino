#include <LedControl.h>

const int JOYSTICK1_X = A0;
const int JOYSTICK1_Y = A1;
const int JOYSTICK1_Z = 2;

LedControl lc = LedControl(12, 10, 11, 1);
const byte name[6][8] = {
  { B00011000, B00100100, B01000010, B10000001, B11111111, B10000001, B10000001, B10000001 },
  { B11111110, B10000001, B10000001, B11111110, B10001000, B10000100, B10000010, B10000001 },
  { B10000001, B11000011, B10100101, B10011001, B10000001, B10000001, B10000001, B10000001 },
  { B01111110, B10000001, B10000001, B10000001, B10000001, B10000001, B10000001, B01111110 },
  { B10000001, B11000001, B10100001, B10010001, B10001001, B10000101, B10000011, B10000001 },
  { B11111000, B10000100, B10000010, B10000001, B10000001, B10000010, B10000100, B11111000 }
};

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
    for (int x = 0; x < 6; x++) {
      for (int i = 0; i < 8; i++) {
        lc.setRow(0, i, name[x][i]);
      }
      delay(500);
      lc.clearDisplay(0);
    }
    
    buttonToggle = !buttonToggle;
  } else {
    lc.clearDisplay(0);
  }

  delay(100);
}