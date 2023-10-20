#include "LedControl.h"

LedControl lc = LedControl(12, 10, 11, 1);

const byte X[8] = {
  B10000001,
  B01000010,
  B00100100,
  B00011000,
  B00011000,
  B00100100,
  B01000010,
  B10000001,
};

const byte Y[8] = {
  B10000001,
  B01000010,
  B00100100,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
};

const byte Z[8] = {
  B11111111,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B11111111,
};

void display(const byte img[]) {
  lc.clearDisplay(0);

  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, img[i]);
  }
}

void setup() {
  Serial.begin(9600);
  lc.shutdown(0, false);
  lc.clearDisplay(0);
  lc.setIntensity(0, 8);
}

void loop() {
  display(X);
  delay(500);
  display(Y);
  delay(500);
  display(Z);
  delay(500);
}