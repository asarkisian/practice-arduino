const int PIN_BLUE = A9; // Blue LED
const int PIN_GREEN = A10; // Green LED
const int PIN_RED = A11; // Red LED

int red;
int green;
int blue;

void setColor(int R, int G, int B) {
  analogWrite(PIN_RED, R);
  analogWrite(PIN_GREEN, G);
  analogWrite(PIN_BLUE, B);
}

void setup() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
}

void loop() {
  setColor(255, 0, 0); // set LED to Red
  delay(500);
  setColor(0, 255, 0); // set LED to Green
  delay(500);
  setColor(0, 0, 255); // set LED to Blue
  delay(500);
}
