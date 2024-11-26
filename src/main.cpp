#include "TubenderStateMachine.hpp"
#include "PID.hpp"
#include <Arduino.h>

Adafruit_MCP23X17 gpioExpander1;
PID BendingPID(gpioExpander1);

void setup() {

    Serial.begin(115200);

}

void loop() {
    
    BendingPID.prepareNewBend(45);
    BendingPID.run();
    delay(5000);
    BendingPID.prepareHome();
    BendingPID.run();
    delay(5000);

}