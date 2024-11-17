#include "TubenderStateMachine.hpp"
#include "Config.hpp"

TubenderStateMachine stateMachine;

void setup() {

    Serial.begin(115200);
    stateMachine.initializePins();

}

void loop() {
    //stateMachine.handleState();
    stateMachine.start();
    delay(20000);
}