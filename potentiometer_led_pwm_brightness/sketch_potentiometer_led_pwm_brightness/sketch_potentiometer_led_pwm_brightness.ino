#define POT_LED_BRIGHTNESS A0
//#define LED_RED 6 // (PWM)

void setup() {
  Serial.begin(9600);
  pinMode(POT_LED_BRIGHTNESS, INPUT);
  //pinMode(LED_RED, OUTPUT);
}

void loop() {
  const int potRead = analogRead(POT_LED_BRIGHTNESS);
  Serial.print("Red: ");
  Serial.println(potRead);
  //const long ledBrightness = map(potRead, 0, 1023, 0, 255); 

  //analogWrite(LED_RED, ledBrightness);

  delay(500);
}