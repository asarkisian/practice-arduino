// LEDs
#define LED_WHITE 13
#define LED_RED 12
#define LED_BLUE 11
#define LED_YELLOW 10
#define LED_GREEN 9

// potentiometers
#define POT_WHITE A4
#define POT_RED A3
#define POT_BLUE A2
#define POT_YELLOW A1
#define POT_GREEN A0

void setup() {
  // engage serial communication
  Serial.begin(9600);
  Serial.println("Setting up project");

  // set LED pins (output)
  pinMode(LED_WHITE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  // set potentiometer pins (input)
  pinMode(POT_WHITE, INPUT);
  pinMode(POT_RED, INPUT);
  pinMode(POT_BLUE, INPUT);
  pinMode(POT_YELLOW, INPUT);
  pinMode(POT_GREEN, INPUT);
}

void loop() {
  const short potWhite = analogRead(POT_WHITE);
  const short potRed = analogRead(POT_RED);
  const short potBlue = analogRead(POT_BLUE);
  const short potYellow = analogRead(POT_YELLOW);
  const short potGreen = analogRead(POT_GREEN);

  const bool toggleButton =  false;

  if (potWhite >= (1023/2)) {
    digitalWrite(LED_WHITE, HIGH);
    Serial.println("TURNING WHITE ON");
  } else {
    digitalWrite(LED_WHITE, LOW);
    Serial.println("TURNING WHITE OFF");
  }

  if (potRed>= (1023/2)) {
    digitalWrite(LED_RED, HIGH);
  } else {
    digitalWrite(LED_RED, LOW);
  }

  if (potBlue >= (1023/2)) {
    digitalWrite(LED_BLUE, HIGH);
  } else {
    digitalWrite(LED_BLUE, LOW);
  }

  if (potYellow >= (1023/2)) {
    digitalWrite(LED_YELLOW, HIGH);
  } else {
    digitalWrite(LED_YELLOW, LOW);
  }  

  if (potGreen >= (1023/2)) {
    digitalWrite(LED_GREEN, HIGH);
  } else {
    digitalWrite(LED_GREEN, LOW);
  }

  delay(100);
}