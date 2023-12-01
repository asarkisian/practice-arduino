const int TEMP_SENSOR_PIN = A0;
const int LED_GREEN_PIN = 13;

void setup() {
  Serial.begin(9600);

  // set pins (output)
  pinMode(LED_GREEN_PIN, OUTPUT);
  
  // set pins (input)
  pinMode(TEMP_SENSOR_PIN, INPUT);
}

void loop() {
  float voltage = analogRead(TEMP_SENSOR_PIN) * 0.004882813; // convert analog reading (0-1023)back to voltage from 0-5v

  float degreesC = (voltage - 0.5) * 100.0; // convert to celcius
  float degreesF = degreesC * (9.0 / 5.0) + 32.0; // convert to fahrenheit

  Serial.print("Temperature (C): ");
  Serial.println(degreesC);
  Serial.print("Temperature (F): ");
  Serial.println(degreesF);

  if (degreesF > 70.0) {
    digitalWrite(LED_GREEN_PIN, HIGH);
  } else {
    digitalWrite(LED_GREEN_PIN, LOW);
  }

  delay(1000);
}
