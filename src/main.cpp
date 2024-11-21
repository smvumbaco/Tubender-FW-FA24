#include "TubenderStateMachine.hpp"
#include <tft.hpp>
#include <Arduino.h>
#include <Adafruit_RA8875.h>

#define RA8875_CS  5   // Chip select pin
#define RA8875_RST 4   // Reset pin

Adafruit_RA8875 adafruitTFT = Adafruit_RA8875(RA8875_CS, RA8875_RST);

void setup() {
    Serial.begin(115200);
    TFT myTFT(adafruitTFT);
    myTFT.initialize();
    myTFT.displayStartMenu();


}

void loop() {

}