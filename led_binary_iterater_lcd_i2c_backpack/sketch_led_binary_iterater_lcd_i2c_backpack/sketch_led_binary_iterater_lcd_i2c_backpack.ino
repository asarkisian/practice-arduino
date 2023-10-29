#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/*
I2C Board of LCD Arduino
GND <---> GND
VCC <---> 5V
SDA <---> A4
SCL <---> A5
*/

//initialize lcd
LiquidCrystal_I2C lcd(0x27, 20, 4);

const int LEDS[] = {13, 12, 11, 10, 9, 8, 7, 6};

void setup() {
  // engage serial communication
  Serial.begin(9600);
  
  // set pins
  for (int i = 0; i < 8; i++) {
    pinMode(LEDS[i], OUTPUT);
  }
  
  // setup lcd
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  // Print a message on both lines of the LCD.
  //lcd.cursor(column,row) index starts at 0
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("LED Binary Seq");
  
  lcd.setCursor(2,1);   //Move cursor to character 2 on line 1
  lcd.print("By Armond");
}

void loop() {
  int geometricSequence[8] = {128, 64, 32, 16, 8, 4, 2, 1};
  int myByte[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  String myByteStr = "";
  unsigned int tally = 0;
  
  delay (500);
  
  // traverse the geometric sequence (up to 128)
  for (int x = 1; x < 129; x++) {
    // reset values
    for (int p = 0; p < 8; p++) {
      myByte[p] = 0; 
    }
    tally = 0;
    myByteStr = "";

    // determine which bits are on/off
    for (int i = 0; i < 8; i++) {
      if ((geometricSequence[i] + tally) <= x) {
        tally += geometricSequence[i];
        myByte[i] = 1;
      }
      myByteStr += myByte[i]; // to display to LCD
    }
    
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Decimal: " + String(x));
    lcd.setCursor(2, 1);
    lcd.print(myByteStr);

    // turn LED on based on whether bit is on or off
    for (int i = 0; i < 8; i++) {
      if (myByte[i] == 1) {
        digitalWrite(LEDS[i], HIGH);
      }
    }

    delay(500);

    // turn all LEDS off
    for (int i = 0; i < 8; i++) {
      digitalWrite(LEDS[i], LOW);
    }
  }
}