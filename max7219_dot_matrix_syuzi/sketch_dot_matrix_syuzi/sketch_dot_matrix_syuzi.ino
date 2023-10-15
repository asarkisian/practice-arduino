#include "LedControl.h"

LedControl lc = LedControl(12, 10, 11);

const byte S[8] = {
  B11111111,
  B10000000,
  B10000000,
  B11111111,
  B00000001,
  B00000001,
  B00000001,
  B11111111
};

const byte Y[8] = {
  B10000010,
  B01000100,
  B00101000,
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B00010000
};

const byte U[8] = {
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B11111111
};

const byte Z[8] = {
  B11111111,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B11111111
};

const byte I[8] = {
  B11111111,
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B11111111
};

void display(const byte img[]) {
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
  display(S);
  delay(500);
  lc.clearDisplay(0);
  display(Y);
  delay(500);
  lc.clearDisplay(0);
  display(U);
  delay(500);
  lc.clearDisplay(0);
  display(Z);
  delay(500);
  lc.clearDisplay(0);
  display(I);
  delay(500);
  lc.clearDisplay(0);
  delay(500);
}