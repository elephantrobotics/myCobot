# ESP32 Lite Pack Library

A lightweight compatibility library. You can use any combination of libraries.

## Usage library

### LovyanGFX(like M5Display)
https://github.com/lovyan03/LovyanGFX

### FastLED
https://github.com/FastLED/FastLED

### I2C_AXP192(like AXP192)
https://github.com/tanakamasayuki/I2C_AXP192

### I2C_BM8563(like RTC)
https://github.com/tanakamasayuki/I2C_BM8563

### I2C_MPU6886(like MPU6886)
https://github.com/tanakamasayuki/I2C_MPU6886

## Support Devices

- [M5StickC](https://docs.m5stack.com/#/en/core/m5stickc)
- [M5StickC Plus](https://docs.m5stack.com/#/en/core/m5stickc_plus)
- [M5Stack BASIC](https://docs.m5stack.com/#/en/core/basic)
- [M5Stack GRAY](https://docs.m5stack.com/#/en/core/gray)
- [M5Stack FIRE](https://docs.m5stack.com/#/en/core/fire)
- [M5Stack CORE2](https://docs.m5stack.com/#/en/core/core2)
- [M5Stack ATOM Lite](https://docs.m5stack.com/#/en/core/atom_lite)
- [M5Stack ATOM Matrix](https://docs.m5stack.com/#/en/core/atom_matrix)
- [M5Stack ATOM ECHO](https://docs.m5stack.com/#/en/atom/atomecho)

## Usage
```c
#include <WiFi.h>     // Define before M5Lite
#include "M5Lite.h"

void setup() {
  M5Lite.begin();
  M5Lite.Axp.ScreenBreath(10);

  M5Lite.Imu.Init();

  M5Lite.dis.drawpix(0, CRGB(255, 0, 0));
  M5Lite.dis.drawpix(2, CRGB(0, 255, 0));
  M5Lite.dis.drawpix(4, CRGB(0, 0, 255));
  M5Lite.dis.drawpix(6, CRGB::White);

  // Info & Help
  M5Lite.Debug.dispInfo();
  M5Lite.Debug.dispHelp();
}

void loop() {
  static int vol = 11;

  M5Lite.Lcd.setCursor(0, 4, 1);
  M5Lite.Lcd.printf("M5StackAuto\n");

  M5Lite.Lcd.printf("Battery\n");
  M5Lite.Lcd.printf(" Temp :%6.1f\n", M5Lite.Axp.GetTempInAXP192());  // AXP192 Internal temperature
  M5Lite.Lcd.printf(" V(V) :%6.3f\n", M5Lite.Axp.GetBatVoltage());    // Battery Voltage(3.0V-4.2V)
  M5Lite.Lcd.printf(" I(mA):%6.1f\n", M5Lite.Axp.GetBatCurrent());    // Battery Current(+:charge, -:decharge)

  M5Lite.Lcd.printf("ASP\n");
  M5Lite.Lcd.printf(" V(V) :%6.3f\n", M5Lite.Axp.GetAPSVoltage());    // ESP32 Voltage

  M5Lite.Lcd.printf("VBus(USB)\n");
  M5Lite.Lcd.printf(" V(V) :%6.3f\n", M5Lite.Axp.GetVBusVoltage());   // USB Voltage
  M5Lite.Lcd.printf(" I(mA):%6.1f\n", M5Lite.Axp.GetVBusCurrent());   // USB Current

  M5Lite.Lcd.printf("VIN(5V-In)\n");
  M5Lite.Lcd.printf(" V(V) :%6.3f\n", M5Lite.Axp.GetVinVoltage());    // 5V IN Voltage
  M5Lite.Lcd.printf(" I(mA):%6.1f\n", M5Lite.Axp.GetVinCurrent());    // 5V IN Current

  if (M5Lite.Imu.imuType != 0) {
    float ax;
    float ay;
    float az;
    float gx;
    float gy;
    float gz;
    float t;

    M5Lite.Imu.getAccelData(&ax, &ay, &az);
    M5Lite.Imu.getGyroData(&gx, &gy, &gz);
    M5Lite.Imu.getTempData(&t);

    if (!M5Lite.Ex.useLcd) {
      Serial.printf(" %f,%f,%f,%f,%f,%f,%f\n", ax, ay, az, gx, gy, gz, t);
    }

    M5Lite.Lcd.printf(" Accel   Gyro\n");
    M5Lite.Lcd.printf("X%5.2f%7.1f\n", ax, gx);
    M5Lite.Lcd.printf("Y%5.2f%7.1f\n", ay, gy);
    M5Lite.Lcd.printf("Z%5.2f%7.1f\n", az, gz);
  }

  RTC_TimeTypeDef RTC_TimeStruct;
  RTC_DateTypeDef RTC_DateStruct;
  M5Lite.Rtc.GetTime(&RTC_TimeStruct);
  M5Lite.Rtc.GetData(&RTC_DateStruct);
  M5Lite.Lcd.printf("%04d-%02d-%02d\n", RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date);
  M5Lite.Lcd.printf("%02d:%02d:%02d\n", RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);

  if (M5Lite.BtnA.wasPressed()) {
    Serial.println("M5Lite.BtnA.wasPressed()");
    M5Lite.Beep.tone(1000, 100);
  }
  if (M5Lite.BtnB.wasPressed()) {
    Serial.println("M5Lite.BtnB.wasPressed()");
    vol--;
    M5Lite.Beep.setVolume(vol);
    Serial.printf("vol = %d\n", vol);
  }
  if (M5Lite.BtnC.wasPressed()) {
    Serial.println("M5Lite.BtnC.wasPressed()");
    vol++;
    M5Lite.Beep.setVolume(vol);
    Serial.printf("vol = %d\n", vol);
  }
  if (M5Lite.BtnA.wasReleased()) {
    Serial.println("M5Lite.BtnA.wasReleased()");
  }
  if (M5Lite.BtnB.wasReleased()) {
    Serial.println("M5Lite.BtnB.wasReleased()");
  }
  if (M5Lite.BtnC.wasReleased()) {
    Serial.println("M5Lite.BtnC.wasReleased()");
  }
  if (M5Lite.Touch.enable) {
    TouchPoint_t p = M5Lite.Touch.getPressPoint();
    M5Lite.Lcd.printf("Touch\n");
    M5Lite.Lcd.printf("  X : %4d\n", p.x);
    M5Lite.Lcd.printf("  Y : %4d\n", p.y);
  }

  if (M5Lite.BtnA.isPressed()) {
    M5Lite.Ex.setLed(true);
  } else {
    M5Lite.Ex.setLed(false);
  }
  if (M5Lite.BtnB.isPressed()) {
    M5Lite.Ex.setVibration(true);
  } else {
    M5Lite.Ex.setVibration(false);
  }

  // delay & M5Lile.update()
  M5Lite.Ex.delay(100);
}
```
