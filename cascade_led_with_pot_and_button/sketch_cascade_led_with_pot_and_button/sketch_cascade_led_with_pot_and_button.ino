#define LED_RED 13
#define LED_GREEN 12
#define LED_BLUE 11
#define LED_WHITE 10
#define LED_YELLOW 9
#define POT_LED_CONTROL A5
#define BUTTON_1 8

void setup() {
  // engage serial communication
  Serial.begin(9600);

  // set pins (output)
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_WHITE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);

  // set pins (input)
  pinMode(POT_LED_CONTROL, INPUT);
  pinMode(BUTTON_1, INPUT);
}

void loop() {
  static bool buttonToggle = false;

  const int pot_reading = analogRead(POT_LED_CONTROL);
  const int button = digitalRead(BUTTON_1);

  if (button == HIGH) {
    buttonToggle = !buttonToggle;
    delay(500);
  }

  if (buttonToggle) {
    if (pot_reading >= 1020.00) {
      digitalWrite(LED_RED, HIGH);
    } else {
      digitalWrite(LED_RED, LOW);
    }
    
    if (pot_reading >= 818.40) {
      digitalWrite(LED_GREEN, HIGH);
    } else {
      digitalWrite(LED_GREEN, LOW);
    }

    if (pot_reading >= 613.80) {
      digitalWrite(LED_BLUE, HIGH);
    } else {
      digitalWrite(LED_BLUE, LOW);
    }

    if (pot_reading >= 409.20) {
      digitalWrite(LED_WHITE, HIGH);
    } else {
      digitalWrite(LED_WHITE, LOW);
    }

    if (pot_reading >= 204.60) {
      digitalWrite(LED_YELLOW, HIGH);
    } else {
      digitalWrite(LED_YELLOW, LOW);
    }
  } else {
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_BLUE, LOW);
      digitalWrite(LED_WHITE, LOW);
      digitalWrite(LED_YELLOW, LOW);
  }

  delay(100);
}