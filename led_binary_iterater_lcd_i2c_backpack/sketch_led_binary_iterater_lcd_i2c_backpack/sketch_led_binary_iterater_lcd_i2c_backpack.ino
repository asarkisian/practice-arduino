const int LEDS[] = {13, 12, 11, 10, 9, 8, 7, 6};
const int POT = A0;

void setup() {
  // engage serial communication
  Serial.begin(9600);
  
  // set pins
  for (int i = 0; i < 8; i++) {
    pinMode(LEDS[i], OUTPUT);
  }

  pinMode(POT, INPUT);
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

    int potReading = analogRead(POT);
    int ledBrightness = map(potReading, 0, 1023, 0, 255);

    // determine which bits are on/off
    for (int i = 0; i < 8; i++) {
      if ((geometricSequence[i] + tally) <= x) {
        tally += geometricSequence[i];
        myByte[i] = 1;
      }
      myByteStr += myByte[i]; // to display to LCD
    }

    // turn LED on based on whether bit is on or off
    for (int i = 0; i < 8; i++) {
      if (myByte[i] == 1) {
        analogWrite(LEDS[i], ledBrightness);
      }
    }

    delay(500);

    // turn all LEDS off
    for (int i = 0; i < 8; i++) {
      digitalWrite(LEDS[i], LOW);
    }
  }
}