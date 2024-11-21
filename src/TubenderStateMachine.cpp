#include "TubenderStateMachine.hpp"
#include "Sensors.hpp"



TubenderStateMachine::TubenderStateMachine() 
: breakBeamBehindChuck(21, "BreakBeam", "Behind Chuck"),
  breakBeamBeforeDie(22, "BreakBeam", "Before Die Clamp"),
  limitSwitchStart(19, "LimitSwitch", "Start of Range"),
  limitSwitchEnd(18, "LimitSwitch", "End of Range"),
  proximityOnChuck(23, "Proximity", "Front of Chuck") {}


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
    breakBeamBehindChuck.initialize();
    breakBeamBeforeDie.initialize();
    limitSwitchStart.initialize(true);  // Enable pull-up for limit switches
    limitSwitchEnd.initialize(true);   
    proximityOnChuck.initialize();
    Serial.println("Sensors initialized.");
    // pinMode(LINEAR_POTENTIOMETER_PIN, INPUT);
}

void TubenderStateMachine::start() {
    Serial.println("Starting...");

    // Check the state of all relevant sensors for safety before proceeding
    bool breakBeamBehindTriggered = breakBeamBehindChuck.isTriggered();
    bool breakBeamBeforeTriggered = breakBeamBeforeDie.isTriggered();
    bool proximityTriggered = proximityOnChuck.isTriggered();
    bool limitSwitchStartTriggered = limitSwitchStart.isTriggered();
    bool limitSwitchEndTriggered = limitSwitchEnd.isTriggered();

    // Check all conditions
    if (breakBeamBehindTriggered && breakBeamBeforeTriggered && proximityTriggered && !limitSwitchStartTriggered && !limitSwitchEndTriggered) {
        // Enable the motor and proceed with the operation
        Serial.println("Safety conditions met. Starting motor...");
        // advanceMotor.enableMotor();  // If integrated with motor class
        _currentState = BENDING;  // Transition to bending state
    } else {
        // Safety not met, handle error or wait
        Serial.println("Safety conditions not met. Holding...");
    }
}

void TubenderStateMachine::bend() {
    Serial.println("Bending...");

    // Check if the tube is within the limits (check limit switches)
    if (!limitSwitchStart.isTriggered() && !limitSwitchEnd.isTriggered()) {
        // Tube is within limits, continue bending
        // Perform bending actions
    } else {
        // Tube is out of range, stop the process
        Serial.println("Tube is out of limits! Stopping...");
        _currentState = FINISHED;  // Transition to finished state
    }
}

void TubenderStateMachine::finish() {
    
}

// Any other methods we wanna include
