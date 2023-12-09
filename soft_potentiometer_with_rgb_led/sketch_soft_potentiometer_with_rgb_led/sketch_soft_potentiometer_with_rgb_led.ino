#include <Streaming.h>

const int SOFT_POT_PIN = A0;
const int LED_RGB_RED = 9; // PWM
const int LED_RGB_GREEN = 10; // PWM
const int LED_RGB_BLUE = 11; // PWM

void setup() {
  Serial.begin(9600);

  pinMode(SOFT_POT_PIN, INPUT);
  pinMode(LED_RGB_RED, OUTPUT);
  pinMode(LED_RGB_GREEN, OUTPUT);
  pinMode(LED_RGB_BLUE, OUTPUT);
}

void setColors(int redAmount, int greenAmount, int blueAmount) {
  analogWrite(LED_RGB_RED, redAmount);
  analogWrite(LED_RGB_GREEN, greenAmount);
  analogWrite(LED_RGB_BLUE, blueAmount);
}

void loop() {
  int softPotRead = analogRead(SOFT_POT_PIN);
  int redValue, greenValue, blueValue;
  int mapRGB1, mapRGB2, constrained1, constrained2;
 
  mapRGB1 = map(softPotRead, 0, 341, 255, 0);
  constrained1 = constrain(mapRGB1, 0, 255);

  mapRGB2 = map(softPotRead, 682, 1023, 0, 255);
  constrained2 = constrain(mapRGB2, 0, 255);

  redValue = constrained1 + constrained2; //Create the red peak
  
  //Create the green peak
  //Note that we are nesting functions (which requires fewer variables)
  
  greenValue = constrain(map(softPotRead, 0, 341, 0, 255), 0, 255)
             - constrain(map(softPotRead, 341, 682, 0,255), 0, 255);

  //Create the blue peak          
  blueValue = constrain(map(softPotRead, 341, 682, 0, 255), 0, 255)
            - constrain(map(softPotRead, 682, 1023, 0, 255), 0, 255);

  setColors(redValue, greenValue, blueValue);
  delay(500);
}