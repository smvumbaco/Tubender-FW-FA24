#ifndef TFT_CLASS
#define TFT_CLASS

#include <Adafruit_RA8875.h>
#include "Adafruit_MCP23X17.h"
#include <SD.h>

class TFT {
  public:
    TFT(Adafruit_RA8875 &display, Adafruit_MCP23X17 *gpioExpander) : tft(display), expander(gpioExpander) {}

    //Intialize TFT
    void initialize();

    // Text Centering Helpers
    int centerCursor(int inLineLength, int inTextScale);
    void printCenterText(const char text[], size_t textLength, int textScale, int yPos);

    // Display Screens
    void displayStartMenu();
    void displayBendSelect();
    void displayVarInputMenu();
    void displayHeightSelect();
    void displayLengthSelect();
    void displayAngleSelect();

    // Wipe Screen
    void resetScreen();

    // SD Image Display
    void readImageFromSD(const char* filename);
    uint16_t color565(uint8_t r, uint8_t g, uint8_t b);
    void displayBitmap(File bmpFile);

  private:
    Adafruit_RA8875 &tft;
    Adafruit_MCP23X17 *expander;
};

#endif
