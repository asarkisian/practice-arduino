#define LED_RED 12
#define BUTTON_LED 2

void setup() {
  Serial.begin(9600);

  pinMode(LED_RED, OUTPUT);
  pinMode(BUTTON_LED, INPUT);
}

void loop() {
  const int ledTurnOff = 5000;
  static bool buttonToggle = false;
  static long previousTime = 0;

  if ((millis() - previousTime) >= ledTurnOff) {
    digitalWrite(LED_RED, LOW);
    buttonToggle = false;
    previousTime = millis();
  }

  if (digitalRead(BUTTON_LED) == HIGH) {
    buttonToggle = !buttonToggle;
    delay(100);
  }

  if (buttonToggle) {
    digitalWrite(LED_RED, HIGH);
  } else {
    digitalWrite(LED_RED, LOW);
  }

  delay(100);
}