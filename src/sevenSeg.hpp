#ifndef SEVENSEGMENTDISPLAY_HPP
#define SEVENSEGMENTDISPLAY_HPP

#include <Arduino.h>
#include <ShiftRegister74HC595.h>

// Pins connected to the CD405xB (demultiplexer control)
#define DEMUX_A 8
#define DEMUX_B 9
#define DEMUX_C 10

class SevenSegmentDisplay {
public:
  // Constructor
     SevenSegmentDisplay(ShiftRegister74HC595 &sr, uint8_t data, uint8_t latch, uint8_t clock) 
        : shiftRegister(sr), dataPin(data), latchPin(latch), clockPin(clock) {}


    // Function to select a digit using the demux
    void selectDigit(int digit);

    // Function to display a number on a specific digit
    void displayCharacter(int digit, int value);

    void display3Digits(int value);

    // Function to clear the display
    void clearDisplay();

  private:
    uint8_t dataPin;
    uint8_t latchPin;
    uint8_t clockPin;

    // Segment map for common cathode display (BC56-12EWA)
    const uint8_t segmentMap[10] = {
        0b00111111, // 0
        0b00000110, // 1
        0b01011011, // 2
        0b01001111, // 3
        0b01100110, // 4
        0b01101101, // 5
        0b01111101, // 6
        0b00000111, // 7
        0b01111111, // 8
        0b01101111  // 9
    };
    ShiftRegister74HC595<1> shiftRegister(dataPin, latchPin, clockPin);

    // Helper function to send data to the shift register
    void shiftOutData(uint8_t data);

};

#endif // SEVENSEGMENTDISPLAY_HPP
