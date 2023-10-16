#include <LedControl.h>

using namespace std;

#define JOYSTICK1_X A0
#define JOYSTICK1_Y A1
#define JOYSTICK2_X A2
#define JOYSTICK2_Y A3

LedControl lc = LedControl(12, 10, 11, 1);

short dot1[2] = {
  0,
  0
};

short dot2[2] = {
  7,
  7
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

  pinMode(JOYSTICK2_X, INPUT);
  pinMode(JOYSTICK2_Y, INPUT);

  // initial draw of dots
  lc.setLed(0, dot1[0], dot1[1], true);
  lc.setLed(0, dot2[0], dot2[1], true);
}

void paintScreen() {
    lc.clearDisplay(0);
    lc.setLed(0, dot1[0], dot1[1], true);
    lc.setLed(0, dot2[0], dot2[1], true);
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

void drawDot2(const short row, const short col) {
  bool isUpdateScreen = false;

  if (row >= 0 && row <= 7) {
    isUpdateScreen = true;
    dot2[0] = row;
  }

  if (col >= 0 && col <= 7) {
    isUpdateScreen = true;
    dot2[1] = col;
  }

  if (isUpdateScreen) {
    paintScreen();
  }
}

void readJoystick1() {
  const int readJoystick1X = analogRead(JOYSTICK1_X);
  const int readJoystick1Y = analogRead(JOYSTICK1_Y);

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

void readJoystick2() {
  const int readJoystick2X = analogRead(JOYSTICK2_X);
  const int readJoystick2Y = analogRead(JOYSTICK2_Y);

  if (readJoystick2X > 530) {
    drawDot2(dot2[0], dot2[1]+1);
  } else if (readJoystick2X < 500) {
    drawDot2(dot2[0], dot2[1]-1);
  }

  if (readJoystick2Y > 530) {
    drawDot2(dot2[0]+1, dot2[1]);
  } else if (readJoystick2Y < 515) {
    drawDot2(dot2[0]-1, dot2[1]);
  }
}

void loop() {
  readJoystick1();
  readJoystick2();
  delay(100);
}