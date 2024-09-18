#include <LiquidCrystal.h> // Include LCD library

// Initialize the LCD with the pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int gasSensorPin = A0;  // MQ-2 gas sensor output connected to A0
int ledPin = 13;        // LED connected to D13
int threshold = 400;    // Gas detection threshold (adjust based on testing)

void setup() {
  pinMode(ledPin, OUTPUT);    // Set LED pin as output
  lcd.begin(16, 2);           // Initialize LCD (16 columns, 2 rows)
  lcd.print("Gas Detector");  // Initial display
  delay(2000);                // Wait 2 seconds
  lcd.clear();                // Clear LCD screen
}

void loop() {
  int gasLevel = analogRead(gasSensorPin);  // Read gas sensor value

  lcd.setCursor(0, 0);                      // Set cursor to first row
  lcd.print("Gas Level: ");                  // Print gas level label
  lcd.print(gasLevel);                      // Display gas level on LCD

  // Check if gas level exceeds the threshold
  if (gasLevel > threshold) {
    digitalWrite(ledPin, HIGH);  // Turn on the LED
    lcd.setCursor(0, 1);         // Move to second row
    lcd.print("Gas Detected!");  // Display alert on LCD
  } else {
    digitalWrite(ledPin, LOW);   // Turn off the LED
    lcd.setCursor(0, 1);         // Move to second row
    lcd.print("Safe         ");  // Display safe message
  }

  delay(500);  // Wait 500ms before next reading
}
