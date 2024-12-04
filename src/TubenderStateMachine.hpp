#ifndef TUBENDERSTATEMACHINE_HPP
#define TUBENDERSTATEMACHINE_HPP

// UI pins
#define BENDING_LIN_POT 35
#define BENDING_RPWM 14
#define BENDING_LPWM 15

#define BUTTON_PLEX_1 1
#define BUTTON_SEL_1A 2
#define BUTTON_SEL_1B 3
#define BUTTON_SEL_1C 4
#define BUTTON_PLEX_2 5
#define BUTTON_SEL_2A 6
#define BUTTON_SEL_2B 7
#define BUTTON_SEL_2C 8
#define DIE_LIMIT_1 21
#define DIE_LIMIT_2 22
#define ADVANCE_LIMIT_1 23
#define ADVANCE_LIMIT_2 24
#define DIE_BEAM 25
#define CHUCK_BEAM 26
#define DIAL_CHANNEL_A 27
#define DIAL_CHANNEL_B 28

#define INDUCTIVE_PROX_1 9
#define INDUCTIVE_PROX_2 10
#define DISPLAY_WAIT 11
#define DISPLAY_INT 12
#define DIE_CLAMP_ENA_POS 13
#define ROTATION_ENA_POS 14
#define ADVANCING_ENA_POS 15
#define SEVEN_SEG_A0 0
#define SEVEN_SEG_A1 1
#define SEVEN_SEG_GB 2
#define SEVEN_SEG_OEB 3
#define CHUCK_CLAMP_ENA_POS 4
#define CHUCK_CLAMP_PUL_POS 5
#define BENDING_L_ENA 6
#define BENDING_R_ENA 7

//Include libraries
#include "Mux.hpp"
#include "Config.hpp"
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

        void reset();

        void start();

        void bend();

        void finish();

        // List all of the methods for the class here


};

#endif