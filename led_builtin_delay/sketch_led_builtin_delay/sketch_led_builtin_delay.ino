#define TIMER_ON 500
#define TIMER_OFF 500

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(TIMER_ON);
  digitalWrite(LED_BUILTIN, LOW);
  delay(TIMER_OFF);
}