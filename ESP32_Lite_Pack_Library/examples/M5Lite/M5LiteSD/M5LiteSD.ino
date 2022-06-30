#include "M5Lite.h"

SPIClass SPI_EXT;

void setup() {
  M5Lite.begin();
  
  if (M5.Ex.board == lgfx::board_M5Stack) {
    // AutoStart
  } else if (M5.Ex.board == lgfx::board_M5StackCore2) {
    // AutoStart
  } else if (M5.Ex.board == lgfx::board_M5StickC) {
    // SD   M5StickC
    // 3V3  3V3
    // GND  GND
    // CLK  GPIO0
    // MISO GPIO38
    // MOSI GPIO26
    // CS   GND
    SPI_EXT.begin(0, 36, 26, -1);
    SD.begin(-1, SPI_EXT);
  } else if (M5.Ex.board == lgfx::board_M5StickCPlus) {
    // SD   M5StickC
    // 3V3  3V3
    // GND  GND
    // CLK  GPIO0
    // MISO GPIO38
    // MOSI GPIO26
    // CS   GND
    SPI_EXT.begin(0, 36, 26, -1);
    SD.begin(-1, SPI_EXT);
  } else if (M5.Ex.board == lgfx::board_unknown) {
    // SD   ATOM(Lite, Matrix) Doesn't work with Echo!
    // 3V3  3V3
    // GND  GND
    // CLK  GPIO23
    // MISO GPIO33
    // MOSI GPIO19
    // CS   GND
    SPI_EXT.begin(23, 33, 19, -1);
    SD.begin(-1, SPI_EXT);
  }
}

void loop() {
  M5Lite.Lcd.setCursor(0, 0, 1);
  M5Lite.Lcd.println("M5LiteSD");
  M5Lite.Lcd.println(millis());
  
  // delay & M5Lile.update()
  M5Lite.Ex.delay(100);
}
