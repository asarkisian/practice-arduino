#include "LedControl.h"

#define JOYSTICK_X A0
#define JOYSTICK_Y A1

LedControl lc = LedControl(12, 10, 11, 1);

int dot[2] = { 0, 0 };

void displayDot(int row, int col) {
  bool isUpdate = false;

  if (row >= 0 && row <= 7) {
      dot[0] = row;
      isUpdate = true;
  }
  
  if(col >= 0 && col <= 7) {
    dot[1] = col;
    isUpdate = true;
  }
  
  if (isUpdate) {
    lc.clearDisplay(0);
    lc.setLed(0, dot[1], dot[0], true);
  }
}

void readJoystick() {
  const int readJoystickX = analogRead(JOYSTICK_X);
  const int readJoystickY = analogRead(JOYSTICK_Y);

  if (readJoystickX > 540) {
    Serial.println("Moving right");
    displayDot(dot[0]+1, dot[1]);
  } else if(readJoystickX < 490) {
    Serial.println("Moving left");
    displayDot(dot[0]-1, dot[1]);
  }

  if (readJoystickY > 540) {
    Serial.println("Moving down");
    displayDot(dot[0], dot[1]+1);
  } else if (readJoystickY < 490) {
    Serial.println("Moving up");
    displayDot(dot[0], dot[1]-1);
  }
}

void setup() {
  Serial.begin(9600);
  lc.shutdown(0, false);
  lc.clearDisplay(0);
  lc.setIntensity(0, 8);

  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
}

void loop() {
  readJoystick();
  delay(100);
}