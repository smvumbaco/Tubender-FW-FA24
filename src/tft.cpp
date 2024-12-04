#include "tft.hpp"

#define RA8875_RST 12
const int Y_POS_TITLE = 100;
const int Y_OFFSET_BENDSELECT = 110;

bool TFT::initialize() {
    expander->digitalWrite(RA8875_RST, LOW);
    delay(100);
    expander->digitalWrite(RA8875_RST, HIGH);
    delay(100);
    if (!tft.begin(RA8875_800x480)) {
        Serial.println("RA8875 not found ... check wiring?");
        return false;
    }
    Serial.println("RA8875 initialized!");

    // Configure the display
    tft.displayOn(true);
    tft.GPIOX(true);      // Enable the TFT - display enable tied to GPIOX
    tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
    tft.PWM1out(255);     // Set backlight to maximum brightness
    tft.textMode();
    return true;
}

int TFT::centerCursor(int inLineLength, int inTextScale) {
  return (800 - ((8 * (inTextScale + 1)) * (inLineLength - 1) )) / 2;
}

void TFT::printCenterText(const char text[], int textLength, int textScale, int yPos) {
  TFT::tft.textSetCursor(centerCursor(textLength, textScale), yPos); // Set Middle Postion
  TFT::tft.print(text);
}



void TFT::displayStartMenu(){
  resetScreen();
  printCenterText("Welcome to Tubender!", sizeof("Welcome to Tubender!"), textScale, Y_POS_TITLE );
  //Line 2
  textScale = 2;
  tft.textEnlarge(textScale); //Reduce text size to 3X scale
  printCenterText("Press (", sizeof("Press (START) to begin bending"), textScale,  Y_POS_TITLE + 150);
  tft.textColor(RA8875_GREEN, RA8875_WHITE);
  tft.print("START");
  tft.textColor(RA8875_BLACK, RA8875_WHITE);
  tft.print(") to begin bending");
}

void TFT::displayTubeInput() {
  resetScreen();
  printCenterText("Insert the tube,", sizeof("Insert the tube,"), textScale, Y_POS_TITLE );
  printCenterText("then input length", sizeof("then input length"), textScale, Y_POS_TITLE + 100 );
}

void TFT::displayAdvancementInput(){
  resetScreen();
  printCenterText("Input Advancment Distance ", sizeof("Input advancment distance prior to the bend"), textScale, Y_POS_TITLE );
  printCenterText("(length prior to the bend)", sizeof("(length prior to the bend)"), textScale, Y_POS_TITLE + 100 );
}

void TFT::displayBendSelect() {
  resetScreen();
  tft.textEnlarge(textScale);   // Enlarge text to 4X scale
  char line[] = "Select a Bend Type:";
  tft.textSetCursor(centerCursor(sizeof(line), textScale), 70); // Set Middle Postion
  tft.print(line);
  
  textScale = 2;
  tft.textEnlarge(textScale);
  const char* bendOptions[] = {"1) Kick", "2) Offset", "3) Saddle", "4) U-Bend", "5) 3D-Bend" };

  for (int bendNum = 1; bendNum <= 4; bendNum++) {
    printCenterText(bendOptions[bendNum - 1], sizeof( (bendOptions[bendNum - 1]) + 8), textScale, Y_OFFSET_BENDSELECT + (bendNum * 60) );
  }
  
}

void TFT::displayVarInputMenu() {
  int paramaterXCor = 200;

  resetScreen();
  char lines[][30] = {"Enter bend parameters:","Height: ", "Length: ", "Angle: "};
  tft.textSetCursor(50, 50); // Set Middle Postion
  tft.print(lines[0]);
  tft.textSetCursor(paramaterXCor, 160);
  tft.print(lines[1]);
  tft.textSetCursor(paramaterXCor, 260);
  tft.print(lines[2]);
  tft.textSetCursor(paramaterXCor, 360);
  tft.print(lines[3]);
}



void TFT::displayAddOrRun(){
  resetScreen();
  printCenterText("Start Bends: Press \"RUN\"", sizeof("Start Bends: Press \"RUN\""), textScale, Y_POS_TITLE );
  printCenterText("or", sizeof("or"), textScale, Y_POS_TITLE + 100 );
  printCenterText("Add Bends: Press \"NEXT\"", sizeof("Add Bends: Press \"NEXT\""), textScale, Y_POS_TITLE + 200 );
}
void TFT::displayRunning() {
  resetScreen();
  printCenterText("Bend in progress :^)", sizeof("Bend in progress :^)"), textScale, Y_POS_TITLE );
}

//Fill sceen with all white, and set text to default scale and black color
void TFT::resetScreen() {
  tft.fillScreen(RA8875_WHITE);
  tft.textColor(RA8875_BLACK, RA8875_WHITE);
  textScale = 3;
  tft.textEnlarge(textScale);   // Enlarge text to 4X scale
}


