#include "REncoder.hpp"

REncoder::REncoder(Adafruit_MCP23X17 &expander, int pinA, int pinB, LatchMode mode):RotaryEncoder(pinA, pinB, mode), gpioExpander(expander) {
}



// A method to get the turn movement of the rotary encoder within a 2ms interval.
// -1 = counterclockwise, 0 = no change, 1 = clockwise
void IRAM_ATTR REncoder::tick() {
    int sig1 = (GPIO.in >> _pin1) & 0x01;
    int sig2 = (GPIO.in >> _pin2) & 0x01;
    int8_t thisState = sig1 | (sig2 << 1);

    if (_oldState != thisState) {
        _position += KNOBDIR[thisState | (_oldState << 2)];
        _oldState = thisState;

        if ((_mode == LatchMode::FOUR3 && thisState == LATCH3) ||
                (_mode == LatchMode::FOUR0 && thisState == LATCH0) ||
                (_mode == LatchMode::TWO03 && (thisState == LATCH0 || thisState == LATCH3))) {
                _positionExt = (_mode == LatchMode::TWO03) ? (_position >> 1) : (_position >> 2);
                // Mark an update event for the main loop
        }
    } // if
} // tick()

REncoder::~REncoder() {

}