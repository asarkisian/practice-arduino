#define NOTE_E5 659
#define NOTE_G5 784
#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_F5 698
#define NOTE_A5 880
#define NOTE_B5 988

const int segmentA = 2;  // Connect segment A to digital pin 2
const int segmentB = 3;  // Connect segment B to digital pin 3
const int segmentC = 4;  // Connect segment C to digital pin 4
const int segmentD = 5;  // Connect segment D to digital pin 5
const int segmentE = 6;  // Connect segment E to digital pin 6
const int segmentF = 7;  // Connect segment F to digital pin 7
const int segmentG = 8;  // Connect segment G to digital pin 8

const int digit1 = 10;   // Connect common anode/cathode of the 1st digit to digital pin 10
const int buzzerPin = 13;
const int redLedPin = 11;
const int greenLedPin = 9;
const int blueLedPin = 12;
const int delayTime = 1000; // Delay time in milliseconds
const int countdownBuzzerDuration = 100; 

void setup() {
  pinMode(segmentA, OUTPUT);
  pinMode(segmentB, OUTPUT);
  pinMode(segmentC, OUTPUT);
  pinMode(segmentD, OUTPUT);
  pinMode(segmentE, OUTPUT);
  pinMode(segmentF, OUTPUT);
  pinMode(segmentG, OUTPUT);

  pinMode(digit1, OUTPUT);

  pinMode(buzzerPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

  // Turn off all segments, digits, and LEDs initially
  turnOffAllSegments();
  turnOffAllDigits();
  turnOffAllLEDs();
}

void loop() {
  // Countdown from 9 to 0
  for (int i = 9; i >= 0; --i) {
    displayNumber(i);
    playCountdownBuzzer();
    delay(delayTime);  // Display each number for 1 second
  }

  // Play the second song and synchronize lights
  playSong();
  synchronizeLights();
}

void displayNumber(int number) {
  // Define the common cathode values for each digit (0-9)
  byte digitValues[] = {
    B01111110, // 0
    B00110000, // 1
    B01101101, // 2
    B01111001, // 3
    B00110011, // 4
    B01011011, // 5
    B01011111, // 6
    B01110000, // 7
    B01111111, // 8
    B01110011  // 9
  };

  // Turn off all segments and digits
  turnOffAllSegments();
  turnOffAllDigits();

  // Display the number on the 1st digit
  digitalWrite(digit1, HIGH); // Turn on the common anode/cathode for the 1st digit
  displayDigit(digitValues[number]);
}

void displayDigit(byte segments) {
  digitalWrite(segmentA, bitRead(segments, 6));
  digitalWrite(segmentB, bitRead(segments, 5));
  digitalWrite(segmentC, bitRead(segments, 4));
  digitalWrite(segmentD, bitRead(segments, 3));
  digitalWrite(segmentE, bitRead(segments, 2));
  digitalWrite(segmentF, bitRead(segments, 1));
  digitalWrite(segmentG, bitRead(segments, 0));

}

void turnOffAllSegments() {
  digitalWrite(segmentA, LOW);
  digitalWrite(segmentB, LOW);
  digitalWrite(segmentC, LOW);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, LOW);
  digitalWrite(segmentG, LOW);

}

void turnOffAllDigits() {
  digitalWrite(digit1, LOW);
}

void playCountdownBuzzer() {
  digitalWrite(buzzerPin, HIGH);
  delay(countdownBuzzerDuration);
  digitalWrite(buzzerPin, LOW);
}

void playSong() {
  int jingleBellsMelody[] = {
    NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
    NOTE_E5, NOTE_E5, NOTE_E5, NOTE_G5,
    NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5,
    NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
    NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
    NOTE_D5, NOTE_D5, NOTE_E5, NOTE_D5,
    NOTE_G5
  };

  int jingleBellsDurations[] = {
    8, 8, 4, 8,
    8, 4, 8, 8,
    8, 8, 8, 8,
    4, 8, 8, 8,
    8, 8, 8, 8,
    4, 8, 8, 8,
    8
  };

  int* melodyToPlay = jingleBellsMelody;
  int* durationsToPlay = jingleBellsDurations;
  int songLength = sizeof(jingleBellsMelody) / sizeof(jingleBellsMelody[0]);

  for (int i = 0; i < songLength; i++) {
    int duration = 1000 / durationsToPlay[i];
    tone(buzzerPin, melodyToPlay[i], duration);

    digitalWrite(redLedPin, HIGH);
    delay(duration * 0.7);
    digitalWrite(redLedPin, LOW);

    digitalWrite(greenLedPin, HIGH);
    delay(duration * 0.7);
    digitalWrite(greenLedPin, LOW);

    digitalWrite(blueLedPin, HIGH);
    delay(duration * 0.7);
    digitalWrite(blueLedPin, LOW);

    delay(25);
  }

  // Pause for 2 seconds before playing the melody again
  delay(2000);
}

void synchronizeLights() {

}

void turnOffAllLEDs() {
  digitalWrite(redLedPin, LOW);
  digitalWrite(greenLedPin, LOW);
  digitalWrite(blueLedPin, LOW);
}
