/*
Circuit instructions (if not using I2C Backpack):

01. Arduino 5V to Breadboard Positive Bus
02. Arduino GND to Breadboard Negative Bus
03. Arduino Digital 12 to LCD RS (pin # 4)
04. Arduino Digital 11 to LCD E (pin # 6)
05. Arduino Digital 5 to LCD D4 (pin # 11)
06. Arduino Digital 4 to LCD D5 (pin # 12)
07. Arduino Digital 3 to LCD D6 (pin # 13)
08. Arduino Digital 2 to LCD D7 (pin # 14)
09. LCD VSS (pin # 1) to Breadboard Negative Bus
10. LCD VDD (pin # 2) to Breadboard Positive Bus
11. LCD VO (pin # 3) to either resistor (220 ohm) Breadboard Positive Bus "OR" 10k Potentiometer Middle/Output pin 
12. LCD A (pin # 15) to either resistor (220 ohm) Breadboard Positive Bus "OR" 10k Potentiometer Middle/Output pin
13. LCD K (pin # 16) to Breadboard Negative Bus
14. If Potentiometer(s) were used, be sure to connect the VCC to 5V and the GND to Arduino GND
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16,2);
}

void loop() {
  // do go down to the next row, modify the 2nd parameter to 1
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");

  delay(500);
}