#include <sevenSeg.hpp>

const int maxTube = 100;
const int maxAdvancement = 100;
const int maxLength = 100;
const int maxHeight = 100;


void SevenSegmentDisplay::intialize(int address) {
  sevenSeg.begin(address);
}

// Function to display a number on a specific digit
void SevenSegmentDisplay::displayDecimalValue(int value) {
  sevenSeg.print(value, DEC);
  sevenSeg.writeDisplay();
  delay(500);
}

void SevenSegmentDisplay::displayTubeLength(int value) {
  displayDecimalValue(value % maxTube);
}

void SevenSegmentDisplay::displayAdvancement(int value) {
  displayDecimalValue(value % maxAdvancement);
}

void SevenSegmentDisplay::displayHeight(int value) {
  displayDecimalValue(value % maxHeight);
}
void SevenSegmentDisplay::displayLength(int value) {
  displayDecimalValue(value % maxLength);
}

void SevenSegmentDisplay::displayAngle(int value) {
      //May have errors with handeling negative values passed
      switch (value % 4) {
        case 0:
            displayDecimalValue(0);
            break;
        case 1:
            displayDecimalValue(22.5);
            break;
        case 2:
            displayDecimalValue(45);
            break;
        case 3:
            displayDecimalValue(90);
            break;
    }
}



