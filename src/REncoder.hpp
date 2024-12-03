#ifndef RENCODER_HPP
#define RENCODER_HPP
#include <Arduino.h>
#include <Adafruit_MCP23X17.h>
#include <RotaryEncoder.h>
#define DIAL_CHANNEL_A 6
#define DIAL_CHANNEL_B 7

class REncoder : public RotaryEncoder {
    private: 
        Adafruit_MCP23X17 &gpioExpander;
    public:
        REncoder(Adafruit_MCP23X17 &expander, int pin1, int pin2, LatchMode mode);
        virtual void IRAM_ATTR tick();
        virtual ~REncoder();
};

#endif
