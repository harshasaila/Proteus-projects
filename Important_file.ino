#include <SoftwareSerial.h>

// Define constants
const double ACaOffset = 2.5; // Offset voltage
const double Senaibl = 0.066; // Sensor sensitivity
const int analogPin = A3;     // Analog input pin

// Define relay pins
const int relay1Pin = 2;  // Digital pin 2 on Arduino
const int relay2Pin = 3;  // Digital pin 3 on Arduino
const int relay3Pin = 4;  // Digital pin 4 on Arduino

// Define specific current value
const double targetCurrent = 31.66;

// Create a flag to track the state of relay3Pin
bool relay3Low = false;

// Create software serial for the second virtual terminal (on pins 8 and 9)
SoftwareSerial virtualTerm2(8, 9); // RX, TX

void setup() {
  // Initialize serial communication for the primary virtual terminal
  Serial.begin(9600); // Set baud rate to 9600

  // Initialize software serial for the second virtual terminal
  virtualTerm2.begin(9600); // Set baud rate to 9600 for second virtual terminal

  // Initialize relay pins as outputs
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(relay3Pin, OUTPUT);
  
  // Set all relays HIGH initially
  digitalWrite(relay1Pin, HIGH);
  digitalWrite(relay2Pin, HIGH);
  digitalWrite(relay3Pin, HIGH);
}

void loop() {
  // Read the analog value from the sensor
  double ValeurLue = analogRead(analogPin);
  
  // Convert the analog value to voltage
  double tension = (ValeurLue * 5.0) / 1023.0;
  
  // Calculate the current
  double courant = (tension - ACaOffset) / Senaibl;
  
  // Print the current value to the primary virtual terminal
  Serial.print("Current: ");
  Serial.print(courant, 2); // Print with 2 decimal places
  Serial.println(" A");     // Display units
  
  // Check if the current value meets or exceeds the target value and relay3Pin has not been set to LOW yet
  if (courant >= targetCurrent && !relay3Low) {
    digitalWrite(relay3Pin, LOW); // Set relay3Pin LOW permanently
    relay3Low = true; // Set the flag to prevent further changes
    
    // Print the message to the second virtual terminal
    virtualTerm2.println("Hii Harsha you have a new MESSAGE.");
    delay(1000);
    virtualTerm2.println();
    virtualTerm2.println("Motor-3 has been shut down due to the heavy current load.");


  }
  
  // Delay for a short period
  delay(400);
}
