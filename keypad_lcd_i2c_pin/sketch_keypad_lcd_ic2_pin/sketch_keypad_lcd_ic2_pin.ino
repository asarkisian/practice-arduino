#include <Keypad.h> // external download
#include <LiquidCrystal_I2C.h> //external download

/*
Module: LCD (w/ I2C Backpack)
GND <---> GND
VCC <---> 5V
SDA <---> A4
SCL <---> A5
*/

/*
Module: Keypad
- R for Row
- C for Column
R1 <---> D9
R2 <---> D8
R3 <---> D7
R4 <---> D6
C1 <---> D5
C2 <---> D4
C3 <---> D3
C4 <---> D2
*/

// LCD
const int LCD_COLUMNS = 20;
const int LCD_ROWS = 4;
LiquidCrystal_I2C lcd(0x27, LCD_COLUMNS, LCD_ROWS);

// LED
const int LED_GREEN = 10; // PWM
const int POT_LED = A0;

// KEYPAD
const int KEYPAD_ROW = 4;
const int KEYPAD_COLUMN = 4;
const char keys[KEYPAD_ROW][KEYPAD_COLUMN] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
};
byte pin_rows[KEYPAD_ROW] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[KEYPAD_COLUMN] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, KEYPAD_ROW, KEYPAD_COLUMN );
const String LOGIN = "3002"; // Engage the LED
const String LOGOUT = "0"; // Disengage the LED
const int INPUT_MAX_CHARACTERS = 4;
String userPassword = "";

void setup() {
  // engage serial communication
  Serial.begin(9600);

  // engage lcd
  lcd.init();
  lcd.clear();
  lcd.backlight();

  // setup pins
  pinMode(LED_GREEN, OUTPUT);
  pinMode(POT_LED, INPUT);

  // set keypad config
  userPassword.reserve(INPUT_MAX_CHARACTERS);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Code: ");
}

void loop() {
  //get potentiometer value
  const int potReading = analogRead(POT_LED);
  const int ledBrightness = map(potReading, 0, 1023, 0, 255);

  // logged in status
  static bool isLoggedIn = true;

  // get keypad input
  char key = keypad.getKey();
  
  // check the key
  if (key){
    Serial.println(key);
    lcd.setCursor(12, 0);
    lcd.print('*');

    if (key == '*') {
      userPassword = "";
    }
    else if (key == '#') {
      Serial.println("Comparing: ");
      Serial.print("User Password: ");
      Serial.println(userPassword);
      Serial.print("Secret Password: ");
      Serial.println(LOGIN);
      delay(5000);
      if (userPassword == LOGIN) {
        analogWrite(LED_GREEN, ledBrightness);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("                    ");
        lcd.setCursor(0, 1);
        lcd.print("You are logged in!");
        Serial.println("You are logged in!");
        isLoggedIn = true;
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter Code: ");
        userPassword = "";
      } else if(userPassword == LOGOUT){
        if (isLoggedIn) {
          analogWrite(LED_GREEN, 0);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("                    ");
          lcd.setCursor(0, 1);
          lcd.print("You are logged out!");
          Serial.println("You are logged out!");
          isLoggedIn = false;
          delay(1000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Enter Code: ");
          userPassword = "";
        }
      }
      
      userPassword += key;
    }
  }

  delay(100);
}