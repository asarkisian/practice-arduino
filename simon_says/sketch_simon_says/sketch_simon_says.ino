
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Streaming.h>
#include <Vector.h>
#include <Wire.h>

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
uint8_t buttonPins[5] = {A0, A1, A2, A3, A4};

// led pins
int ledPins[5] = {2, 3, 4, 5, 6};

// buzzer pin
const int PIEZO_BUZZER_PIN = 7;

// sequence
const int SEQUENCE_COUNT_MAX = 30;
typedef Vector<int> Sequence;

void setup() {
  // engage serial communication
  Serial.begin(SERIAL_BAUD_RATE);
  while (!Serial) { /* wait for serial port to connect */ }

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial << "Error: SSD1306 OLED Allocation Failed" << endl;
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
  Vector<uint8_t> buttonPinsVec(buttonPins);
  for (uint8_t button : buttonPinsVec) {
    pinMode(button, INPUT);
  }

  // set output pins (leds)
  Vector<int> ledPinsVec(ledPins);
  for (int button : ledPinsVec) {
    pinMode(button, INPUT);
  }

  // set output pins (buzzer)
  //pinMode(PIEZO_BUZZER_PIN, OUTPUT);
}

void drawText(String text) {
  display.clearDisplay();

  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0,0);              // Start at top-left corner
  display.println(text);

  display.display();
}

Sequence generateSequence(int level) {
  Sequence buffer;
  int storageArray[SEQUENCE_COUNT_MAX];
  buffer.setStorage(storageArray);

  for (int i = 0; i < level; i++) {
    const int RAN_NUM = random(2, 7);
    buffer.push_back(RAN_NUM);
  }

  Serial << "Buffer ( in the function ): " << buffer << endl;

  return buffer;
}

Sequence activateSequence(Sequence seq) {
  Serial << "Sequence ( in the function ): " << seq << endl;
  for (int d : seq) {
    digitalWrite(d, HIGH);
    delay(750);
    digitalWrite(d, LOW);
  }

  Serial << "Sequence ( inside the FUNCTION ): " << seq << endl;

  return seq;
}

void loop() {
  static int level = 1;

  // display the level number
  drawText("Level: " + String(level));

  // display the light sequence + play sounds
  Sequence seq = activateSequence(generateSequence(level));

  Serial << "Sequence: (outside the FUNCTION) " << seq << endl;

  // get input
  //int buttonRed = digitalRead(BUTTON_RED_PIN);
  //int buttonGreen = digitalRead(BUTTON_GREEN_PIN);
  //int buttonBlue = digitalRead(BUTTON_BLUE_PIN);
  //int buttonWhite = digitalRead(BUTTON_WHITE_PIN);
  //int buttonYellow = digitalRead(BUTTON_YELLOW_PIN);

  // determine if correct

  // if correct --> go to next level
  // if not correct, display "Game Over" and restart back to level 1

  delay(1000);
}