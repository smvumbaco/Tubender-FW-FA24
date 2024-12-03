#ifndef MUX_HPP
#define MUX_HPP
#include <Arduino.h>
#include <Adafruit_MCP23X17.h>


class Mux 
{
private:
    Adafruit_MCP23X17 &gpioExpander;
    int plexPin;
    int pinA;
    int pinB;
    int pinC;
public:
    Mux(Adafruit_MCP23X17 &expander, int outputPin, int pinA, int pinB, int pinC);
    ~Mux();
    u_int scan();
    bool readButton(u_int selector);
};

#endif