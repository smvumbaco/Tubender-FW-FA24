#pragma once

#include <Adafruit_RA8875.h>
#include "Adafruit_MCP23X17.h"
#include <SD.h>

class TFT {
  public:
    TFT(Adafruit_RA8875 &display, Adafruit_MCP23X17 *gpioExpander) : tft(display), expander(gpioExpander) {}

    //Intialize TFT
    bool initialize();

    // Text Centering Helpers
    int centerCursor(int inLineLength, int inTextScale);
    void printCenterText(const char text[], int textLength, int textScale, int yPos);

    // Display Screens
    void displayStartMenu();
    void displayTubeInput();
    void displayAdvancementInput();
    void displayBendSelect();
    void displayVarInputMenu();
    void displayAddOrRun();
    void displayRunning();

    // Wipe Screen and set default text options
    void resetScreen();

  private:
    Adafruit_RA8875 &tft;
    int textScale;
    Adafruit_MCP23X17 *expander;
};

