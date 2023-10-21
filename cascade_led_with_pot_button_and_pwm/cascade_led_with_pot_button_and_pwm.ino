const short LEDS[] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4};
const short POTS[] = {A0, A1};
const short PIEZO_BUZZER = 3;
const short BUTTON = 2; 

void setup() {
  // engage serial communication
  Serial.begin(9600);

  // set LED pins
  for (int i = 0; i < 10; i++) {
    pinMode(LEDS[i], OUTPUT);
  }

  // set POT pins
  for (int i = 0; i < 2; i++) {
    pinMode(POTS[i], INPUT);
  }

  // set button pin
  pinMode(BUTTON, INPUT);

  // no pin to set for piezo buzzer
}

void loop() {
  static bool buttonToggle = true;

  const int potRead1 = analogRead(POTS[0]);
  const int potRead2 = analogRead(POTS[1]);
  const int buttonRead = digitalRead(BUTTON);
  const int ledBrightness = map(potRead2, 0, 1023, 0, 255);

  if (buttonRead == HIGH) {
    buttonToggle = !buttonToggle;
    delay(500);
  }

  if (buttonToggle) {
    if (potRead1 > 102.3) {
      analogWrite(LEDS[9], ledBrightness);
    } else {
      analogWrite(LEDS[9], 0);
    }

    if (potRead1 > 204.6) {
      analogWrite(LEDS[8], ledBrightness);
    } else {
      analogWrite(LEDS[8], 0);
    }

    if (potRead1 > 306.9) {
      analogWrite(LEDS[7], ledBrightness);
    } else {
      analogWrite(LEDS[7], 0);
    }

    if (potRead1 > 409.2) {
      analogWrite(LEDS[6], ledBrightness);
    } else {
      analogWrite(LEDS[6], 0);
    }

    if (potRead1 > 511.5) {
      analogWrite(LEDS[5], ledBrightness);
    } else {
      analogWrite(LEDS[5], 0);
    }

    if (potRead1 > 613.8) {
      analogWrite(LEDS[4], ledBrightness);
    } else {
      analogWrite(LEDS[4], 0);
    }

    if (potRead1 > 716.1) {
      analogWrite(LEDS[3], ledBrightness);
    } else {
      analogWrite(LEDS[3], 0);
    }

    if (potRead1 > 818.4) {
      analogWrite(LEDS[2], ledBrightness);
    } else {
      analogWrite(LEDS[2], 0);
    }

    if (potRead1 > 920.69) {
      analogWrite(LEDS[1], ledBrightness);
    } else {
      analogWrite(LEDS[1], 0);
    }
  
    if (potRead1 > 1020) {
      analogWrite(LEDS[0], ledBrightness);
      for (short i = 0; i < 5000; i++) {
        tone(PIEZO_BUZZER, i, 500);
      }
    } else {
      analogWrite(LEDS[0], 0);
    }
  } else {
    for (short i = 0; i < 10; i++) {
      analogWrite(LEDS[i], 0);
    }
  }

  delay(100);
}