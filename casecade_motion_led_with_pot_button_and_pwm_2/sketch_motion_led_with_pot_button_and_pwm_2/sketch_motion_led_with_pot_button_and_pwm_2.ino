const short LEDS[] = {11, 10, 9, 6, 5}; // PWM
const short BUTTON_LED_ON_OFF = 4;
const short POT_LED_INTENSITY = A0;

void setup() {
  Serial.begin(9600);

  for (short i = 0; i < 5; i++) {
    pinMode(LEDS[i], OUTPUT);
  }

  pinMode(BUTTON_LED_ON_OFF, INPUT);
  pinMode(POT_LED_INTENSITY, INPUT);
}

void turnOnLeds(char dir, long ledBrightness) {
  if (dir == 'f') {
    for (short i = 0; i < 5; i++) {
      analogWrite(LEDS[i], ledBrightness);
      delay(250);
    }
  } else {
    for (short i = 4; i > -1; i--) {
      analogWrite(LEDS[i], ledBrightness);
      delay(250);
    }
  }
}

void turnOffLeds(char dir) {
  if (dir == 'f') {
    for (short i = 0; i < 5; i++) {
      analogWrite(LEDS[i], 0);
      delay(150);
    }
  } else {
    for (short i = 4; i > -1; i--) {
      analogWrite(LEDS[i], 0);
      delay(150);
    }
  }
}

void loop() {
  const short buttonReading = digitalRead(BUTTON_LED_ON_OFF);
  const short potLedIntensityReading = analogRead(POT_LED_INTENSITY);
  const long ledBrightness = map(potLedIntensityReading, 0, 1023, 0, 255);
  static bool toggleButton = true;

  if (buttonReading == HIGH) {
    toggleButton = !toggleButton;
  }

  if (toggleButton) {
    turnOnLeds('f', ledBrightness);
    turnOffLeds('b');
    turnOnLeds('b', ledBrightness);
    turnOffLeds('f');
    toggleButton = !toggleButton;
  }

  delay(100);
}