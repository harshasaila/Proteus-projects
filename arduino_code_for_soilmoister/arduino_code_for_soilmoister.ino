#include <Wire.h>
#include <LiquidCrystal.h>

// Initialize the LCD with the pin numbers
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// Define the pin for the soil moisture sensor and motor
const int soilMoisturePin = A0;
const int motorPin = 7;

// Define the moisture thresholds
const int threshold1 = 50;
const int threshold2 = 70;
const int threshold3 = 90;

// Time between LCD updates (in milliseconds)
const unsigned long updateInterval = 1000;
unsigned long lastUpdate = 0;

void setup() {
  // Set up the LCD columns and rows
  lcd.begin(16, 2);
  
  // Set the motor pin as output
  pinMode(motorPin, OUTPUT);
  
  // Print a startup message
  lcd.print("Soil Moisture:");
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Read the soil moisture sensor value
  int sensorValue = analogRead(soilMoisturePin);
  
  // Map the sensor value to a percentage (0-100%)
  int moisturePercent = map(sensorValue, 0, 1023, 0, 100);
  
  // Determine the motor run time based on moisture level
  int motorTime = 0;
  if (moisturePercent > threshold3) {
    motorTime = 8000; // 8 seconds
  } else if (moisturePercent > threshold2) {
    motorTime = 5000; // 5 seconds
  } else if (moisturePercent > threshold1) {
    motorTime = 3000; // 3 seconds
  } else {
    motorTime = 0;
  }

  // Control the motor
  if (motorTime > 0) {
    digitalWrite(motorPin, HIGH);
    delay(motorTime);
    digitalWrite(motorPin, LOW);
  }
  
  // Update the LCD only if the specified interval has passed
  if (currentMillis - lastUpdate >= updateInterval) {
    lastUpdate = currentMillis;
    
    // Clear the LCD and display the moisture percentage and motor time
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Moisture: ");
    lcd.print(moisturePercent);
    lcd.print("%");
    
    lcd.setCursor(0, 1);
    lcd.print("Motor: ");
    if (motorTime > 0) {
      lcd.print(motorTime / 1000);
      lcd.print("s");
    } else {
      lcd.print("OFF");
    }
  }
}
