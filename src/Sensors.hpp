
#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <Arduino.h>

/**
 * @file Sensor.hpp
 * @brief Represents a general-purpose sensor used in the Tubender system.
 * 
 * This class supports break beam sensors, limit switches, and proximity sensors.
 * Sensors are used to monitor tube placement, machine limits, and safety.
 */

class Sensor {
private:
    int pin;               // GPIO pin where the sensor is connected
    String sensorType;     // Type of sensor
    String location;       // Location or purpose (e.g., "Behind Chuck", "End of Range")

public:
    /**
     * @brief Constructor for the Sensor class.
     * @param pin GPIO pin for the sensor.
     * @param sensorType Type of sensor
     * @param location Descriptive location or purpose.
     */
    Sensor(int pin, String sensorType, String location);

    /**
     * @brief Initializes the sensor by setting the pin mode.
     * @param pullup Whether to enable internal pull-up resistor (default: false).
     */
    void initialize(bool pullup = false);

    /**
     * @brief Reads the current state of the sensor.
     * @return true if the sensor is triggered, false otherwise.
     */
    bool isTriggered();

    /**
     * @brief Returns the type of the sensor.
     * @return Sensor type as a string.
     */
    String getSensorType();

    /**
     * @brief Returns the location or purpose of the sensor.
     * @return Location or purpose as a string.
     */
    String getLocation();
};

#endif // SENSOR_HPP
