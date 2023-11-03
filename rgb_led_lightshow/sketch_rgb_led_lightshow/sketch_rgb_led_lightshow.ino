const int LED_RGB_RED = 9;
const int LED_RGB_GREEN = 10;
const int LED_RGB_BLUE = 11;

void setup() {
  Serial.begin(9600);

  pinMode(LED_RGB_RED, OUTPUT);
  pinMode(LED_RGB_GREEN, OUTPUT);
  pinMode(LED_RGB_BLUE, OUTPUT);
}

void setRGBColor(int redAmount, int greenAmount, int blueAmount) {
  if (redAmount != -1) {
    analogWrite(LED_RGB_RED, redAmount);
  }

  if (greenAmount != -1) {
    analogWrite(LED_RGB_GREEN, greenAmount);
  }

  if (blueAmount != -1) {
    analogWrite(LED_RGB_BLUE, blueAmount);
  }
}

void loop() {
  const int DELAY_PERIOD = 10;
  
  // set blue (blue left)
  for (int i = 0; i < 256; i++) {
    setRGBColor(-1, -1, i);
    delay(DELAY_PERIOD);
  }

  // set red (blue + red left)
  for (int i = 0; i < 256; i++) {
    setRGBColor(i, -1, -1);
  }

  // unset blue (red left)
  for (int i = 255; i > -1; i--) {
    setRGBColor(-1, -1, i);
    delay(DELAY_PERIOD);
  }

  // set green (red + green left)
  for (int i = 0; i < 256; i++) {
    setRGBColor(-1, i, -1);
    delay(DELAY_PERIOD);
  }

  // unset red (green left)
  for (int i = 255; i > -1; i--) {
    setRGBColor(i, -1, -1);
    delay(DELAY_PERIOD);
  }

  // set blue (green + blue left)
  for (int i = 0; i < 256; i++) {
    setRGBColor(-1, -1, i);
    delay(DELAY_PERIOD);
  }

  // set red (green + blue + red left)
  for (int i = 0; i < 256; i++) {
    setRGBColor(i, -1, -1);
    delay(DELAY_PERIOD);
  }

  // unset green (blue + red)
  for (int i = 255; i > -1; i--) {
    setRGBColor(-1, i, -1);
    delay(DELAY_PERIOD);
  }

  // unset blue (red left)
  for (int i = 255; i > -1; i--) {
    setRGBColor(-1, -1, i);
    delay(DELAY_PERIOD);
  }
}