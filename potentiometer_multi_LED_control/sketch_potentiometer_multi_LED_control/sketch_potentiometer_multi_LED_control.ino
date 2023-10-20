const short LED_YELLOW = 2;
const short LED_GREEN = 3;
const short LED_BLUE = 4;
const short LED_RED = 5;

const short POT_1 = A0;
const short POT_2 = A1;

void setup() {
  Serial.begin(9600);

  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  pinMode(POT_1, INPUT);
  pinMode(POT_2, INPUT);
}

void measurePot(const int pot, const int led1, const int led2) {
  const int potSensor = analogRead(pot);

  if (potSensor < (1023/2)) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
  } else if (potSensor >= 500 && potSensor <= 600) {
    digitalWrite(led2, LOW);
    digitalWrite(led1, LOW);
  } else {
    digitalWrite(led2, HIGH);
    digitalWrite(led1, LOW);
  }
}

void loop() {
  measurePot(POT_1, LED_YELLOW, LED_GREEN);
  measurePot(POT_2, LED_RED, LED_BLUE);

  delay(500);
}
