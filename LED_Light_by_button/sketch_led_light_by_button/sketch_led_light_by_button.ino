#define LED1 13
#define BUTTON1 10

void setup() {
  pinMode(LED1, OUTPUT); // led 1

  pinMode(BUTTON1, INPUT_PULLUP); // joystick button 1
}

void checkButton() {
  if (digitalRead(BUTTON1) == 0) {
    digitalWrite(LED1, HIGH);
  } else {
    digitalWrite(LED1, LOW);
  }
}

void loop() {
  checkButton();

  delay(100);
}