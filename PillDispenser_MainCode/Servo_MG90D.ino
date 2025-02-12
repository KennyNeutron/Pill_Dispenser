#include <ESP32Servo.h>

Servo myServo;
const int servoPin = 18;

// Define rotation speeds (adjust if needed)
const int STOP = 90;      // 90 is neutral (stops rotation)
const int FORWARD = 0;    // Full speed in one direction
const int REVERSE = 180;  // Full speed in the opposite direction

int NeutralPulseWidth = 1500;
int SpeedOffset = 100;
int ServoSteps = 18;

void Servo_setup() {
  myServo.attach(servoPin);

  myServo.write(STOP);
  delay(1000);  // Pause at "0 degrees"
}

void Servo_Move60() {
  myServo.write(FORWARD);
  delay(73);
  myServo.write(STOP);
  delay(ServoSteps);
  Serial.println("Servo moved 60 degrees");
  CurrentCompartment++;

  if (CurrentCompartment >= 6) {
    CurrentCompartment = 0;
  }
  Serial.print("Current Compartment: ");
  Serial.println(CurrentCompartment);
}