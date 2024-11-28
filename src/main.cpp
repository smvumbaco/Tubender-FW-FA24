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
#define CHUCK_CLAMP_DIR 4
#define DISPLAY_CS 5
#define DIE_CLAMP_PUL 12
#define DIE_CLAMP_DIR 13
#define BENDING_RPWM 14
#define BENDING_LPWM 15
#define ADVANCING_PUL 16
#define ADVANCING_DIR 17
#define DISPLAY_SCK 18
#define DISPLAY_MISO 23
#define SEVEN_SEG_SER 25
#define SEVEN_SEG_SRCLK 26
#define SEVEN_SEG_RCLK 12
#define ROTATION_DIR 32
#define ROTATION_PUL 33




// Adafruit_RA8875 adafruitTFT = Adafruit_RA8875(RA8875_CS, RA8875_RST);
// TFT myTFT = TFT(adafruitTFT);

//Initialize variables for a timer
Adafruit_MCP23X17 expander1;
Adafruit_MCP23X17 expander2;

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
volatile int encoderCount;
// REncoder* encoder = nullptr;
// REncoder encoder = REncoder(expander1, DIAL_CHANNEL_A, DIAL_CHANNEL_B, RotaryEncoder::LatchMode::FOUR3);
// TODO: IDK IF THESE ARE THE RIGHT PINS
ShiftRegister74HC595<1> shiftRegister = ShiftRegister74HC595<1>(SEVEN_SEG_SER, SEVEN_SEG_SRCLK, SEVEN_SEG_RCLK);
SevenSegmentDisplay sevenSegment = SevenSegmentDisplay(shiftRegister, expander2, SEVEN_SEG_SER, SEVEN_SEG_RCLK, SEVEN_SEG_SRCLK);
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
 

// void IRAM_ATTR onTimer() {
//     portENTER_CRITICAL_ISR(&timerMux);
//     encoder.tick();
//     interruptCounter++;
//     portEXIT_CRITICAL_ISR(&timerMux);
// }

volatile bool dialChannelAInterrupt = false;
volatile bool dialChannelBInterrupt = false;

void IRAM_ATTR handleDialChannelAInterrupt() {
    dialChannelAInterrupt = true;
}

void IRAM_ATTR handleDialChannelBInterrupt() {
    dialChannelBInterrupt = true;
}


void setup() {
    Serial.begin(115200);
    while (!Serial)
        ;
    pinMode(SEVEN_SEG_SER, OUTPUT);
    pinMode(SEVEN_SEG_SRCLK, OUTPUT);
    pinMode(SEVEN_SEG_RCLK, OUTPUT);

    expander1.begin_I2C(0x20);
    delayMicroseconds(1000);
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

    //tests for rencoder
    expander1.setupInterrupts(false, false, LOW);
    expander1.pinMode(DIAL_CHANNEL_A, INPUT_PULLUP);
    expander1.setupInterruptPin(DIAL_CHANNEL_A, LOW);
    expander1.pinMode(DIAL_CHANNEL_B, INPUT_PULLUP);
    expander1.setupInterruptPin(DIAL_CHANNEL_B, LOW);
    Serial.println("Expander 1 Done");
    
    
    expander2.begin_I2C(0x21);
    delayMicroseconds(1000);
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
    
    Serial.println("Expander 2 Done");
    Serial.println("Done with setup");
    // myTFT.initialize();

}

void loop() {
    if (dialChannelAInterrupt) {
        Serial.println("channel a interrupt");
        dialChannelAInterrupt = false;
        u_int16_t state = expander1.getCapturedInterrupt();
        bool a_state = (state>>6) & 0x1;
        bool b_state = (state>>7) & 0x1;
        Serial.printf("dial channel a = %d, dial channel b = %d\n", a_state, b_state);
        expander1.clearInterrupts();
    }

    if (dialChannelBInterrupt) {
        Serial.println("channel b interrupt");
        dialChannelBInterrupt = false;
        u_int16_t state = expander1.getCapturedInterrupt();
        bool a_state = (state>>6) & 0x1;
        bool b_state = (state>>7) & 0x1;
        Serial.printf("dial channel a = %d, dial channel b = %d\n", a_state, b_state);
        expander1.clearInterrupts();
    }
    
    // Serial.println("advancing moving 20 steps");
    // advancing.moveForward(20);

    // delay(1000);
    // Serial.println("chuck clamp moving 20 steps");
    // chuckClamp.moveForward(20);

    // delay(1000);
    // Serial.println("die clamp moving 20 steps");
    // dieClamp.moveForward(20);

    // delay(1000);
    // Serial.println("rotation moving 20 steps"); 
    // tubeRotation.moveForward(20);

    // myTFT.displayStartMenu();
    // if (interruptCounter > 0) {
    //     Serial.println("interrupt detected");

    //     portENTER_CRITICAL_ISR(&timerMux);
    //     encoderCount = encoder.getPosition();
    //     interruptCounter--;
    //     portEXIT_CRITICAL_ISR(&timerMux);
    //     sevenSegment.displayCharacter(0, encoderCount);
    // }

    //Seven Segment Test Code:

    // //  Testing 3 Digit write
    // Serial.println("displaying 000");

    // sevenSegment.display3Digits(000);
    // delay(10000);
    // Serial.println("displaying 888");
    // sevenSegment.display3Digits(888);
    // delay(10000);

    // // Testing 1 digit write
    // sevenSegment.displayCharacter(0, 1);
    // delay(500);
    // sevenSegment.displayCharacter(1, 2);
    // delay(500);
    // sevenSegment.displayCharacter(1, 3);
    
}