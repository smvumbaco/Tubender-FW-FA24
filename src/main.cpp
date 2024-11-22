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
Adafruit_MCP23X17 gpioExpander = Adafruit_MCP23X17();
//Initialize variables for a timer
volatile int interruptCounter;
int newPos;
// REncoder* encoder = nullptr;
RotaryEncoder encoder = RotaryEncoder(DIAL_CHANNEL_A, DIAL_CHANNEL_B, RotaryEncoder::LatchMode::FOUR3);
volatile int buttonPress;
hw_timer_t * timer = NULL;
// volatile SemaphoreHandle_t timerSemaphore;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer() {
    portENTER_CRITICAL_ISR(&timerMux);
    encoder.tick();
    buttonPress += digitalRead(34);
    interruptCounter++;
    portEXIT_CRITICAL_ISR(&timerMux);
}

void setup() {
    Serial.begin(115200);
    while (!Serial)
        ;
    // pinMode(DIAL_CHANNEL_A, INPUT_PULLUP);
    // pinMode(DIAL_CHANNEL_B, INPUT_PULLUP);
    // TFT myTFT(adafruitTFT);
    // myTFT.initialize();
    // myTFT.displayStartMenu();
    
    // register interrupt routine
    pinMode(DIAL_BUTTON, INPUT);
    attachInterrupt(digitalPinToInterrupt(DIAL_CHANNEL_A), onTimer, CHANGE);
    attachInterrupt(digitalPinToInterrupt(DIAL_CHANNEL_B), onTimer, CHANGE);
    //begin the timer with a frequency of 1 MHz (base/80), count up
    // timer = timerBegin(0, 80, true);
    //attach mem location of interrupt called onTimer when timer is true
    // timerAttachInterrupt(timer, &onTimer, true);
    //when the timer counter reaches 1 million, 
    //write an alarm for interrupt to detect
    // timerAlarmWrite(timer, 2000, true);
    //enable alarm for this timer
    // timerAlarmEnable(timer);
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