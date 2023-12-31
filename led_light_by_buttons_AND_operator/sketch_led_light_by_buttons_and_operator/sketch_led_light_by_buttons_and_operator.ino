#define LED1 13
#define LED2 12
#define LED3 11
#define BUTTON1 10
#define BUTTON2 9

void setup() {
  pinMode(LED1, OUTPUT); // led 1
  pinMode(LED2, OUTPUT); // led 2
  pinMode(LED3, OUTPUT); // led 3

  pinMode(BUTTON1, INPUT_PULLUP); // joystick button 1
  pinMode(BUTTON2, INPUT_PULLUP); // joystick button 2

  Serial.begin(9600);
}

void checkButtons() {
  if (digitalRead(BUTTON1) == 0 && digitalRead(BUTTON2) == 0) {
    digitalWrite(LED2, HIGH);
    Serial.println("Both buttons pressed!");
  } else {
    digitalWrite(LED2, LOW);
  }
  
  if (digitalRead(BUTTON1) == 0 && digitalRead(BUTTON2) == 1) {
    digitalWrite(LED1, HIGH);
    Serial.println("Button1 pressed!");
  } else {
    digitalWrite(LED1, LOW);
  }

  if (digitalRead(BUTTON2) == 0 && digitalRead(BUTTON1) == 1) {
    digitalWrite(LED3, HIGH);
    Serial.println("Button2 pressed!");
  } else {
    digitalWrite(LED3, LOW);
  }
}

void loop() {
  checkButtons();

  delay(100);
}