#ifndef TUBENDERSTATEMACHINE_HPP
#define TUBENDERSTATEMACHINE_HPP

// UI pins
#define LINEAR_POTENTIOMETER_PIN 35
//GPIO Expander 1 pins
#define BUTTON_PLEX_1 8
#define BUTTON_SEL_1A 9
#define BUTTON_SEL_1B 10
#define BUTTON_SEL_1C 11
#define BUTTON_PLEX_2 12
#define BUTTON_SEL_2A 13
#define BUTTON_SEL_2B 14
#define BUTTON_SEL_2C 15
#define DIE_LIMIT_1 0
#define DIE_LIMIT_2 1
#define ADVANCE_LIMIT_1 2
#define ADVANCE_LIMIT_2 3
#define DIE_BEAM 4
#define CHUCK_BEAM 5

#define INT_A 20

//gpioExpander2 pins
//GPA
#define SEVEN_SEG_A0 0
#define SEVEN_SEG_A1 1
#define SEVEN_SEG_GB 2
#define SEVEN_SEG_OEB 3
#define CHUCK_CLAMP_ENA 4
#define CHUCK_CLAMP_PUL 5
#define BENDING_L_ENA 6
#define BENDING_R_ENA 7

//GPB
#define INDUCTIVE_S_1 9
#define INDUCTIVE_PROX_2 10
#define DISPLAY_WAIT 11
#define DISPLAY_INT 12
#define DIE_CLAMP_ENA 13
#define ROTATION_ENA 14
#define ADVANCING_ENA 15


//Include libraries
#include "Mux.hpp"
#include "Config.hpp"
#include "Sensor.hpp"

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