#include "PID.hpp"
#include <Arduino.h>
#include "TubenderStateMachine.hpp" // need this to read pin definitions

// Constructor
PID::PID(Adafruit_MCP23X17 &expander) : gpioExpander(expander){
  
    prevTime = millis() - sampleTime; // starts the millis timer and offsets it so that .run() can be used immediately

}

// Clears previous variables and sets a setpoint based on a desired angle
void PID::prepareNewBend(float angle){
    
    // Clear old variables
    integrator = 0.0f;
    prevError = 0.0f;
    differentiator = 0.0f;
    prevMeasurement = 0.0f;
    output = 0.0f;

    // Define setpoint based on the angle
    if (angle <= 50) { // angles larger than 50 degrees are outside our range  

        setpoint = 4095 - (4095/16) * (14*(tan(15*(PI/180))+tan((angle-15)*(PI/180)))); // units = ADC (0-4095) ***TUNE THIS CONVERSION***

    } else {

        // ***THROW AN ERROR***

    }

}

// Clears previous variables and sets the setpoint to fully retract
void PID::prepareHome(){
    
    // Clear old variables
    integrator = 0.0f;
    prevError = 0.0f;
    differentiator = 0.0f;
    prevMeasurement = 0.0f;
    output = 0.0f;

    // Define setpoint
    setpoint = 4095.0f;    

}

// Runs the linear actuator by regularly updating the output of the PID controller based on the sensor input and setpoint value
void PID::run(){

    continueBend = true;

    while (continueBend == true) {

        unsigned long now = millis(); // millis timer to account for any processing time that this PID calculation takes instead of just a delay
        unsigned long timeChange = (now - prevTime);
        if (timeChange >= sampleTime) {
    

            measurement = analogRead(BENDING_LIN_POT); // 0-4095 since 12-bit ADC

            // Error Signal
            float error = setpoint - measurement;


            // Proportional
            float proportional = Kp * error;


            // Integral
            integrator += 0.5f * Ki * (sampleTime/1000) * (error + prevError);

            // Anti-wind up via dynamic integrator clamping -> fancy terms for making sure the integral part isn't counted if we're far from the setpoint

            // First, dynamically figuring output the integrator limits (different from output limits!)
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
            differentiator = (2.0f * Kd * (measurement-prevMeasurement) + (2.0f * tau - (sampleTime/1000)) * differentiator)/(2.0f * tau + (sampleTime/1000));


            // Add the PID terms together
            output = proportional + integrator + differentiator;


            // Limiting the output to the intended range
            if (output > limMax) {

                output = limMax;

            } else if (output < limMin) {

                output = limMin;

            }


            // Update the previous values for future use
            prevError = error;
            prevMeasurement = measurement;
            prevTime = now;


            // Running the linear actuator
            if (output > 10.0f) { // Backward ***CHECK THIS DIRECTION***
                
                gpioExpander.digitalWrite(BENDING_L_ENA, HIGH);
                gpioExpander.digitalWrite(BENDING_R_ENA, HIGH);
                analogWrite(BENDING_LPWM, output);
                analogWrite(BENDING_RPWM, 0);

            } else if (output < -10.0f) { // Forward ***CHECK THIS DIRECTION***

                gpioExpander.digitalWrite(BENDING_L_ENA, HIGH);
                gpioExpander.digitalWrite(BENDING_R_ENA, HIGH);
                analogWrite(BENDING_LPWM, 0);
                analogWrite(BENDING_RPWM, abs(output));        

            } else { // Stop since within range ***CHECK THIS RANGE***

                stop();        

            }
        }
    }
}


// Stops the linear actuator
void PID::stop() {
    gpioExpander.digitalWrite(BENDING_L_ENA, LOW);
    gpioExpander.digitalWrite(BENDING_R_ENA, LOW);
    analogWrite(BENDING_LPWM, 0);
    analogWrite(BENDING_RPWM, 0);  
    continueBend = false;  
}



