const int LED_GREEN = 2;
const int LRD = A0;

void setup() {
  Serial.begin(9600);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LRD, INPUT);
}

void loop() {
  const int LRD_THRESHOLD = 750;
  const int lrdReading = analogRead(LRD);

  if (lrdReading < LRD_THRESHOLD) {
    digitalWrite(LED_GREEN, HIGH);
  } else {
    digitalWrite(LED_GREEN, LOW);
  }
}