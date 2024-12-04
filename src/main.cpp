#include "TubenderStateMachine.hpp"
#include "PID.hpp"
#include <Arduino.h>

Adafruit_MCP23X17 gpioExpander2;
PID BendingPID(gpioExpander2);

void setup() {

    Serial.begin(115200);
    gpioExpander2.begin_I2C(0x21);
    pinMode(BENDING_LIN_POT, INPUT);
    pinMode(BENDING_LPWM, OUTPUT);
    pinMode(BENDING_RPWM, OUTPUT);
    gpioExpander2.pinMode(BENDING_L_ENA, OUTPUT);
    gpioExpander2.pinMode(BENDING_R_ENA, OUTPUT);

}

void loop() {
    
    BendingPID.prepareNewBend(45);
    BendingPID.run();
    delay(5000);
    BendingPID.prepareHome();
    BendingPID.run();
    delay(5000);

}