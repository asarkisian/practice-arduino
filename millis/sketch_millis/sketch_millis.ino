const unsigned long eventInterval = 5000;
unsigned long previousTime = 0;

void setup() {
  Serial.begin(9600); 
}


void loop() {
  // updates frequently
  unsigned long currentTime = millis();

  // this is the event
  if (currentTime - previousTime >= eventInterval) {
    // event code
    Serial.println("Hello millis()!");

    // update the timing for the next time around
    previousTime = currentTime;
  }
}