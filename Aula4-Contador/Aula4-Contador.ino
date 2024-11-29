#include <Arduino.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int resetPin = 9; 
const int pausePin = 8; 

uint8_t seconds = 0;
uint8_t lastSeconds = 0;
bool isPaused = false;

void setup() {
  setupTimer();
  lcd.begin(16, 2);
  pinMode(resetPin, INPUT_PULLUP); 
  pinMode(pausePin, INPUT_PULLUP); 
}

void setupTimer() {
  cli(); // disable interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  // Set prescaler to 256
  TCCR1B |= B00000100; // CS12

  // Enable interrupt
  TIMSK1 |= B00000010;

  // Count to 62500
  OCR1A = 62500;

  sei(); // enable interrupts
}

ISR(TIMER1_COMPA_vect) {
  if (!isPaused) {
    TCNT1 = 0; // reset timer
    if (++seconds > 59) seconds = 0;
  }
}

bool lastResetState = false;
bool lastPauseState = false;

void loop() {
  delay(10);

  if (seconds != lastSeconds) {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Timer:");
    lcd.setCursor(10, 0);
    lcd.print(seconds);
    lastSeconds = seconds;
  }
 
  bool currentResetState = digitalRead(resetPin); 
  bool currentPauseState = digitalRead(pausePin); 

  if (lastResetState && !currentResetState) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Timer reset");
    seconds = 0;
    TCNT1 = 0;
  }

  if (lastPauseState && !currentPauseState) {
    isPaused = !isPaused;
    if (isPaused) {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Timer paused");
    } else {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Timer resumed");
    }
  }

  lastResetState = currentResetState; // Update reset button state
  lastPauseState = currentPauseState; // Update pause button state
}