#include "LedControl.h"

const int DIN_PIN = 12;
const int CS_PIN = 11;
const int CLK_PIN = 10;

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN);

const byte X[8] = {
  B10000001,
  B01000010,
  B00100100,
  B00011000,
  B00011000,
  B00100100,
  B01000010,
  B10000001
};

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  Serial.begin(9600);
}

void display(const byte img[]) {
  for(int i = 0; i < 8; i++) {
    lc.setRow(0, i, img[i]);
  }
}

void loop() {
  display(X);
  delay(500);
  lc.clearDisplay(0);
  delay(500);
}