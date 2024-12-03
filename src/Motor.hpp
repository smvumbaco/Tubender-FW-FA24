#ifndef MOTOR_HPP
#define MOTOR_HPP
#include <Arduino.h>
#include <string>
#include <iostream>
#include <Adafruit_MCP23X17.h>
using namespace std;

/**
* @file Motor.hpp
* @date November 2024
* @brief This file contains the Motor class construction,
* with functions to move/advance these motors, enable/disable them, and
* track their positions.
*/


/**
 * @class Motor
 * @brief This class represents the four stepper motors and their parameters.
 * @param pulPin: The PUL+ pin used to control the step pulse.
 * @param dirPin: The DIR+ pin used to control the direction of movement.
 * @param enaPin: The ENA+ pin used to enable/disable the motor functionality.
 */

struct Pin {
  int pin;
  bool onExpander;
};

class Motor {
  private:
    Adafruit_MCP23X17 *expander;
    bool onExpander[3];
    Pin stepPin;
    Pin dirPin;
    Pin enaPin; // maybe??
    int stepDelay;
    String motorID;
  

  public:

    Motor(Adafruit_MCP23X17 *gpioExpander, Pin pulPin, Pin dPin, Pin enPin, int delay, String id);

    void setPulPin(Pin pulPin);

    void setDirPin(Pin dirPin);

    void setEnaPin(Pin enaPin);

    void setDirection(bool clockwise);

    void moveSteps(int steps);

    void moveForward(int steps);

    void moveBackward(int steps);

    void stopMotor();
    
    String getMotorID();

};

#endif

