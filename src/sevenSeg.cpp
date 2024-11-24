#include <sevenSeg.hpp>

// Function to select a digit using the demux
void SevenSegmentDisplay::selectDigit(int digit) {
  digitalWrite(DEMUX_A, digit & 0x01);
  digitalWrite(DEMUX_B, (digit >> 1) & 0x01);
  digitalWrite(DEMUX_C, (digit >> 2) & 0x01);
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


