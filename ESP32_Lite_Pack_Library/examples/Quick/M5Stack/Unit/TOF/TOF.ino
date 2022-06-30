#include <Wire.h>
#include <VL53L0X.h> // by Pololu http://librarymanager/All#vl53l0x-arduino https://github.com/pololu/vl53l0x-arduino

VL53L0X sensor;

void setup()
{
  Serial.begin(115200);
  Wire.begin(32, 33); // M5StickC

  sensor.setAddress(0x29);
  sensor.setTimeout(500);
  if (!sensor.init()) {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  sensor.startContinuous();
}

void loop()
{
  Serial.print(sensor.readRangeContinuousMillimeters());
  if (sensor.timeoutOccurred()) {
    Serial.print(" TIMEOUT");
  }

  Serial.println();
}
