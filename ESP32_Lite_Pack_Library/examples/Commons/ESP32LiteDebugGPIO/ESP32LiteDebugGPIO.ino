#include "M5StickC.h"
#include "ESP32LiteDebugGPIO.h"

void setup() {
  M5.begin();
  delay(1000);
  dispGpio();
}

void loop() {
}
