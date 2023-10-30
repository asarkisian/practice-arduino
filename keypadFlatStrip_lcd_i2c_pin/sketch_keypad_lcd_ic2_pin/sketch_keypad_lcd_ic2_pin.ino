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
Module: Flat Strip Keypad
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
String userCode = "";

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
  userCode.reserve(INPUT_MAX_CHARACTERS);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Code: ");
}

void displayScreen(const String lines[]) {
  lcd.clear();

  for (int i = 0; i < 4; i++) {
    if (lines[i] != "") {
      lcd.setCursor(0, i);
      lcd.print(lines[i]);
    }
  }
}

void loop() {
  //get potentiometer value
  const int potReading = analogRead(POT_LED);
  const int ledBrightness = map(potReading, 0, 1023, 0, 255);

  // user status
  static String hiddenCode = "";
  static bool isLoggedIn = false;
  static int failedAttempts = 0;
  const int MAX_ATTEMPTS = 5;
  int codeLength = 0;

  // get keypad input
  char key = keypad.getKey();

  // check the key
  if (key){
    codeLength += 1;
    Serial.println(key);
    lcd.setCursor(12, 0);
    for (int i = 0; i < codeLength; i++) {
      hiddenCode += "*";
    }
    lcd.print(hiddenCode);

    if (key == '*') {
      userCode = "";
      hiddenCode = "";
      codeLength = 0;
      const String screen[4] = {"Enter code: ", "", "", ""};
      displayScreen(screen);
    }
    else if (key == '#') {
      if (userCode == LOGIN) {
        
        // reset attempts
        failedAttempts = 0;

        if (isLoggedIn) {
          analogWrite(LED_GREEN, ledBrightness);
          const String screen[4] = {"Enter code: ", "", "Already logged in!", ""};
          displayScreen(screen);
          userCode = "";
          hiddenCode = "";
          codeLength = 0;
        } else {
          isLoggedIn = true;
          analogWrite(LED_GREEN, ledBrightness);
          const String screen[4] = {"Enter code: ", "", "You are logged in!", ""};
          displayScreen(screen);
          userCode = "";
          hiddenCode = "";
          codeLength = 0;
        }
      } else if(userCode == LOGOUT){
        if (isLoggedIn) {
          isLoggedIn = false;
          analogWrite(LED_GREEN, 0);
          const String screen[4] = {"Enter code: ", "", "You are logged out!", ""};
          displayScreen(screen);
          userCode = "";
          hiddenCode = "";
          codeLength = 0;
        } else {
          const String screen[4] = {"Enter code: ", "", "Already logged out!", ""};
          displayScreen(screen);
          userCode = "";
          hiddenCode = "";
          codeLength = 0;
        }
      } else {
        if (!isLoggedIn) {
          String attemptsStr = "Tries: " + String(failedAttempts+1) + "/5";
          const String screen[4] = {"Enter code: ", "", "Invalid code!", attemptsStr};
          displayScreen(screen);
          userCode = "";
          hiddenCode = "";
          codeLength = 0;
          failedAttempts += 1;

          if (failedAttempts >= MAX_ATTEMPTS) {
            const String screen[4] = {"Access denied: ", "", "Locked - 30 minutes!", ""};
            displayScreen(screen);
            userCode = "";
            delay(60*60*30);
            failedAttempts = 0;     
          }
        } else {
          userCode = "";
          hiddenCode = "";
          codeLength = 0;
          const String screen[4] = {"Enter code: ", "", "", ""};
          displayScreen(screen);
        }
      }
    } else {
      userCode += key;
      Serial.println(userCode);
    }
  }

  delay(100);
}