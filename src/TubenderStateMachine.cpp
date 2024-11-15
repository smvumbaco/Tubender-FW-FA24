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
    //write code in here
}

void TubenderStateMachine::bend() {
    //write code in here
}

void TubenderStateMachine::finish() {
    //write code in here
}

// Any other methods we wanna include
