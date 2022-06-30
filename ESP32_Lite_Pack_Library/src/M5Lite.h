#ifndef __M5Lite_H__
#define __M5Lite_H__

#include <Arduino.h>
#include <core_version.h>
#include <Wire.h>
#include <SPI.h>
#include "FS.h"
#include "SD.h"
#include "SPIFFS.h"
#include <Preferences.h>
#include "nvs_flash.h"
#include "lwip/sockets.h"

#define LGFX_M5STACK          // M5Stack (Basic / Gray / Go / Fire)
#define LGFX_M5STACKCORE2     // M5StackCore2
#define LGFX_M5STICKC         // M5Stick C / CPlus
#define LGFX_TTGO_TWATCH      // TTGO T-Watch
#include <LGFX_TFT_eSPI.hpp>  // https://github.com/lovyan03/LovyanGFX
#include "M5LiteAXP192.h"
#include "M5LiteRTC.h"
#include "M5LiteTouch.h"
#include "M5LiteButton.h"
#include "M5LiteIMU.h"
#include "M5LiteMPU6886.h"
#include "M5LiteSH200Q.h"
#include "M5LitePower.h"
#include "M5LiteCommUtil.h"
#include "M5LiteSpeaker.h"
#include "M5LiteLED.h"
#include "M5LiteSound.h"
#include "M5LiteDebug.h"
#include "M5LiteEx.h"

// Color
#define BLACK               0x0000
#define NAVY                0x000F
#define DARKGREEN           0x03E0
#define DARKCYAN            0x03EF
#define MAROON              0x7800
#define PURPLE              0x780F
#define OLIVE               0x7BE0
#define LIGHTGREY           0xC618
#define DARKGREY            0x7BEF
#define BLUE                0x001F
#define GREEN               0x07E0
#define CYAN                0x07FF
#define RED                 0xF800
#define MAGENTA             0xF81F
#define YELLOW              0xFFE0
#define WHITE               0xFFFF
#define ORANGE              0xFD20
#define GREENYELLOW         0xAFE5
#define PINK                0xF81F

// Config
uint8_t M5_IR             = -1;
uint8_t M5_LED            = -1;
uint8_t BUTTON_A_PIN      = -1;
uint8_t BUTTON_B_PIN      = -1;
uint8_t BUTTON_C_PIN      = -1;
uint8_t SPEAKER_PIN       = -1;
uint8_t TONE_PIN_CHANNEL  = -1;
uint8_t TFCARD_CS_PIN     = -1;

