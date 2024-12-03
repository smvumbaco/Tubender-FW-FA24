#ifndef TUBENDERSTATEMACHINE_HPP
#define TUBENDERSTATEMACHINE_HPP

// Update sensor pins / check that they're correct

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
#define DIE_LIMIT_1 21
#define DIE_LIMIT_2 22
#define ADVANCE_LIMIT_1 23
#define ADVANCE_LIMIT_2 24
#define DIE_BEAM 25
#define CHUCK_BEAM 26
#define DIAL_CHANNEL_A 27
#define DIAL_CHANNEL_B 28

#define INDUCTIVE_PROX_1 2
#define INDUCTIVE_PROX_2 3
#define DISPLAY_WAIT 4
#define DISPLAY_INT 5
#define DIE_CLAMP_ENA_POS 6
#define ROTATION_ENA_POS 7
#define ADVANCING_ENA_POS 8
#define SEVEN_SEG_A0 21
#define SEVEN_SEG_A1 22
#define SEVEN_SEG_GB 23
#define SEVEN_SEG_OEB 24
#define CHUCK_CLAMP_ENA_POS 25
#define CHUCK_CLAMP_PUL_POS 26
#define BENDING_L_ENA 27
#define BENDING_R_ENA 28

//Include libraries

#include "Config.hpp"
#include "Sensors.hpp"
#include "Mux.hpp"

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

        Sensor breakBeamBehindChuck; // Pin 4
        Sensor breakBeamBeforeDie; // Pin 5
        Sensor limitSwitchAdvance; // Pin 2
        Sensor limitSwitchDie; // Pin 3
        Sensor proximityOnChuck1; // Pin 9
        Sensor proximityOnChuck2; // Pin 10
        Sensor dieLimit1; // Pin 0
        Sensor dieLimit2; // Pin 1
    public:

        // Constructor
        TubenderStateMachine();
       
        ~TubenderStateMachine();

        void handleState();
        
        void initializePins();

        void start();

        void bend();

        void finish();

        // List all of the methods for the class here
        static void handleBreakBeamBehindChuckInterrupt();
        static void handleBreakBeamBeforeDieInterrupt();
        static void handleLimitSwitchStartInterrupt();
        static void handleLimitSwitchEndInterrupt();
        static void handleProximityOnChuckInterrupt();
        static void handleDieLimit1Interrupt();
        static void handleDieLimit2Interrupt();
        static void handleProximityOnChuck2Interrupt();

};

#endif