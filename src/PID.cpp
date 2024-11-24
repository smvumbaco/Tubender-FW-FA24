#include "PID.hpp"
#include <Arduino.h>
#include "TubenderStateMachine.hpp" // need this to read pin definitions

// Constructor
PID::PID(Adafruit_MCP23X17 &expander) : gpioExpander(expander){
  
}


// Clears previous variables and sets a setpoint based on a desired angle
void PID::prepareNewBend(float angle){
    
    // Clear old variables
    integrator = 0.0f;
    prevError = 0.0f;
    differentiator = 0.0f;
    prevMeasurement = 0.0f;
    out = 0.0f;

    // Define setpoint based on the angle
    setpoint = 10.0f; // CHANGE THIS TO CONVERT ANGLE TO SETPOINT IN INCHES, THROW AN ERROR IF OUTSIDE OF RANGE

}

// Clears previous variables and sets the setpoint to 0 to fully retract
void PID::prepareHome(){
    
    // Clear old variables
    integrator = 0.0f;
    prevError = 0.0f;
    differentiator = 0.0f;
    prevMeasurement = 0.0f;
    out = 0.0f;

    // Define setpoint
    setpoint = 0.0f;    

}

// Runs the linear actuator by regularly updating the output of the PID controller based on the sensor input and setpoint value
void PID::run(){

    //FIGURE OUT UNITS FOR EVERYTHING, SOME STUFF IS INCHES, SOME STUFF IS PWM LENGTH

    measurement = analogRead(BENDING_LIN_POT); // MAYBE CONVERT THIS VALUE TO INCHES RIGHT IN THIS LINE

    // Error Signal
    float error = setpoint - measurement;


    // Proportional
    float proportional = Kp * error;


    // Integral
    integrator += 0.5f * Ki * sampleTime * (error + prevError);

    // Anti-wind up via dynamic integrator clamping -> fancy terms for making sure the integral term doesn't go crazy based on our limits, like speed or stroke length

    // First, dynamically figuring out the integrator limits (different from output limits!)
    float limMinIntegrator, limMaxIntegrator;

    if (limMax > proportional) { 
    
        limMaxIntegrator = limMax - proportional;

    } else { 

        limMaxIntegrator = 0.0f;

    }

    if (limMin < proportional) { 
    
        limMinIntegrator = limMin - proportional;

    } else { 

        limMinIntegrator = 0.0f;
        
    }

    // Next, clamping the integrator values to those limits
    if (integrator > limMaxIntegrator) {

        integrator = limMaxIntegrator;

    } else if (integrator < limMinIntegrator) {

        integrator = limMinIntegrator;

    }


    // Derivative (aka "band-limited differentiator" because it includes a lowpass filter)
    differentiator = (2.0f * Kd * (measurement-prevMeasurement) + (2.0f * tau - sampleTime) * differentiator)/(2.0f * tau + sampleTime);


    // Add the PID terms together
    out = proportional + integrator + differentiator;


    // Limiting the output to the intended range
    if (out > limMax) {

        out = limMax;

    } else if (out < limMin) {

        out = limMin;

    }


    // Update the previous values for future use
    prevError = error;
    prevMeasurement = measurement;


    // Running the linear actuator
    if (out > 0.01f) { // Forward CHECK THIS DIRECTION
        
        digitalWrite(BENDING_L_ENA, HIGH);
        digitalWrite(BENDING_R_ENA, HIGH);
        analogWrite(BENDING_LPWM, out);
        analogWrite(BENDING_RPWM, 0.0f);

    } else if (out < -0.01f) { // Backward CHECK THIS DIRECTION

        digitalWrite(BENDING_L_ENA, HIGH);
        digitalWrite(BENDING_R_ENA, HIGH);
        analogWrite(BENDING_LPWM, 0.0f);
        analogWrite(BENDING_RPWM, out);        

    } else { // Stop since within range EDIT THIS RANGE

        stop();        

    }


    // Delaying based on the sample rate
    delay(sampleTime*1000); 

}


// Stops the linear actuator
void PID::stop() {
    digitalWrite(BENDING_L_ENA, LOW);
    digitalWrite(BENDING_R_ENA, LOW);
    analogWrite(BENDING_LPWM, 0.0f);
    analogWrite(BENDING_RPWM, 0.0f);    
}



