#include "Motor.hpp"
#include <Arduino.h>
using namespace std;


Motor::Motor(int sPin, int dPin, int ePin, int delay, String id) 
: stepPin(sPin), dirPin(dPin), enaPin(ePin), stepDelay(delay), motorID(id){
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enaPin, OUTPUT);
  digitalWrite(stepPin, LOW);
  digitalWrite(dirPin, LOW);
  digitalWrite(enaPin, HIGH);   // disables the motor by default
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


void Motor::enableMotor() {
    digitalWrite(enaPin, LOW);
}

void Motor::disableMotor() {
    digitalWrite(enaPin, HIGH);
}

// Stop motor - can be more complex with sensors if required
void Motor::stopMotor() {
    digitalWrite(stepPin, LOW);
}

// Get motor ID (useful for debugging or display)
String Motor::getMotorID() {
    return motorID;
}
