#include <ESP32Servo.h>

Servo myServo;
const int servoPin = 18;

// Define rotation speeds (adjust if needed)
const int STOP = 90;    // 90 is neutral (stops rotation)
const int FORWARD = 0;  // Full speed in one direction
const int REVERSE = 180; // Full speed in the opposite direction

void setup() {
    myServo.attach(servoPin);
    myServo.write(STOP);  // Ensure it starts in the stopped position
    delay(5000);          // Pause at "0 degrees"
}

void loop() {
    // Move from 0° to 60°
    myServo.write(FORWARD);  
    delay(400);           // Adjust this delay to move approximately 60°
    myServo.write(STOP);  
    delay(5000);          // Pause for 5 seconds

    // Move from 60° to 120°
    myServo.write(FORWARD);  
    delay(400);
    myServo.write(STOP);  
    delay(5000);

    // Move from 120° to 180°
    myServo.write(FORWARD);  
    delay(400);
    myServo.write(STOP);  
    delay(5000);

    // Move back to "0 degrees" (opposite direction)
    myServo.write(REVERSE);
    delay(1200); // Approximate full 180° rotation back
    myServo.write(STOP);
    delay(5000);
}
