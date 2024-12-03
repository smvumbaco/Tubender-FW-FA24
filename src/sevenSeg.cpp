#include <sevenSeg.hpp>

// Function to select a digit using the demux - active low since this is the cathode and we need to create a voltage drop from the anode
// A0 = LSB of digit, A1 = second bit of digit
void SevenSegmentDisplay::selectDigit(u_int8_t digit) {
  gpioExpander.digitalWrite(SEVEN_SEG_GB, 0);
  gpioExpander.digitalWrite(SEVEN_SEG_A0, digit & 0x01);
  gpioExpander.digitalWrite(SEVEN_SEG_A1, (digit >> 1) & 0x01);
}

// Function to display a number on a specific digit
void SevenSegmentDisplay::displayCharacter(int digit, int value) {
  selectDigit(digit);                    // Select the digit (via demux)
  uint8_t data = segmentMap[value];      // Get segment data for the value
  shiftRegister.setAll(&data);            // Send data to the shift register
}

void SevenSegmentDisplay::display3Digits(int value) {
    // Extract and display each digit individually
    for (int digitNum = 0; digitNum < 3; digitNum++) {
        int digitValue = (value / (int)pow(10, 2 - digitNum)) % 10; // Extract digit
        displayCharacter(digitNum, digitValue); // Display digit on its corresponding segment
        delay(5); // Small delay for multiplexing
    }
}


