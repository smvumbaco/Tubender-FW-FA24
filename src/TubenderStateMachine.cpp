#include "TubenderStateMachine.hpp"



volatile bool buttonPress;


void IRAM_ATTR buttonPressedInterrupt() {
    buttonPress = true;
}

TubenderStateMachine::TubenderStateMachine(Adafruit_MCP23X17 &expander1, Adafruit_MCP23X17 &expander2, TFT &tft) : gpioExpander1(expander1), gpioExpander2(expander2), tft_display(tft), mux1(gpioExpander1, BUTTON_PLEX_1, BUTTON_SEL_1A, BUTTON_SEL_1B, BUTTON_SEL_1C), mux2(gpioExpander1, BUTTON_PLEX_2, BUTTON_SEL_2A, BUTTON_SEL_2B, BUTTON_SEL_2C) {
    
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
    
}

void TubenderStateMachine::reset() {

}

void TubenderStateMachine::start() {
    // after getting initial tube length
    // double initialLength = 240.0;
    // Config tubeConfig(initialLength);
    // tubeConfig.addNewBend("offset", 0, 22.5, 10, 15);
    // Serial.print(tubeConfig.tubeLength);
    tft_display.displayStartMenu();
    while (!mux1.readButton(0))
        ;
    
}

void TubenderStateMachine::bend() {
    
}

void TubenderStateMachine::finish() {
    
}

// Any other methods we wanna include