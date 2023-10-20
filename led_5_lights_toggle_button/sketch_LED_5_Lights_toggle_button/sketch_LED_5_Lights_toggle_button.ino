
// declare and define LEDs (pins 2 through 6)
const short LEDS[] = {2, 3, 4, 5, 6};

// declare and define button switch (to toggle all the LEDs)
const short LED_SWITCHER 7

void setup() {
  // engage serial communication
  Serial.begin(9600);

  // set all LED pins
  for (short i = 0; i < 6; i++) {
    pinMode(LEDS[i], OUTPUT);
  }
  
  // set button
  pinMode(LED_SWITCHER, INPUT);
}

void loop() {
  // static to keep track of count throughout each iteration
  static short ledCount = -1;

  // toggle led's 1 through 5 on with each press of a button
  if (digitalRead(LED_SWITCHER) == HIGH) {
    if (ledCount >= -1 && ledCount <= 4) {
      ledCount++;

      // reset the count if reaching the 6th led (since it does not exist)
      if (ledCount == 5) {
        ledCount = -1; // off state (no LEDs are on here)
      }
    }

    // turn on the LED
    digitalWrite(LEDS[ledCount], HIGH);

    // iterate through all the LEDs and turn off the rest. There should only be 1 on at a given time
    for (short int i = 0; i < 5; i++) {

      if (i != ledCount) {
        // turn off the LED
        digitalWrite(LEDS[i], LOW);
      }
    }
  }

  delay(100);
}