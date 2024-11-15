#include "TubenderStateMachine.hpp"
#include "Mux.hpp"

// TubenderStateMachine::TubenderStateMachine(insert expander parameter here) {

// }
TubenderStateMachine::TubenderStateMachine() {

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
    gpioExpander1.pinMode(BUTTON_PLEX_1, INPUT);
    gpioExpander1.pinMode(BUTTON_SEL_1A, OUTPUT);
    gpioExpander1.pinMode(BUTTON_SEL_1B, OUTPUT);
    gpioExpander1.pinMode(BUTTON_SEL_1C, OUTPUT);
    gpioExpander1.pinMode(BUTTON_PLEX_2, INPUT);
    gpioExpander2.begin_I2C(0x1);
}

void TubenderStateMachine::start() {
    
}

void TubenderStateMachine::bend() {
    
}

void TubenderStateMachine::finish() {
    
}

// Any other methods we wanna include