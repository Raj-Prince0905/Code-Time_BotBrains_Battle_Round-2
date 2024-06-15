#include <Servo.h>

const int soilMoisturePin = A0;
const int potentiometerPin = A1;
const int pumpPin = 9;
const int buzzerPin = 8;
const int ledPin = 7;
const int buttonPin = 2;

Servo servoMotor;
int soilMoistureThreshold = 300; // Default threshold
bool systemActive = true;

void setup() {
  pinMode(soilMoisturePin, INPUT);
  pinMode(potentiometerPin, INPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Button pin configured with internal pull-up resistor
  servoMotor.attach(10);
  
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);
  servoMotor.write(0); // Initialize servo to closed position
}

void loop() {
  if (systemActive) {
    int soilMoisture = analogRead(soilMoisturePin);
    int thresholdPotValue = analogRead(potentiometerPin);
    soilMoistureThreshold = map(thresholdPotValue, 0, 1023, 0, 1023); // Map potentiometer value to adjust threshold
    
    if (soilMoisture < soilMoistureThreshold) {
      digitalWrite(pumpPin, HIGH);
      digitalWrite(ledPin, HIGH);
      digitalWrite(buzzerPin, HIGH);
      servoMotor.write(90); // Open the servo valve
      delay(5000); // Watering duration
      digitalWrite(pumpPin, LOW);
      digitalWrite(ledPin, LOW);
      digitalWrite(buzzerPin, LOW);
      servoMotor.write(0); // Close the servo valve
    }
  }
  
  // Check if button is pressed to activate/deactivate system
  if (digitalRead(buttonPin) == LOW) {
    systemActive = !systemActive; // Toggle system active state
    delay(200); // Button debounce delay
  }
  
  // Enter sleep mode when system is inactive
  if (!systemActive) {
    digitalWrite(pumpPin, LOW);
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
    servoMotor.write(0); // Ensure servo is closed
    // Enter low power sleep mode
    sleepMode();
  }
  
  delay(1000); // Check soil moisture every second
}

void sleepMode() {
  // Code to enter sleep mode
  // Implement as per specific Arduino model's sleep mode instructions
}
