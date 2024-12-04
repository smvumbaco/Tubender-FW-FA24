#include <tft.hpp>
#define RA8875_RST 12

void TFT::initialize() {
    expander->digitalWrite(RA8875_RST, LOW);
    delay(100);
    expander->digitalWrite(RA8875_RST, HIGH);
    delay(100);
    if (!TFT::tft.begin(RA8875_800x480)) {
        Serial.println("RA8875 not found ... check wiring?");
        while (1);
    }
    Serial.println("RA8875 initialized!");

    // Configure the display
    TFT::tft.displayOn(true);
    TFT::tft.GPIOX(true);      // Enable the TFT - display enable tied to GPIOX
    TFT::tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
    TFT::tft.PWM1out(255);     // Set backlight to maximum brightness
    TFT::tft.textMode();

}

int TFT::centerCursor(int inLineLength, int inTextScale) {
  return (800 - ((8 * (inTextScale + 1)) * (inLineLength - 1) )) / 2;
}

void TFT::printCenterText(const char text[], size_t textLength, int textScale, int yPos) {
  TFT::tft.textSetCursor(centerCursor(textLength, textScale), yPos); // Set Middle Postion
  TFT::tft.print(text);
}

void TFT::displayStartMenu(){
  resetScreen();
  //tft.drawBitmap(0, 0, bmpFile);
  //Line 1
  tft.textColor(RA8875_BLACK, RA8875_WHITE);
  int textScale = 3;
  tft.textEnlarge(textScale);   // Enlarge text to 4X scale
  printCenterText("Welcome to Tubender!", sizeof("Welcome to Tubender!"), textScale, 100 );
  //Line 2
  textScale = 2;
  tft.textEnlarge(textScale); //Reduce text size to 3X scale
  printCenterText("Press (", sizeof("Press ("), textScale,  300);
  tft.textColor(RA8875_GREEN, RA8875_WHITE);
  tft.print("START");
  tft.textColor(RA8875_BLACK, RA8875_WHITE);
  tft.print(") to begin bending");
}

void TFT::displayBendSelect() {
  resetScreen();
  //Line 1
  tft.textColor(RA8875_BLACK, RA8875_WHITE);
  int textScale = 3;
  tft.textEnlarge(textScale);   // Enlarge text to 4X scale
  char line[] = "Select a Bend Type:";
  tft.textSetCursor(centerCursor(sizeof(line), textScale), 70); // Set Middle Postion
  tft.print(line);
  
  textScale = 2;
  tft.textEnlarge(textScale);
  const int y_offset = 70;
  const char* bendOptions[] = {"1) Kick", "2) Offset", "3) Saddle", "4) U-Bend", "5) 3D-Bend" };

  for (int bendNum = 1; bendNum <= 4; bendNum++) {
    printCenterText(bendOptions[bendNum - 1], sizeof(bendOptions[bendNum - 1]), textScale, y_offset + (bendNum * 60) );
  }
  
}

void TFT::displayVarInputMenu() {
  resetScreen();
  //Line 1
  tft.textColor(RA8875_BLACK, RA8875_WHITE);
  int textScale = 3;
  tft.textEnlarge(textScale);   // Enlarge text to 4X scale
  char lines[][30] = {"Enter bend parameters:","Height: ", "Length: ", "Angle: "};
  tft.textSetCursor(50, 50); // Set Middle Postion
  tft.print(lines[0]);
  int paramaterXCor = 200;
  tft.textSetCursor(paramaterXCor, 160);
  tft.print(lines[1]);
  tft.textSetCursor(paramaterXCor, 260);
  tft.print(lines[2]);
  tft.textSetCursor(paramaterXCor, 360);
  tft.print(lines[3]);
}

#define ARROW_X 180
void TFT::displayHeightSelect(){
  tft.textSetCursor(ARROW_X, 160);
  tft.print("->");
}
void TFT::displayLengthSelect(){
  tft.textSetCursor(ARROW_X, 260);
  tft.print("->");
}
void TFT::displayAngleSelect(){
  tft.textSetCursor(ARROW_X, 360);
  tft.print("->");
}

void TFT::resetScreen() {
  tft.textColor(RA8875_BLACK, RA8875_WHITE);
  tft.fillScreen(RA8875_WHITE);
}
void TFT::readImageFromSD(const char* filename) { 
  File bmpFile = SD.open(filename);
  if (bmpFile) {
      Serial.println("Displaying image...");
      displayBitmap(bmpFile);
      bmpFile.close();
  }
  else {
      Serial.println("Error opening image file.");
  }
}

uint16_t TFT::color565(uint8_t r, uint8_t g, uint8_t b) {
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void TFT::displayBitmap(File bmpFile) {
  // BMP header information (14-byte header + 40-byte DIB header)
  bmpFile.seek(10);  // Offset to the start of pixel data
  uint32_t dataOffset;
  bmpFile.read((uint8_t*)&dataOffset, 4);

  // Image width and height
  bmpFile.seek(18);
  int32_t width, height;
  bmpFile.read((uint8_t*)&width, 4);
  bmpFile.read((uint8_t*)&height, 4);

  // Set position for pixel data and start drawing
  bmpFile.seek(dataOffset);

  // BMP files are typically stored bottom-to-top
  bool flip = height > 0;
  height = abs(height);

  uint16_t pixel;
  for (int y = 0; y < height; y++) {
    int row = flip ? (height - 1 - y) : y;
    for (int x = 0; x < width; x++) {
      // Read pixel (assume 24-bit BMP with no compression)
      uint8_t b = bmpFile.read();
      uint8_t g = bmpFile.read();
      uint8_t r = bmpFile.read();
      pixel = color565(r, g, b);
      tft.drawPixel(x, row, pixel);
    }
  }
}