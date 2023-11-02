// CONFIG
//const int SERIAL_BAUD_RATE = 9600;
//const int LDR_THRESHOLD = 750;
//const int DELAY_AMOUNT = 100;

// PINS
//const int LED_RED = 11; // PWM
//const int LED_BLUE = 10; // PWM
const int LED_RGB_RED = 3;
const int LED_RGB_GREEN = 5;
const int LED_RGB_BLUE = 6;
//const int BUTTON_LED_ON_OFF = 2;
//const int POT_LED = A0;
//const int LDR_LED = A1;

void setup() {
  // engage serial communication
  //Serial.begin(SERIAL_BAUD_RATE);

  // set pins (led)
  //pinMode(LED_RED, OUTPUT);
  //pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RGB_RED, OUTPUT);
  pinMode(LED_RGB_GREEN, OUTPUT);
  pinMode(LED_RGB_BLUE, OUTPUT);
  
  // set pins (button)
  //pinMode(BUTTON_LED_ON_OFF, INPUT);
  
  // set pins (potentiometer)
  //pinMode(POT_LED, INPUT);
  
  // set pins (photoresistor)
  //pinMode(LDR_LED, INPUT);
}

// control the rgb led
void setRGBColor(int redAmount, int greenAmount, int blueAmount) {
  analogWrite(LED_RGB_RED, redAmount);
  analogWrite(LED_RGB_GREEN, greenAmount);
  analogWrite(LED_RGB_BLUE, blueAmount);
}

void loop() {
  // analog read values
  //int potLedRead = analogRead(POT_LED);
  //int ldrRead = analogRead(LDR_LED);

  // digital read values
  //int buttonLedRead = digitalRead(BUTTON_LED_ON_OFF);

  // config
  //static int buttonLedToggle = false;
  //int ledBrightness = map(potLedRead, 0, 1023, 0, 255);

  // toggle button state
  //if (buttonLedRead == HIGH) {
  //  buttonLedToggle = !buttonLedToggle;
  //  delay(100);
  //}

  // determine if ldr exceeds threshold
  //if (ldrRead < LDR_THRESHOLD) {
  //    // even if ldr is below the threshold, the button also needs to be on
  //    if (buttonLedToggle) {
  //      // engage blue led
  //      analogWrite(LED_BLUE, ledBrightness);
  //    } else {
  //      // disengage blue led
  //      analogWrite(LED_BLUE, 0);
  //    }
  //} else {
  //  // disengage blue led
  //  analogWrite(LED_BLUE, 0);
  //}

  // determine button state
  //if (buttonLedToggle) {
    // engage red led
  //  analogWrite(LED_RED, ledBrightness);
  //} else {
    // disengage blue led
  //  analogWrite(LED_RED, 0);
  //}

  setRGBColor(255, 0, 0);
}