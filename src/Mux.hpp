#ifndef MUX_HPP
#define MUX_HPP
#include <Arduino.h>
#include <Adafruit_MCP23X17.h>


class Mux 
{
private:
    Adafruit_MCP23X17 &gpioExpander;
    int plexPin;
public:
    Mux(Adafruit_MCP23X17 &expander, int outputPin);
    ~Mux();
    u_int scan();
    bool readButton(u_int selector);
};

#endif