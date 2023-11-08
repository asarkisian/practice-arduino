#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SERIAL_BAUD_RATE 9600
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 

// instantiate Adafruit object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// button pins
const int BUTTON_RED_PIN = A0;
const int BUTTON_GREEN_PIN = A1;
const int BUTTON_BLUE_PIN = A2;
const int BUTTON_WHITE_PIN = A3;
const int BUTTON_YELLOW_PIN = A4;

// led pins
const int LED_RED = 6;
const int LED_GREEN = 5;
const int LED_BLUE = 4;
const int LED_WHITE = 3;
const int LED_YELLOW = 2;

void drawText(String text) {
  display.clearDisplay();

  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0,0);              // Start at top-left corner
  display.println(text);

  display.display();
}

void setup() {
  // engage serial communication
  Serial.begin(SERIAL_BAUD_RATE);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 OLED allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  drawText("Armond Says V1.0");

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the display buffer
  display.clearDisplay();

  // set input pins (buttons)
  pinMode(BUTTON_RED_PIN, INPUT);
  pinMode(BUTTON_GREEN_PIN, INPUT);
  pinMode(BUTTON_BLUE_PIN, INPUT);
  pinMode(BUTTON_WHITE_PIN, INPUT);
  pinMode(BUTTON_YELLOW_PIN, INPUT);

  // set output pins (leds)
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_WHITE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);      
}

void loop() {
  int buttonRed = digitalRead(BUTTON_RED_PIN);
  int buttonGreen = digitalRead(BUTTON_GREEN_PIN);
  int buttonBlue = digitalRead(BUTTON_BLUE_PIN);
  int buttonWhite = digitalRead(BUTTON_WHITE_PIN);
  int buttonYellow = digitalRead(BUTTON_YELLOW_PIN);

  if (buttonRed == HIGH) {
    digitalWrite(LED_RED, HIGH);
  } else {
    digitalWrite(LED_RED, LOW);
  }

  if (buttonGreen == HIGH) {
    digitalWrite(LED_GREEN, HIGH);
  } else {
    digitalWrite(LED_GREEN, LOW);
  }

  if (buttonBlue == HIGH) {
    digitalWrite(LED_BLUE, HIGH);
  } else {
    digitalWrite(LED_BLUE, LOW);
  }

  if (buttonWhite == HIGH) {
    digitalWrite(LED_WHITE, HIGH);
  } else {
    digitalWrite(LED_WHITE, LOW);
  }

  if (buttonYellow == HIGH) {
    digitalWrite(LED_YELLOW, HIGH);
  } else {
    digitalWrite(LED_YELLOW, LOW);
  }

  drawText("Hello Armond");

  delay(100);
}