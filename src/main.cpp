#include "TubenderStateMachine.hpp"
#include <tft.hpp>
#include <Arduino.h>
#include "REncoder.hpp"
#include "RotaryEncoder.h"
#include "Adafruit_MCP23X17.h"
#include "Motor.hpp"
#include "Mux.hpp"
#include "sevenSeg.hpp"
// #include <Adafruit_RA8875.h>

#define RA8875_CS  5   // Chip select pin
#define RA8875_RST 4   // Reset pin
// Pins on main board
#define CHUCK_CLAMP_DIR 26
#define DISPLAY_CS 29
#define DIE_CLAMP_PUL 14
#define DIE_CLAMP_DIR 16
#define BENDING_RPWM 13
#define BENDING_LPWM 23
#define ADVANCING_PUL 27
#define ADVANCING_DIR 28
#define DISPLAY_SCK 30
#define DISPLAY_MISO 31
#define SEVEN_SEG_SER 10
#define SEVEN_SEG_SRCLK 11
#define SEVEN_SEG_RCLK 12
#define ROTATION_DIR 8
#define ROTATION_PUL 9




// Adafruit_RA8875 adafruitTFT = Adafruit_RA8875(RA8875_CS, RA8875_RST);
// TFT myTFT = TFT(adafruitTFT);

//Initialize variables for a timer
Adafruit_MCP23X17 expander1 = Adafruit_MCP23X17();
Adafruit_MCP23X17 expander2 = Adafruit_MCP23X17();

Pin advancingPul = {ADVANCING_PUL, false};
Pin advancingDir = {ADVANCING_DIR, false};
Pin advancingEnable = {ADVANCING_ENA, true};
Motor advancing = Motor(&expander2, advancingPul, advancingDir, advancingEnable, 100, "advancing");

Pin rotationPul = {ROTATION_PUL, false};
Pin rotationDir = {ROTATION_DIR, false};
Pin rotationEnable = {ROTATION_ENA, true};
Motor tubeRotation = Motor(&expander2, rotationPul, rotationDir, rotationEnable, 100, "chuck rotation");

Pin dieClampPul = {DIE_CLAMP_PUL, false};
Pin dieClampDir = {DIE_CLAMP_DIR, false};
Pin dieClampEnable = {DIE_CLAMP_ENA, true};
Motor dieClamp = Motor(&expander2, dieClampPul, dieClampDir, dieClampEnable, 500, "die clamp");

Pin chuckClampPul = {CHUCK_CLAMP_PUL, true};
Pin chuckClampDir = {CHUCK_CLAMP_DIR, false};
Pin chuckClampEnable = {CHUCK_CLAMP_ENA, true};
Motor chuckClamp = Motor(&expander2, chuckClampPul, chuckClampDir, chuckClampEnable, 100, "chuck clamp");

volatile int interruptCounter;
// REncoder* encoder = nullptr;
REncoder encoder = REncoder(expander1, DIAL_CHANNEL_A, DIAL_CHANNEL_B, RotaryEncoder::LatchMode::FOUR3);
// TODO: IDK IF THESE ARE THE RIGHT PINS
ShiftRegister74HC595<1> shiftRegister = ShiftRegister74HC595<1>(SEVEN_SEG_SER,SEVEN_SEG_SRCLK, SEVEN_SEG_RCLK);
SevenSegmentDisplay sevenSegment = SevenSegmentDisplay(shiftRegister, SEVEN_SEG_SER, SEVEN_SEG_RCLK, SEVEN_SEG_SRCLK);
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
    Serial.println("starting setup");
    expander1.begin_I2C(0x0);
    delayMicroseconds(10);
    expander2.begin_I2C(0x1);
    delayMicroseconds(10);
    expander1.pinMode(BUTTON_PLEX_1, INPUT);
    expander1.pinMode(BUTTON_SEL_1A, OUTPUT);
    expander1.pinMode(BUTTON_SEL_1B, OUTPUT);
    expander1.pinMode(BUTTON_SEL_1C, OUTPUT);
    expander1.pinMode(BUTTON_PLEX_2, INPUT);
    expander1.pinMode(BUTTON_SEL_2A, OUTPUT);
    expander1.pinMode(BUTTON_SEL_2B, OUTPUT);
    expander1.pinMode(BUTTON_SEL_2C, OUTPUT);
    expander1.pinMode(DIE_LIMIT_1, INPUT);
    expander1.pinMode(DIE_LIMIT_2, INPUT);
    expander2.pinMode(INDUCTIVE_PROX_1, INPUT);
    expander2.pinMode(INDUCTIVE_PROX_2, INPUT);
    expander2.pinMode(DISPLAY_WAIT, OUTPUT);
    expander2.pinMode(DISPLAY_INT, OUTPUT);
    expander2.pinMode(SEVEN_SEG_A0, OUTPUT);
    expander2.pinMode(SEVEN_SEG_A1, OUTPUT);
    expander2.pinMode(SEVEN_SEG_GB, OUTPUT);
    expander2.pinMode(SEVEN_SEG_OEB, OUTPUT);
    expander2.pinMode(BENDING_L_ENA, OUTPUT);
    expander2.pinMode(BENDING_R_ENA, OUTPUT);
    Serial.println("Done with setup");
    // myTFT.initialize();

}

void loop() {
    Serial.println("advancing moving 20 steps");
    advancing.moveForward(20);

    delay(1000);
    Serial.println("chuck clamp moving 20 steps");
    chuckClamp.moveForward(20);

    delay(1000);
    Serial.println("die clamp moving 20 steps");
    dieClamp.moveForward(20);

    delay(1000);
    Serial.println("rotation moving 20 steps"); 
    tubeRotation.moveForward(20);

    // myTFT.displayStartMenu();

    //Seven Segment Test Code:

    //  Testing 3 Digit write
    //sevenSegment.display3Digits(000)
    //delay(1000);
    //sevenSegment.display3Digits(888)
    //delay(1000);

    // Testing 1 digit write
    //sevenSegment.displayCharacter(0, 1);
    //delay(500);
    //sevenSegment.displayCharacter(1, 2);
    //delay(500);
    //sevenSegment.displayCharacter(1, 3);


    
}