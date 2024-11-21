#ifndef PID_HPP
#define PID_HPP

// DO I NEED TO DEFINE PINS HERE, OR CAN I ACCESS THE ONES WE DEFINED IN THE STATEMACHINE (MAYBE BY INCLUDING THE STATEMACHINE)
#define BENDING_LIN_POT 35
#define BENDING_RPWM 14
#define BENDING_LPWM 15

// FIGURE OUT HOW TO DEFINE THESE PINS, SINCE THEY'RE ON THE EXPANDER
#define BENDING_L_ENA 0 
#define BENDING_R_ENA 0

class PID {
    
    private:

        // Setpoint -> the desired end position
        float setpoint;

        // Measured position from the linear potentiometer
        float measurement;

        // Controller Gains -> these are the values we should tune
        const float Kp = 1.0f;
        const float Ki = 0.0f;
        const float Kd = 0.0f;

        // Derivative low-pass filter time constant -> to avoid amplification of high frequency noise
        const float tau = 1.0f;

        // Output limits -> to make sure we don't send signals outside the linear actuator's input range
        const float limMin = 0.0f;
        const float limMax = 255.0f; //CHECK THE RANGE FOR PWM WRITING

        // Sample Time
        const float T = 0.05f; // DOUBLE CHECK THAT THIS MEANS WHAT I THINK IT MEANS

        // Controller "memory"
        float integrator;
        float prevError; // Required for integrator
        float differentiator;
        float prevMeasurement; // Required for differentiator

        // Controller Output
        float out;

    public:

        PID(); // Constructor

        void prepareNewBend(float angle); // Clears previous variables and sets a setpoint based on a desired angle

        void prepareHome(); // Clears previous variables and sets the setpoint to 0 to fully retract

        void run(); // Runs the linear actuator by regularly updating the output of the PID controller based on the sensor input and setpoint value

        void stop(); // Stops the linear actuator

};

#endif