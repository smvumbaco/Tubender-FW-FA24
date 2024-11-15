#ifndef TUBENDERSTATEMACHINE_HPP
#define TUBENDERSTATEMACHINE_HPP

// UI pins
#define LINEAR_POTENTIOMETER_PIN 35
#define BUTTON_PLEX_1 1
#define BUTTON_SEL_1A 2
#define BUTTON_SEL_1B 3
#define BUTTON_SEL_1C 4
#define BUTTON_PLEX_2 5
#define BUTTON_SEL_2A 6
#define BUTTON_SEL_2B 7
#define BUTTON_SEL_2C 8
//Include libraries
#include <Adafruit_MCP23X17.h>

// Constant Variables
const float gravity = 9.81; //this is just an example, delete this if/when we have a real variable

enum States {
    START,
    BENDING,
    FINISHED
};

class TubenderStateMachine {

    private:
        enum States _currentState;
        Adafruit_MCP23X17 gpioExpander1;
        Adafruit_MCP23X17 gpioExpander2;
        Mux mux1;
        Mux mux2;
    public:

        // Constructor
        TubenderStateMachine();
        //TubenderStateMachine(put expander parameter(s) in here);

        ~TubenderStateMachine();

        void handleState();
        
        void initializePins();

        void start();

        void bend();

        u_int scanButtons();

        void finish();

        // List all of the methods for the class here


};

#endif