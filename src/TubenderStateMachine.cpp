#include "TubenderStateMachine.hpp"
#include "Mux.hpp"
#include "Config.hpp"
#include "Sensors.hpp"




TubenderStateMachine::TubenderStateMachine() 
: mux1(gpioExpander1, BUTTON_PLEX_1), mux2(gpioExpander1, BUTTON_PLEX_2),
  breakBeamBehindChuck(21, "BreakBeam", "Behind Chuck"),
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

    
    breakBeamBehindChuck.initialize();
    breakBeamBeforeDie.initialize();
    limitSwitchStart.initialize(true);  // Enable pull-up for limit switches
    limitSwitchEnd.initialize(true);   
    proximityOnChuck.initialize();
    Serial.println("Sensors initialized.");
    // pinMode(LINEAR_POTENTIOMETER_PIN, INPUT);
}

void TubenderStateMachine::start() {
    //after getting initial tube length
    double initialLength = 240.0;
    Config tubeConfig(initialLength);
    tubeConfig.addNewBend("offset", 0, 22.5, 10, 15);
    Serial.print(tubeConfig.tubeLength);
    
    
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
