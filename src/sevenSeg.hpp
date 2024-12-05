#ifndef SEVENSEGMENTDISPLAY_HPP
#define SEVENSEGMENTDISPLAY_HPP

#include <Arduino.h>
#include <Adafruit_MCP23X17.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

// Pins connected to SN74LVC
#define SEVEN_SEG_DT 0
#define SEVEN_SEG_CLK 1

class SevenSegmentDisplay {
public:
  // Constructor
     SevenSegmentDisplay( Adafruit_7segment seg ) 
        : sevenSeg(seg)  {
        };
    void intialize(int address);
    // Function to display a number on a specific digit
    void displayTubeLength(int value);
    void displayAdvancement(int value);
    void displayDecimalValue(int value);
    void displayAngle(int value);
    void displayHeight(int value);
    void displayLength(int value);

  private:
    Adafruit_7segment sevenSeg;

    // Segment map for common cathode display (BC56-12EWA)
    const uint8_t segmentMap[10] = {
    0b11111100,  // 0
    0b01100000,  // 1
    0b11011010,  // 2
    0b11110010,  // 3
    0b01100110,  // 4
    0b10110110,  // 5
    0b10111110,  // 6
    0b11100000,  // 7
    0b11111110,  // 8
    0b11110110   // 9
  };

};

#endif // SEVENSEGMENTDISPLAY_HPP
