// LEDs
#define LED_WHITE 6 // PWM
#define LED_RED 5 // PWM
#define LED_BLUE 3 // PWM

// potentiometers
#define POT_WHITE A2
#define POT_RED A1
#define POT_BLUE A0

void setup() {
  // engage serial communication
  Serial.begin(9600);
  Serial.println("Setting up project");

  // set LED pins (output)
  pinMode(LED_WHITE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  // set potentiometer pins (input)
  pinMode(POT_WHITE, INPUT);
  pinMode(POT_RED, INPUT);
  pinMode(POT_BLUE, INPUT);
}

void loop() {
  const short potWhite = analogRead(POT_WHITE);
  const short potRed = analogRead(POT_RED);
  const short potBlue = analogRead(POT_BLUE);

  const short whiteBrightness = map(potWhite, 0, 1023, 0, 255);
  const short redBrightness = map(potRed, 0, 1023, 0, 255);
  const short blueBrightness = map(potBlue, 0, 1023, 0, 255);

  // provide pwm variable brightness
  analogWrite(LED_WHITE, whiteBrightness);
  analogWrite(LED_RED, redBrightness);
  analogWrite(LED_BLUE, blueBrightness);

  delay(100);
}