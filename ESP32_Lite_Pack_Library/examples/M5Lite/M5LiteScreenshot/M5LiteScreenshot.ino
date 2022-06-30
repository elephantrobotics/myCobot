//#include <WiFi.h>     // Define before M5Lite
#include "M5Lite.h"

void setup() {
  M5Lite.begin();

  M5Lite.Lcd.setCursor(0, 0, 1);
  M5Lite.Lcd.println("M5Lite");
  M5Lite.Lcd.println("Screenshot");

  M5Lite.Ex.screenshot(SD, "/screenshot.bmp");
}

void loop() {
  // delay & M5Lile.update()
  M5Lite.Ex.delay(100);
}
