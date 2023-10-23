const short LEDS[] = {11, 10, 9, 6, 5}; // PWM
const short POTS[] = {A0, A1};
const short BUTTON_ON_OFF = 2;

void setup() {
  // engage serial communication
  Serial.begin(9600);

  // set LED pins
  for (short i = 0; i < 5; i++) {
    pinMode(LEDS[i], OUTPUT);
  }

  // set POT pins
  for (short i = 0; i < 2; i++) {
    pinMode(POTS[i], INPUT);
  }

  // set BUTTON_ON_OFF pin
  pinMode(BUTTON_ON_OFF, INPUT);
}

void controlLights(const int potLedCascade, const int ledBrightness) {
  if (potLedCascade >= (204.6*5)) {
    analogWrite(LEDS[0], ledBrightness);
  } else {
    analogWrite(LEDS[0], 0);
  }

  if (potLedCascade >= (204.6*4)) {
    analogWrite(LEDS[1], ledBrightness);
  } else {
    analogWrite(LEDS[1], 0);
  }

  if (potLedCascade >= (204.6*3)) {
    analogWrite(LEDS[2], ledBrightness);
  } else {
    analogWrite(LEDS[2], 0);
  }

  if (potLedCascade >= (204.6*2)) {
    analogWrite(LEDS[3], ledBrightness);
  } else {
    analogWrite(LEDS[3], 0);
  }

  if (potLedCascade >= (204.6)) {
    analogWrite(LEDS[4], ledBrightness);
  } else {
    analogWrite(LEDS[4], 0);
  }
}

void loop() {
  // setup timer
  const unsigned long currentTime = millis();
  static unsigned long previousTime = 0;
  const unsigned long checkLED = 100;

  // get readings
  const int potLedIntensityReading = analogRead(POTS[0]);
  const int potLedCascadeReading = analogRead(POTS[1]);
  const int buttonReading = digitalRead(BUTTON_ON_OFF);
  const long ledBrightness = map(potLedIntensityReading, 0, 1023, 0, 255);

  static bool buttonToggle = true;

  if (buttonReading == HIGH) {
    buttonToggle = !buttonToggle;
    delay(100);
  }

  // control timer events
  if ((currentTime - previousTime) >= checkLED) {
    if (buttonToggle) {
      controlLights(potLedCascadeReading, ledBrightness);
    } else {
      for (short i = 0; i < 5; i++) {
        analogWrite(LEDS[i], 0);
      }
    }

    previousTime = currentTime;
  }

  delay(100);
}