class M5LiteBase {
  public:
    void begin(bool LCDEnable = true, bool PowerEnable = true, bool SerialEnable = true) {
      // UART
      if (SerialEnable) {
        Serial.begin(115200);
        Serial.flush();
        delay(200);
      }

      Serial.println("===============================================================");
      Serial.println("M5Lite Initializing");
      Serial.println("===============================================================");
      Serial.printf ("ESP32                 : %s\n", ARDUINO_ESP32_RELEASE);

      Axp.setAXP192(&axp192);
      Mpu6886.setMPU6886(&mpu6886);
      Sh200Q.setSH200Q(&sh200q);
      Imu.setMPU6886(&mpu6886);
      Imu.setSH200Q(&sh200q);
      Imu.setBMA423(&bma423);
      Power.setIP5306(&ip5306);
      BtnC.setAXP192(&axp192);
      BtnA.setTouch(&Touch);
      BtnB.setTouch(&Touch);
      BtnC.setTouch(&Touch);

      // LCD INIT
      if (LCDEnable) {
        Lcd.begin();
        Ex.board = (int)Lcd.getBoard();
        Imu.board = Ex.board;
        if (Ex.board == lgfx::board_M5Stack) {
          // M5Stack
          M5_IR             = -1;
          M5_LED            = -1;
          BUTTON_A_PIN      = 39;
          BUTTON_B_PIN      = 38;
          BUTTON_C_PIN      = 37;
          SPEAKER_PIN       = 25;
          TONE_PIN_CHANNEL  =  0;
          TFCARD_CS_PIN     =  4;

          Ex.Sound.begin();
          SD.begin(TFCARD_CS_PIN, SPI, 20000000);

          Wire1.begin(21, 22);
        } else if (Ex.board == lgfx::board_M5StackCore2) {
          // M5Stack Core2
          M5_IR             = -1;
          M5_LED            = 100;
          BUTTON_A_PIN      = 101;
          BUTTON_B_PIN      = 102;
          BUTTON_C_PIN      = 103;
          SPEAKER_PIN       = -1;
          TONE_PIN_CHANNEL  =  0;
          TFCARD_CS_PIN     =  4;

          Axp.enable = true;
          Rtc.enable = true;
          Touch.enable = true;

          Ex.Sound.begin();
          SD.begin(TFCARD_CS_PIN, SPI, 20000000);

          Wire1.begin(21, 22);
        } else if (Ex.board == lgfx::board_M5StickC) {
          // M5StickC
          M5_IR             =  9;
          M5_LED            = 10;
          BUTTON_A_PIN      = 37;
          BUTTON_B_PIN      = 39;
          BUTTON_C_PIN      = 100;
          SPEAKER_PIN       = -1;
          TONE_PIN_CHANNEL  = -1;
          TFCARD_CS_PIN     = -1;

          Axp.enable = true;
          Rtc.enable = true;

          Wire1.begin(21, 22);
        } else if (Ex.board == lgfx::board_M5StickCPlus) {
          // M5StickC Plus
          M5_IR             =  9;
          M5_LED            = 10;
          BUTTON_A_PIN      = 37;
          BUTTON_B_PIN      = 39;
          BUTTON_C_PIN      = 100;
          SPEAKER_PIN       =  2;
          TONE_PIN_CHANNEL  =  0;
          TFCARD_CS_PIN     = -1;

          Axp.enable = true;
          Rtc.enable = true;

          Wire1.begin(21, 22);
        } else if (Ex.board == lgfx::board_TTGO_TWatch) {
          // TTGO T-Watch
          M5_IR             = -1;
          M5_LED            = -1;
          BUTTON_A_PIN      = 36;
          BUTTON_B_PIN      = -1;
          BUTTON_C_PIN      = -1;
          SPEAKER_PIN       = -1;
          TONE_PIN_CHANNEL  = -1;
          TFCARD_CS_PIN     = -1;

          Rtc.enable = true;

          Wire1.begin(21, 22);
        } else if (Ex.board == lgfx::board_unknown) {
          // ATOM
          M5_IR             = 12;
          M5_LED            = -1;
          BUTTON_A_PIN      = 39;
          BUTTON_B_PIN      = -1;
          BUTTON_C_PIN      = -1;
          SPEAKER_PIN       = -1;
          TONE_PIN_CHANNEL  = -1;
          TFCARD_CS_PIN     = -1;

          // LCD not use
          Ex.useLcd = false;

          // LED start
          dis.begin();

          // I2C Init
          Wire1.begin(25, 21, 10000);
        } else {
          // Other
          Wire1.begin(-1, -1);
        }
      } else {
        Wire1.begin(21, 22);
      }

      // Power
      if (PowerEnable) {
        Axp.setBoard(Ex.board);
        Axp.begin();
        if (Ex.useLcd) {
          Lcd.drawPixel(0, 0, 0x0000);
          Lcd.clear();
        }
      }

      Rtc.begin();

      BtnA.begin(BUTTON_A_PIN, true, DEBOUNCE_MS);
      BtnB.begin(BUTTON_B_PIN, true, DEBOUNCE_MS);
      BtnC.begin(BUTTON_C_PIN, true, DEBOUNCE_MS);

      Beep.setPin(SPEAKER_PIN, TONE_PIN_CHANNEL);

      Ex.Sound.setAXP(&Axp);
      Ex.Sound.setBoard(Ex.board);

      Debug._Lcd = &Lcd;
      Debug._Axp = &Axp;
      Debug._BtnA = &BtnA;
      Debug._BtnB = &BtnB;
      Debug._BtnC = &BtnC;
      Debug._Rtc = &Rtc;
      Debug._Imu = &Imu;
      Debug._Mpu6886 = &Mpu6886;
      Debug._Sh200Q = &Sh200Q;
      Debug._I2C = &I2C;
      Debug._Power = &Power;
      Debug._Beep = &Beep;
      Debug._dis = &dis;
      Debug._Touch = &Touch;
      Debug._preferences = &preferences;
      Ex._Lcd = &Lcd;
      Ex._Axp = &Axp;
      Ex._BtnA = &BtnA;
      Ex._BtnB = &BtnB;
      Ex._BtnC = &BtnC;
      Ex._Rtc = &Rtc;
      Ex._Imu = &Imu;
      Ex._Mpu6886 = &Mpu6886;
      Ex._Sh200Q = &Sh200Q;
      Ex._I2C = &I2C;
      Ex._Power = &Power;
      Ex._Beep = &Beep;
      Ex._dis = &dis;
      Ex._Touch = &Touch;
      Ex._Debug = &Debug;
      Ex._preferences = &preferences;

      Ex.setPin(M5_LED);
      Ex.setLed(false);

      Touch.setLcd(&Lcd);

      Imu.Init();

      // Mac Address
      uint8_t mac[6];
      esp_read_mac(mac, ESP_MAC_WIFI_STA);
      Serial.printf ("Mac Address           : %02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

      // Board
      Serial.printf ("Board                 : ");
      if (Imu.board == lgfx::board_M5Stack) {
        // M5Stack
        Serial.println("M5Stack");
      } else if (Imu.board == lgfx::board_M5StackCore2) {
        // M5Stack Core2
        Serial.println("M5Stack Core2");
      } else if (Imu.board == lgfx::board_M5StickC) {
        // M5StickC
        Serial.println("M5StickC");
      } else if (Imu.board == lgfx::board_M5StickCPlus) {
        // M5StickC Plus
        Serial.println("M5StickC Plus");
      } else if (Imu.board == lgfx::board_TTGO_TWatch) {
        // TTGO T-Watch
        Serial.println("LILYGO TTGO T-Watch");
      } else if (Imu.board == lgfx::board_unknown) {
        // ATOM
        Serial.println("M5Stack ATOM");
      }

      // LCD
      int width = Lcd.width();
      int height = Lcd.height();
      if (0 < width) {
        Serial.printf ("LCD                   : Width:%d, Height:%d\n", width, height);
      } else {
        Serial.printf ("LCD                   : (NONE)\n");
      }

      // Touch
      if (Touch.enable) {
        Serial.printf ("Touch                 : Enable\n");
      } else {
        Serial.printf ("Touch                 : (NONE)\n");
      }

      // AXP192
      if (Axp.enable) {
        Serial.printf ("AXP192                : Enable\n");
      } else {
        Serial.printf ("AXP192                : (NONE)\n");
      }

      // IMU
      Serial.printf ("IMU                   : ");
      if (Imu.imuType == M5LiteIMU::IMU_UNKNOWN) {
        Serial.println("(NONE)");
      } else if (Imu.imuType == M5LiteIMU::IMU_SH200Q) {
        Serial.println("SH200Q(6-AXIS)");
      } else if (Imu.imuType == M5LiteIMU::IMU_MPU6886) {
        Serial.println("MPU6886(6-AXIS)");
      } else if (Imu.imuType == M5LiteIMU::IMU_BMA423) {
        Serial.println("BMA423(3-AXIS:ACCEL)");
      }

      // RTC
      if (Rtc.enable) {
        RTC_TimeTypeDef RTC_TimeStruct;
        RTC_DateTypeDef RTC_DateStruct;
        Rtc.GetTime(&RTC_TimeStruct);
        Rtc.GetData(&RTC_DateStruct);
        struct tm dt;
        dt.tm_year = RTC_DateStruct.Year - 1900;
        dt.tm_mon = RTC_DateStruct.Month - 1;
        dt.tm_mday  = RTC_DateStruct.Date;
        dt.tm_hour = RTC_TimeStruct.Hours;
        dt.tm_min  = RTC_TimeStruct.Minutes;
        dt.tm_sec  = RTC_TimeStruct.Seconds;
        struct timeval tv;
        tv.tv_sec = mktime(&dt);
        struct timezone tz;
        tz.tz_minuteswest = 9 * 60; // Jp
        tz.tz_dsttime = 0;
        settimeofday(&tv, &tz);

        Serial.printf ("RTC                   : ");
        Serial.printf ("%04d-%02d-%02d ", RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date);
        Serial.printf ("%02d:%02d:%02d\n", RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);
      } else {
        Serial.printf ("RTC                   : (NONE)\n");
      }

      Serial.printf ("Local Time            : ");
      time_t t = time(NULL);
      struct tm *t_st;
      t_st = localtime(&t);
      Serial.printf ("%04d-%02d-%02d ", t_st->tm_year + 1900, t_st->tm_mon + 1, t_st->tm_mday);
      Serial.printf ("%02d:%02d:%02d\n", t_st->tm_hour, t_st->tm_min, t_st->tm_sec);

      if(!SPIFFS.begin()){
        Lcd.fillScreen(TFT_RED);
        Lcd.println("SPIFFS Format ... (please wait)");
        Serial.print("SPIFFS Format ... (please wait)");
        delay(100);
        SPIFFS.format();
        Serial.println("Down");
        ESP.restart();
      }
      uint32_t totalBytes = SPIFFS.totalBytes();
      uint32_t usedBytes = SPIFFS.usedBytes();
      String sizeString = Debug.fileSizeString(totalBytes);
      Serial.printf("SPIFFS Total Bytes    : %10s\n", sizeString.c_str());
      sizeString = Debug.fileSizeString(usedBytes);
      Serial.printf("SPIFFS Used Bytes     : %10s\n", sizeString.c_str());

      if (SerialEnable) {
        Serial.println();
        Serial.println("Initializing ... Down\n");
      }
    }

    void update() {
      Ex.update();
    }

    TFT_eSPI Lcd;
    M5LiteAXP192 Axp = M5LiteAXP192();

    M5LiteButton BtnA;
    M5LiteButton BtnB;
    M5LiteButton BtnC;

    M5LiteRTC Rtc;

    M5LiteIMU Imu;
    M5LiteMPU6886 Mpu6886;
    M5LiteSH200Q Sh200Q;

    M5LiteCommUtil I2C = M5LiteCommUtil(Wire);
    M5LitePower Power;
    M5LiteSpeaker Beep;
    M5LiteLED dis;
    M5LiteTouch Touch;

    M5LiteDebug Debug;
    M5LiteEx Ex;

  private:
    const uint32_t DEBOUNCE_MS = 10;
    I2C_MPU6886 mpu6886 = I2C_MPU6886(I2C_MPU6886_DEFAULT_ADDRESS, Wire1);
    I2C_SH200Q sh200q = I2C_SH200Q(I2C_SH200Q_DEFAULT_ADDRESS, Wire1);
    I2C_BMA423 bma423 = I2C_BMA423(I2C_BMA423_DEFAULT_ADDRESS, Wire1);
    I2C_AXP192 axp192 = I2C_AXP192(I2C_AXP192_DEFAULT_ADDRESS, Wire1);
    I2C_IP5306 ip5306 = I2C_IP5306(I2C_IP5306_DEFAULT_ADDRESS, Wire1);
    Preferences preferences = Preferences();
};

M5LiteBase M5Lite;
#define M5 M5Lite

#endif
