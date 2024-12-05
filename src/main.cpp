#include "TubenderStateMachine.hpp"
#include <tft.hpp>
#include <Arduino.h>

#include <Adafruit_RA8875.h>


// Pins on main board
Adafruit_MCP23X17 expander1;
Adafruit_MCP23X17 expander2;

// Motor setup
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



// need sensor instances

//  NEED TO INSTANTIATE PID OBJECT


#define RA8875_CS  5   // Chip select pin
#define RA8875_RST 12   // Reset pin
Adafruit_RA8875 adafruitTFT(RA8875_CS, RA8875_RST);
TFT myTFT(adafruitTFT, &expander2);

volatile int interruptCounter;
volatile int encoderCount;
// REncoder* encoder = nullptr;
// REncoder encoder = REncoder(expander1, DIAL_CHANNEL_A, DIAL_CHANNEL_B, RotaryEncoder::LatchMode::FOUR3);

ShiftRegister74HC595<1> shiftRegister(SEVEN_SEG_SER, SEVEN_SEG_SRCLK, SEVEN_SEG_RCLK);
SevenSegmentDisplay sevenSegment(shiftRegister, expander2, SEVEN_SEG_SER, SEVEN_SEG_RCLK, SEVEN_SEG_SRCLK);
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

volatile bool sensorStateChanged = false;
volatile unsigned long lastInterruptTime = 0;


// State machine
TubenderStateMachine stateMachine(expander1, expander2);


// Rotary Encoder ISRs
void IRAM_ATTR handleDialChannelAInterrupt() {
    dialChannelAInterrupt = true;
}

void IRAM_ATTR handleDialChannelBInterrupt() {
    dialChannelBInterrupt = true;
}


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

    if (sensorStateChanged) {
        sensorStateChanged = false;
        if (stateMachine.checkSensors()) {
            Serial.println("All sensors are valid. Proceeding...");
        } else {
            Serial.println("Safety check failed. Stopping operation.");
            // Stop all motors for safety
            advancing.stopMotor();
            tubeRotation.stopMotor();
            dieClamp.stopMotor();
            chuckClamp.stopMotor();
            // ADD STOP METHOD FOR BENDING ACTUATOR
        }
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