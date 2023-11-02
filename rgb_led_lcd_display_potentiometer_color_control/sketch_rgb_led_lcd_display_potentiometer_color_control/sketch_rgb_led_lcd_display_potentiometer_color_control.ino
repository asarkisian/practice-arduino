/*
Circuit instructions for LCD portion (if not using I2C Backpack):

01. Arduino 5V to Breadboard Positive Bus
02. Arduino GND to Breadboard Negative Bus
03. Arduino Digital 12 to LCD RS (pin # 4)
04. Arduino GND to LCD RW (pin # 5)
05. Arduino Digital 11 to LCD E (pin # 6)
06. Arduino Digital 5 to LCD D4 (pin # 11)
07. Arduino Digital 4 to LCD D5 (pin # 12)
08. Arduino Digital 3 to LCD D6 (pin # 13)
09. Arduino Digital 2 to LCD D7 (pin # 14)
10. LCD VSS (pin # 1) to Breadboard Negative Bus
11. LCD VDD (pin # 2) to Breadboard Positive Bus
12. LCD VO (pin # 3) to either resistor (220 ohm) Breadboard Positive Bus "OR" 10k Potentiometer Middle/Output pin
 (this dims/brightens the text)
13. LCD A (pin # 15) to either resistor (220 ohm) Breadboard Positive Bus "OR" 10k Potentiometer Middle/Output pin
 (this dims/brightens the background)
14. LCD K (pin # 16) to Breadboard Negative Bus
15. If Potentiometer(s) were used, be sure to connect the VCC to 5V and the GND to Arduino GND
*/

//#include <LiquidCrystal.h>

//const int POT_RED = A2;
//const int POT_GREEN = A1;
//const int POT_BLUE = A0;

const int LED_RED = 3;
const int LED_GREEN = 5;
const int LED_BLUE = 6;

//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);

  //lcd.begin(16,2);

  //pinMode(POT_RED, INPUT);
  //pinMode(POT_GREEN, INPUT);
  //pinMode(POT_BLUE, INPUT);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

void loop() {
  //const int potRedRead = analogRead(POT_RED);
  //const int potGreenRead = analogRead(POT_GREEN);
  //const int potBlueRead = analogRead(POT_BLUE);

  //const int redAmount = map(potRedRead, 0, 1023, 0, 255);
  //const int greenAmount = map(potGreenRead, 0, 1023, 0, 255);
  //const int blueAmount = map(potBlueRead, 0, 1023, 0, 255);

  //lcd.clear();
  //lcd.setCursor(0, 0);
  //Serial.println("R(" + String(redAmount) + ") G(" + String(greenAmount) + ") B(" + String(blueAmount) + ")");
  
  analogWrite(LED_RED, 15);
  analogWrite(LED_GREEN, 20);
  analogWrite(LED_BLUE, 35);

  delay(250);
}