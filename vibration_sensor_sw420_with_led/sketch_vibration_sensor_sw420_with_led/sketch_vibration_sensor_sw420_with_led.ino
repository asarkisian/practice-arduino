const int VIBSEN_PIN = 3; // PWM
const int LED_PIN = 13;

void setup() {
  Serial.begin(9600);
  pinMode(VIBSEN_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  long vibSenRead = pulseIn(VIBSEN_PIN, HIGH);
  delay(50);
  Serial.println(vibSenRead);

  if (vibSenRead > 50) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}