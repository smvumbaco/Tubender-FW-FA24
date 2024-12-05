#include "TubenderStateMachine.hpp"
#include <Arduino.h>


volatile bool buttonPress;

extern void IRAM_ATTR ISR_bbsensor1();
extern void IRAM_ATTR ISR_bbsensor2();
extern void IRAM_ATTR ISR_proximity1();
extern void IRAM_ATTR ISR_proximity2();
extern void IRAM_ATTR ISR_advancingLimit1();
extern void IRAM_ATTR ISR_advancingLimit2();
extern void IRAM_ATTR ISR_bendLimit1();
extern void IRAM_ATTR ISR_bendLimit2();

void IRAM_ATTR buttonPressedInterrupt() {
    buttonPress = true;
}

TubenderStateMachine::TubenderStateMachine(Adafruit_MCP23X17 &expander1, Adafruit_MCP23X17 &expander2) 
: gpioExpander1(expander1), gpioExpander2(expander2), 
  mux1(gpioExpander1, BUTTON_PLEX_1, BUTTON_SEL_1A, BUTTON_SEL_1B, BUTTON_SEL_1C),
  mux2(gpioExpander1, BUTTON_PLEX_2, BUTTON_SEL_2A, BUTTON_SEL_2B, BUTTON_SEL_2C) {
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
    pinMode(SEVEN_SEG_SER, OUTPUT);
    pinMode(SEVEN_SEG_SRCLK, OUTPUT);
    pinMode(SEVEN_SEG_RCLK, OUTPUT);

    delayMicroseconds(1000);
    gpioExpander1.pinMode(BUTTON_PLEX_1, INPUT);
    gpioExpander1.pinMode(BUTTON_SEL_1A, OUTPUT);
    gpioExpander1.pinMode(BUTTON_SEL_1B, OUTPUT);
    gpioExpander1.pinMode(BUTTON_SEL_1C, OUTPUT);
    gpioExpander1.pinMode(BUTTON_PLEX_2, INPUT);
    gpioExpander1.pinMode(BUTTON_SEL_2A, OUTPUT);
    gpioExpander1.pinMode(BUTTON_SEL_2B, OUTPUT);
    gpioExpander1.pinMode(BUTTON_SEL_2C, OUTPUT);
    gpioExpander1.pinMode(DIE_LIMIT_1, INPUT);
    gpioExpander1.pinMode(DIE_LIMIT_2, INPUT);

    //tests for rencoder
    gpioExpander1.setupInterrupts(false, false, LOW);
    gpioExpander1.pinMode(DIAL_CHANNEL_A, INPUT_PULLUP);
    gpioExpander1.setupInterruptPin(DIAL_CHANNEL_A, LOW);
    gpioExpander1.pinMode(DIAL_CHANNEL_B, INPUT_PULLUP);
    gpioExpander1.setupInterruptPin(DIAL_CHANNEL_B, LOW);
    Serial.println("Expander 1 Done");
    
    
    delayMicroseconds(1000);
    gpioExpander2.pinMode(INDUCTIVE_S_1, INPUT);
    gpioExpander2.pinMode(INDUCTIVE_S_2, INPUT);
    gpioExpander2.pinMode(DISPLAY_WAIT, OUTPUT);
    gpioExpander2.pinMode(DISPLAY_INT, OUTPUT);
    gpioExpander2.pinMode(SEVEN_SEG_A0, OUTPUT);
    gpioExpander2.pinMode(SEVEN_SEG_A1, OUTPUT);
    gpioExpander2.pinMode(SEVEN_SEG_GB, OUTPUT);
    gpioExpander2.pinMode(SEVEN_SEG_OEB, OUTPUT);
    gpioExpander2.pinMode(BENDING_L_ENA, OUTPUT);
    gpioExpander2.pinMode(BENDING_R_ENA, OUTPUT);

    gpioExpander2.begin_I2C(0x21);
    delay(10);

    // Sensor Setup
    pinMode(CHUCK_BEAM, INPUT_PULLUP);  // Break Beam Sensor before chuck
    pinMode(DIE_BEAM, INPUT_PULLUP);    // Break Beam Sensor before die
    pinMode(INDUCTIVE_S_1, INPUT_PULLUP); // Proximity Sensor 1
    pinMode(INDUCTIVE_S_2, INPUT_PULLUP); // Proximity Sensor 2
    pinMode(ADVANCE_LIMIT_1, INPUT_PULLUP); // Advancing Limit Switch 1
    pinMode(ADVANCE_LIMIT_2, INPUT_PULLUP); // Advancing Limit Switch 2
    pinMode(DIE_LIMIT_1, INPUT_PULLUP);     // Bending Limit Switch 1
    pinMode(DIE_LIMIT_2, INPUT_PULLUP);     // Bending Limit Switch 2


    // Attach interrupts for sensors
    attachInterrupt(digitalPinToInterrupt(CHUCK_BEAM), ISR_bbsensor1, FALLING);
    attachInterrupt(digitalPinToInterrupt(DIE_BEAM), ISR_bbsensor2, FALLING);
    attachInterrupt(digitalPinToInterrupt(INDUCTIVE_S_1), ISR_proximity1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(INDUCTIVE_S_2), ISR_proximity2, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ADVANCE_LIMIT_1), ISR_advancingLimit1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ADVANCE_LIMIT_2), ISR_advancingLimit2, CHANGE);
    attachInterrupt(digitalPinToInterrupt(DIE_LIMIT_1), ISR_bendLimit1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(DIE_LIMIT_2), ISR_bendLimit2, CHANGE);

    Serial.println("Pins initialized.");
    
}

bool TubenderStateMachine::checkSensors() {
    // Check each sensor's state
    bool breakBeam1 = digitalRead(CHUCK_BEAM) == LOW; // Tube present before chuck
    bool breakBeam2 = digitalRead(DIE_BEAM) == LOW;   // Tube present before die
    bool proximity1 = digitalRead(INDUCTIVE_S_1) == LOW; // Metal detected
    bool proximity2 = digitalRead(INDUCTIVE_S_2) == LOW; // Metal detected
    bool limitSwitch1 = digitalRead(ADVANCE_LIMIT_1) == HIGH; // Limit switch not pressed
    bool limitSwitch2 = digitalRead(ADVANCE_LIMIT_2) == HIGH; // Limit switch not pressed
    bool bendSwitch1 = digitalRead(DIE_LIMIT_1) == HIGH;      // Limit switch in correct state
    bool bendSwitch2 = digitalRead(DIE_LIMIT_2) == LOW;       // Limit switch in correct state

    // Combine all checks
    return (breakBeam1 && breakBeam2 && proximity1 && proximity2 &&
            limitSwitch1 && limitSwitch2 && bendSwitch1 && !bendSwitch2);
}


void TubenderStateMachine::reset() {

}

void TubenderStateMachine::start() {
    
    //after getting initial tube length
    // double initialLength = 240.0;
    // Config tubeConfig(initialLength);
    // tubeConfig.addNewBend("offset", 0, 22.5, 10, 15);
    // Serial.print(tubeConfig.tubeLength);
}

void TubenderStateMachine::bend() {
    
}

void TubenderStateMachine::finish() {
    
}

// Any other methods we wanna include