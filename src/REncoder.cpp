#include "REncoder.hpp"

// Constructor sets up the interrupt pin
REncoder::REncoder(Adafruit_MCP23X17 &expander, int clkPin, int dataPin): gpioExpander(expander) {
    
    gpioExpander.pinMode(dataPin, INPUT_PULLUP);
    gpioExpander.pinMode(clkPin, INPUT_PULLUP);
    gpioExpander.setupInterruptPin(clkPin);
    currentPosition = 0;
}



// A method to get the turn movement of the rotary encoder. 
// Gets the states of the gpio at the time of the interrupt, then shifts by the data pin
// Datapin is HIGH at falling edge of clk if turned clockwise
// Datapin is LOW at falling edge of clk if turned counter
// -1 = counterclockwise, 0 = no change, 1 = clockwise
bool REncoder::tick() {
    u_int16_t pinStates = gpioExpander.getCapturedInterrupt();
    Serial.print("Pin states: ");
    Serial.println(pinStates);
    bool dataState = (pinStates>>dataPin) & 0x1;
    if (dataState) {
        currentPosition++;
    }
    else {
        currentPosition--;
    }
    

} // tick()

void REncoder::resetPosition() {
    currentPosition = 0;
}

int REncoder::getPosition() {
    return currentPosition;
}

REncoder::~REncoder() {

}