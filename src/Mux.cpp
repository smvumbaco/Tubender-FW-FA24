#include "Mux.hpp"

Mux::Mux(Adafruit_MCP23X17 &expander, int outputPin = 1) : gpioExpander(expander)
{
    int plexPin = outputPin;
}
Mux::~Mux()
{

}

u_int Mux::scan()
{
    u_int buttonOut;
    for (u_int sel = 0; sel <= 7; sel++) 
    {
        buttonOut += (readButton(sel) << sel);
    }   
    return buttonOut;
}

//TODO find out if these buttons are active lo
bool Mux::readButton(u_int selector)
{
    bool a = (selector >> 2) & 1;
    bool b = (selector >> 1) & 1;
    bool c = selector & 1;  
    gpioExpander.digitalWrite(plexPin + 1, a);
    gpioExpander.digitalWrite(plexPin + 2, b);
    gpioExpander.digitalWrite(plexPin + 3, c);
    bool buttonValue = gpioExpander.digitalRead(plexPin);
    return buttonValue;
}


