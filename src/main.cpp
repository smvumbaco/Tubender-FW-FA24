#include "TubenderStateMachine.hpp"
#include "Config.hpp"

TubenderStateMachine stateMachine;

void setup() {

    Serial.begin(9600);
    stateMachine.initializePins();

}

void loop() {
    stateMachine.handleState();
}