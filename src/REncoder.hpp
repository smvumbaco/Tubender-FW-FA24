#ifndef RENCODER_HPP
#define RENCODER_HPP
#include <Arduino.h>
#include <Adafruit_MCP23X17.h>
#include <RotaryEncoder.h>
#define DIAL_CLK 6
#define DIAL_DATA 7

class REncoder {
    private: 
        Adafruit_MCP23X17 &gpioExpander;
        int dataPin;
        int clkPin;
        volatile int8_t _oldState;
        int currentPosition;

    public:
        REncoder(Adafruit_MCP23X17 &expander, int dPin, int clockPin);
        virtual bool tick();
        virtual ~REncoder();
        void resetPosition();
        int getPosition();
};

#endif
