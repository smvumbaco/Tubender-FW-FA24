#ifndef TUBENDERSTATEMACHINE_HPP
#define TUBENDERSTATEMACHINE_HPP

// UI pins
#define LINEAR_POTENTIOMETER_PIN 35

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

    public:

        // Constructor
        TubenderStateMachine();
        //TubenderStateMachine(put expander parameter(s) in here);

        ~TubenderStateMachine();

        void handleState();
        
        void initializePins();

        void start();

        void bend();

        void finish();

        // List all of the methods for the class here


};

#endif