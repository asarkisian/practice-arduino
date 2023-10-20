// Note: Use a 100 ohm resistor on the cathod side
// Note: The piezo buzzer will conflict if you try to use analogWrite on PWM D11 and PWM D3
// Note: you cannot have two piezo buzzer playing at the same time
// Note: tone() works independently from delay() function
// Note:"31 hertz is the lowest frequency
// Note: must call noTone() if using multiple piezo buzzers on separate pins

const short PIEZO_PIN = 8

void setup() {
  // no setup required for piezo buzzer
}

void loop() {
  // Tone needs 2 arguments to work, but can take three
  // 1) Pin #
  // 2) Frequency - this is in hertz (cycles per second) which determines the pitch
  tone(PIEZO_PIN, 3000, 500);  

  delay(1500);
}