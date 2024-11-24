#include "Motor.hpp"
#include <Arduino.h>
using namespace std;

//The order of pins should be step pin, dir pin, enable pin 
Motor::Motor(Adafruit_MCP23X17 *gpioExpander, Pin pulPin, Pin dPin, Pin enPin, int delay, String id)
: expander(gpioExpander), stepPin(pulPin), dirPin(dPin), enaPin(enPin), stepDelay(delay), motorID(id) {
  
  setPulPin(stepPin);
  setDirPin(dPin);
  setEnaPin(enPin);
}

//sets the pull pin. if onExpander is true, sets pulPin on the current Motor object's GPIO expander.
void Motor::setPulPin(Pin pulPin) {
  stepPin = pulPin;
  if (pulPin.onExpander == true) {
    expander->pinMode(stepPin.pin, OUTPUT);
    expander->digitalWrite(stepPin.pin, LOW);
  } else {
      pinMode(stepPin.pin, OUTPUT);
      digitalWrite(stepPin.pin, LOW);
  }
}

void Motor::setDirPin(Pin directionPin) {
  dirPin = directionPin;
  if (dirPin.onExpander == true) {
    expander->pinMode(dirPin.pin, OUTPUT);
    expander->digitalWrite(dirPin.pin, LOW);
  } else {
      pinMode(dirPin.pin, OUTPUT);
      digitalWrite(dirPin.pin, LOW);
  }
}

//set enaPin attribute of Motor and set it to its default
void Motor::setEnaPin(Pin enPin) {
  enaPin = enPin;
  if (enaPin.onExpander == true) {
    expander->pinMode(enaPin.pin, OUTPUT);
    expander->digitalWrite(enaPin.pin, HIGH);
  } else {
      pinMode(enaPin.pin, OUTPUT);
      digitalWrite(enaPin.pin, HIGH);
  }
}


void Motor::setDirection(bool clockwise) {
  if (dirPin.onExpander) {
    expander->digitalWrite(dirPin.pin, clockwise ? HIGH : LOW);
  } else {
    digitalWrite(dirPin.pin, clockwise ? HIGH : LOW);
  }
}

void Motor::moveSteps(int steps) {
  if (stepPin.onExpander) {
    for (int i=0; i < steps; i++) {
      expander->digitalWrite(stepPin.pin, HIGH);
      delayMicroseconds(stepDelay);
      expander->digitalWrite(stepPin.pin, LOW);
      delayMicroseconds(stepDelay);
    }
  } else {
    for (int i=0; i < steps; i++) {
    digitalWrite(stepPin.pin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin.pin, LOW);
    delayMicroseconds(stepDelay);

    // Can add code for stop conditions or feedback
    }
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
    if (enaPin.onExpander) {
      expander->digitalWrite(enaPin.pin, HIGH);
    } else {
      digitalWrite(enaPin.pin, HIGH);

    }
}

// Get motor ID (useful for debugging or display)
String Motor::getMotorID() {
    return motorID;
}
