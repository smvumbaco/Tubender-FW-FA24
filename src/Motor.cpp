#include "Motor.hpp"
#include <Arduino.h>
using namespace std;


Motor::Motor(int sPin, int dPin, int delay, String id)
: stepPin(sPin), dirPin(dPin), stepDelay(delay), motorID(id){
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  digitalWrite(stepPin, LOW);
  digitalWrite(dirPin, LOW);
}

void Motor::setDirection(bool clockwise) {
  digitalWrite(dirPin, clockwise ? HIGH : LOW);
}

void Motor::moveSteps(int steps) {
  for (int i=0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);


    // Can add code for stop conditions or feedback
  }
}

// Move forward by a given number of steps
void Motor::moveForward(int steps) {
    setDirection(true);  // Clockwise
    moveSteps(steps);
}

// Move backward by a given number of steps
void Motor::moveBackward(int steps) {
    setDirection(false);  // Counterclockwise
    moveSteps(steps);
}

// Stop motor - can be more complex with sensors if required
void Motor::stopMotor() {
    digitalWrite(stepPin, LOW);
}

// Get motor ID (useful for debugging or display)
String Motor::getMotorID() {
    return motorID;
}
