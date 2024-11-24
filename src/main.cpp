#include "TubenderStateMachine.hpp"
#include <tft.hpp>
#include <Arduino.h>
#include "REncoder.hpp"
#include "RotaryEncoder.h"
#include "Adafruit_MCP23X17.h"
// #include <Adafruit_RA8875.h>

#define RA8875_CS  5   // Chip select pin
#define RA8875_RST 4   // Reset pin

// Adafruit_RA8875 adafruitTFT = Adafruit_RA8875(RA8875_CS, RA8875_RST);
//Initialize variables for a timer
Adafruit_MCP23X17 expander1 = Adafruit_MCP23X17();
volatile int interruptCounter;
int newPos;
// REncoder* encoder = nullptr;
REncoder encoder = REncoder(expander1, DIAL_CHANNEL_A, DIAL_CHANNEL_B, RotaryEncoder::LatchMode::FOUR3);
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
 

void IRAM_ATTR onTimer() {
    portENTER_CRITICAL_ISR(&timerMux);
    encoder.tick();
    interruptCounter++;
    portEXIT_CRITICAL_ISR(&timerMux);
}




void setup() {
    Serial.begin(115200);
    while (!Serial)
        ;
    // TFT myTFT(adafruitTFT);
    // myTFT.initialize();
    // myTFT.displayStartMenu();
    
    // register interrupt routine
    pinMode(DIAL_BUTTON, INPUT);
    // attachInterrupt(digitalPinToInterrupt(DIAL_CHANNEL_A), onTimer, CHANGE);
    // attachInterrupt(digitalPinToInterrupt(DIAL_CHANNEL_B), onTimer, CHANGE);
    //begin the timer on number 0 with a frequency of 1 MHz (base/80), count up
    timer = timerBegin(0, 80, true);
    //attach mem location of interrupt called onTimer when timer is true
    timerAttachInterrupt(timer, &onTimer, true);
    //when the timer counter reaches 1 million, 
    //write an alarm for interrupt to detect
    timerAlarmWrite(timer, 2000, true);
    //enable alarm for this timer
    timerAlarmEnable(timer);
    Serial.println("Done with setup");

}

void loop() {
    if (interruptCounter > 0) {
        portENTER_CRITICAL(&timerMux);
        interruptCounter--;
        newPos = encoder.getPosition();
        portEXIT_CRITICAL(&timerMux);
    }

    int pos = 0;
    Serial.println(newPos);
    Serial.print("button: ");
    Serial.println(buttonPress);
    if (pos != newPos) {
        Serial.print(newPos);
        Serial.print(" dir:");
        Serial.println((int)(encoder.getDirection()));
        pos = newPos;
    } // if

}