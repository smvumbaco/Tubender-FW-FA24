#include <Arduino.h>
#include "TubenderStateMachine.hpp"
#include <HardwareSerial.h>


TubenderStateMachine stateMachine;

void setup() {

    Serial.begin(9600);

    stateMachine.initializePins();

}

void loop() {
    stateMachine.handleState();
}