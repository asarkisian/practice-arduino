#include <LiquidCrystal.h>
#include <Keypad.h>

// LCD initialization
LiquidCrystal lcd(8, 9, 10, 11, 12, 13); 

// Pin definitions for LEDs and buzzer
const int redLEDPin = 6;
const int yellowLEDPin = 7;
const int buzzerPin = 18; 
 
// Keypad configuration
const byte ROW_NUM    = 4; 
const byte COLUMN_NUM = 4; 

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pin_rows[ROW_NUM] = {5, 4, 3, 2}; 
byte pin_column[COLUMN_NUM] = {14, 15, 16, 17}; 

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

// Variables to track scores and rounds
int redScore = 0;
int yellowScore = 0;
int roundsPlayed = 0;

// Setup function
void setup() {
  lcd.begin(16, 2); 
  pinMode(redLEDPin, OUTPUT);
  pinMode(yellowLEDPin, OUTPUT);
  
  lcd.print("Press'D'to roll");
}
// Main loop
void loop() {
  playGame(redLEDPin, "Red", redScore);
  playGame(yellowLEDPin, "Yellow", yellowScore);

  // Game ends after 6 rounds
  roundsPlayed++;
  if (roundsPlayed == 1) {
    lcd.clear();
    lcd.print("Game Over");
    delay(2000);


   // Display final scores on two lines
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Red: " + String(redScore) + " Point");
    lcd.setCursor(0, 1);
    lcd.print("Yellow: " + String(yellowScore) + " Point");
    delay(3000);


    // Determine the winner
    if (redScore > yellowScore) {
      lcd.clear();
      lcd.print("Red wins!");
      digitalWrite(redLEDPin, HIGH);
      playWinningSound();
    } else if (yellowScore > redScore) {
      lcd.clear();
      lcd.print("Yellow wins!");
      digitalWrite(yellowLEDPin, HIGH);
      playWinningSound();
    } else {
      lcd.clear();
      lcd.print("It's a tie!");
    }

    while (true) {
       // Infinite loop to stop the program after displaying the result
    }
  }
}
// Function to play the game for a player
void playGame(int ledPin, const char* playerName, int& playerScore) {
  lcd.clear();
  lcd.print(playerName);
  lcd.setCursor(0, 1);
  lcd.print("Press'D'to roll");
  
  digitalWrite(ledPin, HIGH);
  waitForKeypress('D');
  digitalWrite(ledPin, LOW);
  playDiceRollSound(); 
  int diceRoll = random(1, 7); 
  lcd.clear();
  lcd.print(playerName);
  lcd.setCursor(0, 1);
  lcd.print("You rolled: " + String(diceRoll));
  delay(2000);
  
  playerScore += diceRoll;
}
// Function to play the sound effect for a dice roll
void playDiceRollSound() {
  int note[] = {262, 330, 392, 523, 659, 784, 988}; // Musical notes for the sound effect

  for (int i = 0; i < 20; i++) { // Repeat the sound effect
    int randomNote = random(7);
    int duration = random(50, 150);
    tone(buzzerPin, note[randomNote], duration);
    delay(duration + 50);
  }
  noTone(buzzerPin);
}
// Function to play the winning sound effect
void playWinningSound() {
  int winningMelody[] = {500, 600, 700, 800, 900, 1000, 1100, 1200}; // Custom frequencies
  int winningNoteDuration = 200;

  for (int i = 0; i < 8; i++) {
    tone(buzzerPin, winningMelody[i], winningNoteDuration);
    delay(winningNoteDuration + 50);
  }
  noTone(buzzerPin);
}


// Function to wait for a specific keypress
void waitForKeypress(char targetKey) {
  char key = keypad.getKey();
  while (key != targetKey) {
    key = keypad.getKey();
    delay(50);
  }
}
