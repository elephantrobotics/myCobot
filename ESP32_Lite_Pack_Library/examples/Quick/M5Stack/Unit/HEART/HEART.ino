#include <Wire.h>
#include "MAX30100_PulseOximeter.h"  // http://librarymanager/All#MAX30100lib https://github.com/oxullo/Arduino-MAX30100

#define REPORTING_PERIOD_MS     1000

PulseOximeter pox;

uint32_t tsLastReport = 0;

// コールバック
void onBeatDetected()
{
  Serial.println("Beat!");
}

void setup()
{
  Serial.begin(115200);
  delay(100);
  Serial.print("Initializing pulse oximeter..");

  Wire.begin(32, 33); // M5StickC

  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }

  // コールバック登録
  //pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()
{
  pox.update();

  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    Serial.print(pox.getHeartRate());
    Serial.print(",");
    Serial.print(pox.getSpO2());
    Serial.println();

    tsLastReport = millis();
  }
}
