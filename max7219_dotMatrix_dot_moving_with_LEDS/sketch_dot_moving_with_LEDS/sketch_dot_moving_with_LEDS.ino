#include "LedControl.h"

#define JOYSTICK1_X A0
#define JOYSTICK1_Y A1
#define JOYSTICK1_Z 13

#define LED_YELLOW 9
#define LED_RED 8

// instantiate the led dot matrix
LedControl lc = LedControl(12, 10, 11, 1);
short dot[] = {0, 0};

void checkLED() {
  // turn YELLOW LED on only if the dot is on one of the 4 corners
  if (
    dot[0] == 0 && dot[1] == 0 ||
    dot[0] == 0 && dot[1] == 7 ||
    dot[0] == 7 && dot[1] == 0 ||
    dot[0] == 7 && dot[1] == 7
    ) {
      digitalWrite(LED_YELLOW, HIGH);
    } else {
      digitalWrite(LED_YELLOW, LOW);
    }
  
  // turn RED LED on only if dot is on one of the 4 center squares
  if (
    dot[0] == 3 && dot[1] == 3 ||
    dot[0] == 3 && dot[1] == 4 ||
    dot[0] == 4 && dot[1] == 3 ||
    dot[0] == 4 && dot[1] == 4
    ) {
      digitalWrite(LED_RED, HIGH);
  } else {
      digitalWrite(LED_RED, LOW);
  }
}

void moveDot(const short row, const short col) {
  bool isUpdateScreen = false;

  // only display the dot if within X boundaries
  if (row >= 0 && row <= 7) {
    dot[0] = row;
    isUpdateScreen = true;
  }

  // only display the dot if within Y boundaries
  if (col >= 0 && col <= 7) {
    dot[1] = col;
    isUpdateScreen = true;
  }

  if (isUpdateScreen) {
    lc.clearDisplay(0);
    lc.setLed(0, dot[0], dot[1], true);
  }
}

void readJoystick1() {
  if (analogRead(JOYSTICK1_X) > 530) {
    moveDot(dot[0], dot[1] + 1);
  } else if (analogRead(JOYSTICK1_X) < 510) {
    moveDot(dot[0], dot[1] - 1);
  }

  if (analogRead(JOYSTICK1_Y) > 530) {
    moveDot(dot[0] + 1, dot[1]);
  } else if (analogRead(JOYSTICK1_Y) < 510) {
    moveDot(dot[0] - 1, dot[1]);
  }
}

void setup() {
  // engage serial communication
  Serial.begin(9600);

  // setup the joystick
  pinMode(JOYSTICK1_X, INPUT);
  pinMode(JOYSTICK1_Y, INPUT);
  pinMode(JOYSTICK1_Z, INPUT);

  // setup led(s)
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  // setup the led dot matrix
  lc.shutdown(0, false);
  lc.clearDisplay(0);
  lc.setIntensity(0, 8);
  lc.setLed(0, dot[0], dot[1], true);
}

void loop() {
  readJoystick1();
  checkLED();

  delay(100);
}