// outputs
const short LED_RED = 3;
const short LED_GREEN = 4;
const short PIEZO_BUZZER = 5;

// inputs
const short POT_1 = A5;
const short BUTTON_1 = 2;

void setup() {
  Serial.begin(9600);

  // no setup required for the piezo buzzer
  // ...

  // controlled by the button
  pinMode(LED_RED, OUTPUT);
  pinMode(BUTTON_1, INPUT);

  // controlled by the potentiometer
  pinMode(LED_GREEN, OUTPUT);
  pinMode(POT_1, INPUT);
}

void loop() {
  const short potReading = analogRead(POT_1);
  const short buttonReading = digitalRead(BUTTON_1);
  static bool isRedLedOn = false;

  // control green LED using potentiometer
  if (potReading > (1023/2)) {
    digitalWrite(LED_GREEN, LOW);
  } else {
    digitalWrite(LED_GREEN, HIGH);
  }

  // control red LED using button
  if (buttonReading == HIGH) {
    isRedLedOn = !isRedLedOn;
  }

  // turn the red light on until turned off
  if (isRedLedOn) {
    digitalWrite(LED_RED, HIGH);
  } else {
    digitalWrite(LED_RED, LOW);
  }

  // ring the buzzer if both lights are turned on
  if (isRedLedOn && potReading <= (1023/2)) {
    for (int i = 100; i < 10000; i++) {
      tone(PIEZO_BUZZER, i, 100);
    }
  }

  delay(100);
}