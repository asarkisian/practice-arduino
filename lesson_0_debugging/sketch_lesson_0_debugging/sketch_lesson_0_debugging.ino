void setup() {
  // initialize serial communication
  Serial.begin(9600);
  Serial.println("Hello, Arduino!");
}

void loop() {
  Serial.println("In the loop");
  delay(500);
}
