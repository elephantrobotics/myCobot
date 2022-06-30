#include <Adafruit_MCP4725.h>   // http://librarymanager/All#Adafruit_MCP4725 https://github.com/adafruit/Adafruit_MCP4725

Adafruit_MCP4725 dac;

void setup() {
  dac.begin(0x60, &Wire);       // call Wire.begin()
  Wire.begin(32, 33);           // Re Init(M5StickC)

  Serial.begin(115200);
  delay(1000);
}

void loop() {
  dac.setVoltage(0, false, 400000L);
  dac.setVoltage(4095, false, 400000L);
}
