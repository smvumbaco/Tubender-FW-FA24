#include "Sensor.hpp"
#include <Arduino.h>
using namespace std;

// Constructor
Sensor::Sensor(int pin, String sensorType, String location)
    : pin(pin), sensorType(sensorType), location(location), isInterrupt(false) {}

// Initializes the sensor by setting the pin mode
void Sensor::initialize(bool pullup) {
    if (pullup) {
        pinMode(pin, INPUT_PULLUP);  // Enable internal pull-up for switches or floating pins
    } else {
        pinMode(pin, INPUT);         // Standard input for sensors
    }
}

// Reads the current state of the sensor
bool Sensor::isTriggered() {
    return digitalRead(pin) == LOW;  // Assuming LOW means triggered for most sensors
}

// Returns the type of the sensor
String Sensor::getSensorType() {
    return sensorType;
}

// Returns the location or purpose of the sensor
String Sensor::getLocation() {
    return location;
}

void Sensor::enableInterrupt(void (*ISR)(void)) {
    attachInterrupt(digitalPinToInterrupt(pin), ISR, FALLING);
    isInterrupt = true;
}

void Sensor::disableInterrupt(){
    detachInterrupt(digitalPinToInterrupt(pin));
    isInterrupt = false;
}

