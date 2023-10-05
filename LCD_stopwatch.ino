#include <LiquidCrystal.h>

// lcd pin connections
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

unsigned long startTime = 0;
unsigned long elapsedTime = 0;
boolean timerRunning = false;
boolean stopped = false;
boolean buttonPressed = false;

const int startButtonPin = 2; // Pin for the "Press Start" button
const int stopButtonPin = 3;  // Pin for the "Stop" button
const int resetButtonPin = 4; // Pin for the "Reset" button

void start_button();
void stop_button();
void reset_button();
void calc_time();

void setup() {
  lcd.begin(16, 2);
  lcd.print("Press to start");
  lcd.setCursor(0,1);
  lcd.print("   Stopwatch");

  // pullup to prevent noise in circuits
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(stopButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);
}

void loop() {
  start_button();
  stop_button();
  reset_button();
  calc_time();
}

void start_button(){
  // Check if the "Press Start" button is pressed to start or resume the timer
  if (digitalRead(startButtonPin) == LOW && !timerRunning && !stopped && !buttonPressed) {
    startTime = millis() - elapsedTime;
    timerRunning = true;
    buttonPressed = true;
  }
}
void stop_button(){
  // Check if the "Stop" button is pressed to pause or resume the timer
  if (digitalRead(stopButtonPin) == LOW) {
    if (!buttonPressed) {
      buttonPressed = true;
      if (timerRunning) {
        elapsedTime = millis() - startTime;
        timerRunning = false;
        stopped = true;
        lcd.setCursor(0, 1);
        lcd.print("      STOP");
        delay(1000); // Pause for 1 second
      } else if (!timerRunning && stopped) {
        startTime = millis() - elapsedTime;
        timerRunning = true;
        stopped = false;
        lcd.setCursor(0, 1);
        lcd.print("             "); // Clear the "STOP" message to continue
      }
    }
  } else {
    buttonPressed = false;
  }
}
void reset_button(){
  // Check if the "Reset" button is pressed to clear everything and start over
  if (digitalRead(resetButtonPin) == LOW) {
    startTime = 0;
    elapsedTime = 0;
    timerRunning = false;
    stopped = false;
    lcd.clear();
    lcd.print("Press to start");
  }
}
void calc_time(){
  if (timerRunning) {
    elapsedTime = millis() - startTime;

    // Display the elapsed time per second on the LCD
    if (elapsedTime % 1000 == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Elapsed Time:");
      lcd.setCursor(0, 1);
      lcd.print(elapsedTime / 1000);
      lcd.print("s");
    }
  }
}
