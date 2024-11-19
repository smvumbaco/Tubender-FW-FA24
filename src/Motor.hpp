#ifndef MOTOR_HPP
#define MOTOR_HPP
#include <Arduino.h>
#include <string>
#include <iostream>
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


class Motor {
  private:
    int stepPin;
    int dirPin;
    int enaPin; // maybe??
    int stepDelay;
    String motorID;
  

  public:

    Motor(int sPin, int dPin, int delay, String id);
      
    void setDirection(bool clockwise);

    void moveSteps(int steps);

    void moveForward(int steps);

    void moveBackward(int steps);

    void stopMotor();
    
    String getMotorID();

};

#endif

