#include <LedControl.h>

#define JOYSTICK1_X A0
#define JOYSTICK1_Y A1
#define JOYSTICK1_BTN 9

LedControl lc = LedControl(12, 10, 11, 1);

short dot1[2] = {
  0,
  0
};

void setup() {
  // initialize serial communications
  Serial.begin(9600);

  // initialize the led dot matrix
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  // assign joystick pins
  pinMode(JOYSTICK1_X, INPUT);
  pinMode(JOYSTICK1_Y, INPUT);
  pinMode(JOYSTICK1_BTN, INPUT_PULLUP);

  // initial draw of dot
  lc.setLed(0, dot1[0], dot1[1], true);
}

void paintScreen() {
    lc.setLed(0, dot1[0], dot1[1], true);
}

void drawDot1(const short row, const short col) {
  bool isUpdateScreen = false;

  if (row >= 0 && row <= 7) {
    isUpdateScreen = true;
    dot1[0] = row;
  }

  if (col >= 0 && col <= 7) {
    isUpdateScreen = true;
    dot1[1] = col;
  }

  if (isUpdateScreen) {
    paintScreen();
  }
}

void readJoystick1() {
  const int readJoystick1X = analogRead(JOYSTICK1_X);
  const int readJoystick1Y = analogRead(JOYSTICK1_Y);
  const int readJoystick1Btn = digitalRead(JOYSTICK1_BTN);

  if (readJoystick1Btn == 0) {
    lc.clearDisplay(0);
  }

  if (readJoystick1X > 530) {
    drawDot1(dot1[0], dot1[1]+1);
  } else if (readJoystick1X < 515) {
    drawDot1(dot1[0], dot1[1]-1);
  }

  if (readJoystick1Y > 530) {
    drawDot1(dot1[0]+1, dot1[1]);
  } else if (readJoystick1Y < 515) {
    drawDot1(dot1[0]-1, dot1[1]);
  }
}

void loop() {
  readJoystick1();
  delay(100);
}