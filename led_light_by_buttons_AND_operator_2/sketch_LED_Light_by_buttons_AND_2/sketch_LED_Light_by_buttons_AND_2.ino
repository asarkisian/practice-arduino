#define LED_WHITE 12
#define LED_BLUE 11
#define LED_RED 10
#define BUTTON_1 2
#define BUTTON_2 3


void setup() {
  Serial.begin(9600);
  pinMode(LED_WHITE, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
}

void loop() {
  if (digitalRead(BUTTON_1) == HIGH && digitalRead(BUTTON_2) == HIGH) {
    digitalWrite(LED_RED, HIGH);
  } else {
    digitalWrite(LED_RED, LOW);
  }

  if (digitalRead(BUTTON_1) == HIGH && digitalRead(BUTTON_2) == LOW) {
    digitalWrite(LED_WHITE, HIGH);
  } else {
    digitalWrite(LED_WHITE, LOW);
  }

  if (digitalRead(BUTTON_2) == HIGH && digitalRead(BUTTON_1) == LOW) {
    digitalWrite(LED_BLUE, HIGH);
  } else {
    digitalWrite(LED_BLUE, LOW);
  }

  delay(100);
}