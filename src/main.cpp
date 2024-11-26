#include "TubenderStateMachine.hpp"
#include "PID.hpp"
#include <Arduino.h>

Adafruit_MCP23X17 gpioExpander1;
PID BendingPID(gpioExpander1);

void setup() {

    Serial.begin(115200);
    gpioExpander1.pinMode(BENDING_L_ENA, OUTPUT);
    gpioExpander1.pinMode(BENDING_R_ENA, OUTPUT);
    pinMode(BENDING_LPWM, OUTPUT);
    pinMode(BENDING_RPWM, OUTPUT);

}

void loop() {
    Serial.println("moving");
    BendingPID.prepareNewBend(45);
    BendingPID.run();
    delay(5000);
    BendingPID.prepareHome();
    BendingPID.run();
    delay(5000);

}