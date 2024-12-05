#include "TubenderStateMachine.hpp"
#include <tft.hpp>
#include <Arduino.h>

#include <Adafruit_RA8875.h>


// Pins on main board
Adafruit_MCP23X17 expander1;
Adafruit_MCP23X17 expander2;





Pin advancingPul = {ADVANCING_PUL, false};
Pin advancingDir = {ADVANCING_DIR, false};
Pin advancingEnable = {ADVANCING_ENA, true};
Motor advancing(&expander2, advancingPul, advancingDir, advancingEnable, 100, "advancing");

Pin rotationPul = {ROTATION_PUL, false};
Pin rotationDir = {ROTATION_DIR, false};
Pin rotationEnable = {ROTATION_ENA, true};
Motor tubeRotation(&expander2, rotationPul, rotationDir, rotationEnable, 100, "chuck rotation");

Pin dieClampPul = {DIE_CLAMP_PUL, false};
Pin dieClampDir = {DIE_CLAMP_DIR, false};
Pin dieClampEnable = {DIE_CLAMP_ENA, true};
Motor dieClamp(&expander2, dieClampPul, dieClampDir, dieClampEnable, 500, "die clamp");

Pin chuckClampPul = {CHUCK_CLAMP_PUL, true};
Pin chuckClampDir = {CHUCK_CLAMP_DIR, false};
Pin chuckClampEnable = {CHUCK_CLAMP_ENA, true};
Motor chuckClamp(&expander2, chuckClampPul, chuckClampDir, chuckClampEnable, 100, "chuck clamp");

#define RA8875_CS  5   // Chip select pin
#define RA8875_RST 12   // Reset pin
Adafruit_RA8875 adafruitTFT(RA8875_CS, RA8875_RST);
TFT myTFT(adafruitTFT, &expander2);

volatile int interruptCounter;
volatile int encoderCount;
// REncoder* encoder = nullptr;
REncoder encoder(expander1, DIAL_DATA, DIAL_CLK);

Adafruit_7segment matrix = Adafruit_7segment();
SevenSegmentDisplay sevenSegment(matrix);

hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
 

// void IRAM_ATTR onTimer() {
//     portENTER_CRITICAL_ISR(&timerMux);
//     encoder.tick();
//     interruptCounter++;
//     portEXIT_CRITICAL_ISR(&timerMux);
// }

volatile bool dialChannelBInterrupt = false;

volatile bool sensorStateChanged = false;
volatile unsigned long lastInterruptTime = 0;


// State machine
TubenderStateMachine stateMachine(expander1, expander2, myTFT, encoder);





// Sensor ISRs
void IRAM_ATTR ISR_bbsensor1() {
    sensorStateChanged = true;
}

void IRAM_ATTR ISR_bbsensor2() {
    sensorStateChanged = true;
}

void IRAM_ATTR ISR_proximity1() {
    sensorStateChanged = true;
}

void IRAM_ATTR ISR_proximity2() {
    sensorStateChanged = true;
}


void IRAM_ATTR ISR_advancingLimit1() {
    static unsigned long lastInterruptTime = 0; // Static variable to persist between calls
    unsigned long currentTime = micros(); // Use micros instead of millis

    if (currentTime - lastInterruptTime > 50000) { // 50ms debounce in microseconds
        lastInterruptTime = currentTime;
        sensorStateChanged = true;
        // Do minimal work here
    }
}

void IRAM_ATTR ISR_advancingLimit2() {
    static unsigned long lastInterruptTime = 0; // Static variable to persist between calls
    unsigned long currentTime = micros(); // Use micros instead of millis

    if (currentTime - lastInterruptTime > 50000) { // 50ms debounce in microseconds
        lastInterruptTime = currentTime;
        sensorStateChanged = true;
        // Do minimal work here
    }
}

void IRAM_ATTR ISR_bendLimit1() {
    static unsigned long lastInterruptTime = 0; // Static variable to persist between calls
    unsigned long currentTime = micros(); // Use micros instead of millis

    if (currentTime - lastInterruptTime > 50000) { // 50ms debounce in microseconds
        lastInterruptTime = currentTime;
        sensorStateChanged = true;
        // Do minimal work here
    }
}

void IRAM_ATTR ISR_bendLimit2() {
    static unsigned long lastInterruptTime = 0; // Static variable to persist between calls
    unsigned long currentTime = micros(); // Use micros instead of millis

    if (currentTime - lastInterruptTime > 50000) { // 50ms debounce in microseconds
        lastInterruptTime = currentTime;
        sensorStateChanged = true;
        // Do minimal work here
    }
}

void setup() {
    Serial.begin(115200);
    while (!Serial)
        ;

    expander1.begin_I2C(0x20);
    delayMicroseconds(1000);
    expander2.begin_I2C(0x21);
    delayMicroseconds(1000);

    Serial.println("Expander 2 Done");
    Serial.println("Done with setup");

}

void loop() {
    //Integrating Rotary Encoder and 7-Seg



}