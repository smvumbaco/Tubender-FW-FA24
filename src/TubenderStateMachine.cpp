#include "TubenderStateMachine.hpp"


// TubenderStateMachine::TubenderStateMachine(insert expander parameter here) {

// }
TubenderStateMachine::TubenderStateMachine() : mux1(gpioExpander1, BUTTON_PLEX_1), mux2(gpioExpander1, BUTTON_PLEX_2) {
    
}

TubenderStateMachine::~TubenderStateMachine() {

}

void TubenderStateMachine::handleState() {

    switch (_currentState)
    {
    case START:
        //start();
        break;

    case BENDING:
        //bend();
        break;

    case FINISHED:
        //finish();
        break;
    
    default:
        break;
    }
    // delay(10);

}

void TubenderStateMachine::initializePins() {

    // pinMode(LINEAR_POTENTIOMETER_PIN, INPUT);
    // setup pins for gpioExpander1
    gpioExpander1.begin_I2C(0x0);
    delay(10);
    gpioExpander1.pinMode(BUTTON_PLEX_1, INPUT);
    gpioExpander1.pinMode(BUTTON_SEL_1A, OUTPUT);
    gpioExpander1.pinMode(BUTTON_SEL_1B, OUTPUT);
    gpioExpander1.pinMode(BUTTON_SEL_1C, OUTPUT);
    gpioExpander1.pinMode(BUTTON_PLEX_2, INPUT);
    gpioExpander1.pinMode(BUTTON_SEL_2A, OUTPUT);
    gpioExpander1.pinMode(BUTTON_SEL_2B, OUTPUT);
    gpioExpander1.pinMode(BUTTON_SEL_2C, OUTPUT);

    gpioExpander2.begin_I2C(0x1);
    delay(10);
    
}

void TubenderStateMachine::reset() {

}

void TubenderStateMachine::start() {
    
    //after getting initial tube length
    double initialLength = 240.0;
    Config tubeConfig(initialLength);
    tubeConfig.addNewBend("offset", 0, 22.5, 10, 15);
    Serial.print(tubeConfig.tubeLength);
}

void TubenderStateMachine::bend() {
    
}

void TubenderStateMachine::finish() {
    
}

// Any other methods we wanna include