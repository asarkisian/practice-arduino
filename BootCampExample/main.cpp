#include <SPI.h>
 #include <MFRC522.h>
 #include <Wire.h>
 #include <LiquidCrystal_I2C.h>
 
 #define RST_PIN         5   
 #define SS_PIN          53   
 
 MFRC522 mfrc522(SS_PIN, RST_PIN);  
 
 // Define the key (UID) you want to compare against
 byte key[4] = {0x93, 0x63, 0x03, 0xB7};  // Replace with your RFID tag's UID bytes
 
 // Define LCD properties
 LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD I2C address and dimensions (16x2)
 
 // Define LED pins
 #define GREEN_LED_PIN   7
 #define RED_LED_PIN     6
 
 // Define buzzer pin
 #define BUZZER_PIN      4
 
 void setup() {
   Serial.begin(9600);   // Initialize serial communications
   SPI.begin();          // Init SPI bus
   mfrc522.PCD_Init();   // Init MFRC522
   Wire.begin();         // Init I2C bus for LCD
   
   // Init LCD with I2C address and dimensions
   lcd.begin(16, 2);     // Init LCD with 16 columns and 2 rows
   lcd.backlight();      // Ensure backlight is turned on
 
   pinMode(GREEN_LED_PIN, OUTPUT); // Set LED pins as outputs
   pinMode(RED_LED_PIN, OUTPUT);
   
   // Set buzzer pin as output
   pinMode(BUZZER_PIN, OUTPUT);
 
   // Initially turn off LEDs and buzzer, and display status
   digitalWrite(GREEN_LED_PIN, LOW);
   digitalWrite(RED_LED_PIN, LOW);
   digitalWrite(BUZZER_PIN, LOW);
 }
 
 void loop() {
   // Look for new cards
   if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
     // Check if the UID matches the predefined key
     bool uidMatched = true;
     for (byte i = 0; i < mfrc522.uid.size; i++) {
       if (mfrc522.uid.uidByte[i] != key[i]) {
         uidMatched = false;
         break;
       }
     }
 
     // Control LEDs and LCD based on UID match
     if (uidMatched) {
       digitalWrite(GREEN_LED_PIN, HIGH); // Turn on green LED
       digitalWrite(RED_LED_PIN, LOW);    // Turn off red LED
       digitalWrite(BUZZER_PIN, LOW);     // Ensure buzzer is off
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("Access granted");
       lcd.setCursor(0, 1);
       lcd.print("Door is open");
       Serial.println("Access granted - Green LED on");
     } else {
       digitalWrite(GREEN_LED_PIN, LOW);  // Turn off green LED
       digitalWrite(RED_LED_PIN, HIGH);   // Turn on red LED
       digitalWrite(BUZZER_PIN, HIGH);    // Turn on buzzer
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("Access denied");
       lcd.setCursor(0, 1);
       lcd.print("Door is closed");
       Serial.println("Access denied - Red LED on");
     }
 
     mfrc522.PICC_HaltA();      // Halt PICC
     mfrc522.PCD_StopCrypto1(); // Stop encryption on PCD
   }
 
   delay(1000); // Delay before scanning for a new card
 }
