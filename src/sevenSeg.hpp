#ifndef SEVENSEGMENTDISPLAY_HPP
#define SEVENSEGMENTDISPLAY_HPP

#include <Arduino.h>
#include <ShiftRegister74HC595.h>
#include <Adafruit_MCP23X17.h>

// Pins connected to SN74LVC
#define SEVEN_SEG_A0 0
#define SEVEN_SEG_A1 1
#define SEVEN_SEG_GB 2

class SevenSegmentDisplay {
public:
  // Constructor
     SevenSegmentDisplay(ShiftRegister74HC595<1> &sr, Adafruit_MCP23X17 &expander, uint8_t data, uint8_t latch, uint8_t clock) 
        : shiftRegister(sr), gpioExpander(expander), dataPin(data), latchPin(latch), clockPin(clock) {
          
        };

    // Function to select a digit using the demux
    void selectDigit(u_int8_t digit);

    // Function to display a number on a specific digit
    void displayCharacter(int digit, int value);

    void display3Digits(int value);

    // Function to clear the display
    void clearDisplay();

  private:
    uint8_t dataPin;
    uint8_t latchPin;
    uint8_t clockPin;
    Adafruit_MCP23X17 &gpioExpander;

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
    ShiftRegister74HC595<1> shiftRegister;

    // Helper function to send data to the shift register
    void shiftOutData(uint8_t data);

};

#endif // SEVENSEGMENTDISPLAY_HPP
