#ifndef TUBENDERSTATEMACHINE_HPP
#define TUBENDERSTATEMACHINE_HPP

// UI pins
#define LINEAR_POTENTIOMETER_PIN 35
//GPIO Expander 1 pins
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
// #define DIAL_CHANNEL_A 27
// #define DIAL_CHANNEL_B 28
#define INT_A 20



// Pins on GPIO expander 2

#define INDUCTIVE_PROX_1 2
#define INDUCTIVE_PROX_2 3
#define DISPLAY_WAIT 4
#define DISPLAY_INT 5
#define DIE_CLAMP_ENA 6
#define ROTATION_ENA 7
#define ADVANCING_ENA 8
#define SEVEN_SEG_A0 21
#define SEVEN_SEG_A1 22
#define SEVEN_SEG_GB 23
#define SEVEN_SEG_OEB 24
#define CHUCK_CLAMP_ENA 25
#define CHUCK_CLAMP_PUL 26
#define BENDING_L_ENA 27
#define BENDING_R_ENA 28


//Include libraries
#include "Mux.hpp"
#include "Config.hpp"
// Constant Variables
const float gravity = 9.81; //this is just an example, delete this if/when we have a real variable
const double angleToStepsChuck = 10.0; //const that converts angle value to steps
const double angleToDCBending = 3.0; //const that converts an angle value to DC for linear actuator
const double lengthToStepsPlatform = 10.0; //const that converts a length
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