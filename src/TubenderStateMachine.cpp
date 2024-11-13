#include "TubenderStateMachine.hpp"

// TubenderStateMachine::TubenderStateMachine(insert expander parameter here) {

// }

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

}

void TubenderStateMachine::start() {

}

void TubenderStateMachine::bend() {
    
}

void TubenderStateMachine::finish() {
    
}

// Any other methods we wanna include
