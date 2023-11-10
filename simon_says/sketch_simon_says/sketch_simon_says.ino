#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LinkedList.h>
#include <SPI.h>
#include <Streaming.h>
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
const int SEQUENCE_COUNT_MAX = 10;
LinkedList<int> mySeq = LinkedList<int>();
LinkedList<int> seq = LinkedList<int>();

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
  for (int i = 0; i < 5; i++) {
    pinMode(buttonPins[i], INPUT);
  }

  // set output pins (leds)
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // set output pins (buzzer)
  //pinMode(PIEZO_BUZZER_PIN, OUTPUT);
}

void drawText(int size, int color, int x, int y, String text) {
  display.clearDisplay();
  display.setTextSize(size);
  display.setTextColor(color);
  display.setCursor(x, y);
  display.println(text);
  display.display();
}

void generateSequence() {
  Serial << "Preparing to push back. We are at level: " << level << endl;
  for (int i = 0; i < level; i++) {
    const int RAN_NUM = random(2, 7);
    seq.add(RAN_NUM);
    Serial << "Pushing back sequence: " << String(RAN_NUM) << endl;
  }
}

void activateSequence() {
  for (int i = 0; i < seq.size(); i++) {
    Serial << "Activate sequence | Pin: " << seq.get(i) << " -- setting HIGH!" << endl;
    digitalWrite(seq.get(i), HIGH);
    delay(1000);
    Serial << "Activate sequence | Pin: " << seq.get(i) << " -- setting LOW!" << endl;
    digitalWrite(seq.get(i), LOW);
  }
}

bool getInputAndCheck() {
  while (mySeq.size() < seq.size()) {
    int buttonRed = digitalRead(buttonPins[0]);
    int buttonGreen = digitalRead(buttonPins[1]);
    int buttonBlue = digitalRead(buttonPins[2]);
    int buttonWhite = digitalRead(buttonPins[3]);
    int buttonYellow = digitalRead(buttonPins[4]);

    if (buttonRed == HIGH) {
      Serial << "Red was pressed!" << endl;
      mySeq.add(6);
      delay(100);
    }
    
    if (buttonGreen == HIGH) {
      Serial << "Green was pressed!" << endl;
      mySeq.add(5);
      delay(100);
    }
    
    if (buttonBlue == HIGH) {
      Serial << "Blue was pressed!" << endl;
      mySeq.add(4);
      delay(100);
    }
    
    if (buttonWhite == HIGH) {
      Serial << "White was pressed!" << endl;
      mySeq.add(3);
      delay(100);
    }
    
    if (buttonYellow == HIGH) {
      Serial << "Yellow was pressed!" << endl;
      mySeq.add(2);
      delay(100);
    }
  }

  delay(50);

  if (mySeq.size() != seq.size()) {
    Serial << "Error: Something broke.. users sequence size does not match program sequence size!" << endl;
    return false;
  }

  // check the answer
  bool isCorrect = true;

  for (int i = 0; i < seq.size(); i++) {
    Serial << "Comparing two values for i = " << i << " | mySeq.at(i) = " << mySeq.get(i) << " | seq.at(i) = " << seq.get(i) << endl;
    if (mySeq.get(i) != seq.get(i)) {
      Serial << "INCORRECT VALUE FOUND!!!!!!!!!!!!!!!!" << endl;
      isCorrect = false;
    }
  }

  Serial << "Returning isCorrect: " << isCorrect << endl;
  return isCorrect;
}

void clearSequences() {
  seq.clear();
  mySeq.clear();
}

void loop() {
  Serial << "Preparing to clear sequence" << endl;
  clearSequences();

  // display the level number
  drawText(1, SSD1306_WHITE, 0, 0, "Level: " + String(level));
  Serial << "Preparing to generate sequence" << endl;
  generateSequence();

  Serial << "Preparing to activate sequence" << endl;
  activateSequence();

  // get input
  Serial << "Preparing to get input" << endl;
  
  if (getInputAndCheck()) {
    level++;
    Serial << "Incrementing level: " << level << endl;
  } else {
    level = 1;
    Serial << "Game over!!!, we are back to level 1 " << endl;
  }

  delay(1000);

  Serial << "End of the main loop" << endl;
}