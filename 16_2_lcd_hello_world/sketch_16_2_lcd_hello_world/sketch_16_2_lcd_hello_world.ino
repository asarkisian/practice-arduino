/*
Circuit instructions (if not using I2C Backpack):

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
  lcd.setCursor(0, 1);
  lcd.print("This is a test");

  delay(500);
}
