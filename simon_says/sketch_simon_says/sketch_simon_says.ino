
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
Sequence seq;

// level
int level = 1;

void setup() {
  // engage serial communication
  Serial.begin(SERIAL_BAUD_RATE);
  while (!Serial) { /* wait for serial port to connect */ }

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial << "Error: SSD1306 OLED Allocation Failed" << endl;
    for(;;); // Don't proceed, loop forever
  }

  drawText(1, SSD1306_WHITE, 0, 0, "Armond Says V1.0");

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
  for (int led : ledPinsVec) {
    pinMode(led, OUTPUT);
  }

  // set output pins (buzzer)
  //pinMode(PIEZO_BUZZER_PIN, OUTPUT);
}

void drawText(int size, int color, int x, int y, String text) {
  display.clearDisplay();

  display.setTextSize(size);              // Normal 1:1 pixel scale
  display.setTextColor(color); // Draw white text
  display.setCursor(x, y);              // Start at top-left corner
  display.println(text);

  display.display();
}

void generateSequence() {
  int storageArray[SEQUENCE_COUNT_MAX];
  seq.setStorage(storageArray);

  for (int i = 0; i < level; i++) {
    const int RAN_NUM = random(2, 7);
    seq.push_back(RAN_NUM);
    Serial << "Pushing back sequence: " << String(RAN_NUM) << endl;
  }
}

void activateSequence() {
  for (int d : seq) {
    Serial << "Activate sequence | Pin: " << String(d) << " -- setting HIGH!" << endl;
    digitalWrite(d, HIGH);
    delay(750);
    Serial << "Activate sequence | Pin: " << String(d) << " -- setting LOW!" << endl;
    digitalWrite(d, LOW);
  }

  return seq;
}

void getInputAndCheck() {
  bool isInputReceived = false;
  int keysInputted = 0;

  Serial << "Entering the while loop! | isInputReceived: " << isInputReceived << endl;
  
  while (!isInputReceived) {
    Serial << "Getting button status via digitalRead" << endl;
    int buttonRed = digitalRead(buttonPins[0]);
    int buttonGreen = digitalRead(buttonPins[1]);
    int buttonBlue = digitalRead(buttonPins[2]);
    int buttonWhite = digitalRead(buttonPins[3]);
    int buttonYellow = digitalRead(buttonPins[4]);

    if (buttonRed == HIGH) {
      Serial << "Red was pressed!" << endl;
      keysInputted++;
    }
    
    if (buttonGreen == HIGH) {
      Serial << "Green was pressed!" << endl;
      keysInputted++;
    }
    
    if (buttonBlue == HIGH) {
      Serial << "Blue was pressed!" << endl;
      keysInputted++;
    }
    
    if (buttonWhite == HIGH) {
      Serial << "White was pressed!" << endl;
      keysInputted++;
    }
    
    if (buttonYellow == HIGH) {
      Serial << "Yellow was pressed!" << endl;
      keysInputted++;
    }
    
    if (keysInputted >= level) {
      isInputReceived = true;
      Serial << "Breaking out of the loop | keysInputted: " << String(keysInputted) << " | Level: " << String(level) << endl;
    }

    delay(100);
  }

  // check the answer
}

void clearSequence() {
  for (int i = 0; i < seq.size(); i++) {
    seq.remove(i);
    Serial << "Clearing sequence: " << i << endl;
  }
}

void loop() {
  Serial << "Preparing to clear sequence" << endl;
  clearSequence();

  // display the level number
  drawText(1, SSD1306_WHITE, 0, 0, "Level: " + String(level));
  Serial << "Preparing to generate sequence" << endl;
  generateSequence();

  Serial << "Preparing to activate sequence" << endl;
  activateSequence();

  // get input
  Serial << "Preparing to get input" << endl;
  getInputAndCheck();

  delay(1000);

  Serial << "End of the main loop" << endl;
}