#ifndef PID_HPP
#define PID_HPP

#include <Adafruit_MCP23X17.h>

class PID {
    
    private:

        // In order to read from the gpio expander
        Adafruit_MCP23X17 &gpioExpander;

        // Setpoint -> the desired end position
        float setpoint;

        // Measured position from the linear potentiometer
        float measurement;

        // Controller Gains -> these are the values we should tune
        const float Kp = 1.0f;
        const float Ki = 0.0f;
        const float Kd = 0.0f;

        // Derivative low-pass filter time constant -> to avoid amplification of high frequency noise
        const float tau = 1.0f; // ***CHOOSE A BETTER VALUE FOR LOW PASS FILTER (IF Kd > 0, OTHERWISE UNNECESSARY)***

        // Output limits -> to make sure we don't send signals outside the linear actuator's input range
        const float limMin = -255.0f; // duty cycle
        const float limMax = 255.0f; // duty cycle

        // Sample Time
        const float sampleTime = 100.0f; // milliseconds

        // Controller "memory"
        float integrator;
        float prevError; // Required for integrator
        float differentiator;
        float prevMeasurement; // Required for differentiator

        // Controller Output
        float output;

        // While true, PID.run() continues to loop, and stops when it's false
        bool continueBend;

        // Used for millis timer
        unsigned long prevTime;

    public:

        PID(Adafruit_MCP23X17 &expander); // Constructor

        void prepareNewBend(float angle); // Clears previous variables and sets a setpoint based on a desired angle

        void prepareHome(); // Clears previous variables and sets the setpoint to fully retract

        void run(); // Runs the linear actuator by regularly updating the output of the PID controller based on the sensor input and setpoint value

        void stop(); // Stops the linear actuator

};

#endif