#ifndef __M5LiteEx_H__
#define __M5LiteEx_H__

class M5LiteEx {
  public:
    int board = 0;
    bool useLcd = true;

    M5LiteSound Sound;

    TFT_eSPI *_Lcd;
    M5LiteAXP192 *_Axp;
    M5LiteButton *_BtnA;
    M5LiteButton *_BtnB;
    M5LiteButton *_BtnC;
    M5LiteRTC *_Rtc;
    M5LiteIMU *_Imu;
    M5LiteMPU6886 *_Mpu6886;
    M5LiteSH200Q *_Sh200Q;
    M5LiteCommUtil *_I2C;
    M5LitePower *_Power;
    M5LiteSpeaker *_Beep;
    M5LiteLED *_dis;
    M5LiteDebug *_Debug;
    M5LiteTouch *_Touch;
    Preferences *_preferences;

    void update(void) {
      _Touch->update();
      _BtnA->read();
      _BtnB->read();
      _BtnC->read();
      _Beep->update();
      _Debug->update();
    }

    void delay(unsigned long ms) {
      const unsigned long tick = 50;

      update();

      while (0 < ms) {
        if (tick < ms) {
          ::delay(tick);
          ms -= tick;
        } else {
          ::delay(ms);
          ms = 0;
        }
        update();
      }
    }

    void setLed(bool state) {
      static int8_t now = -1;

      if (now == state) {
        return;
      }
      now = state;

      if (_ledPin == -1) {
        // Non LED
        return;
      } else if (_ledPin < 40) {
        // GPIO
        pinMode(_ledPin, OUTPUT);
        digitalWrite(_ledPin, !state);
      } else if (_ledPin == 100) {
        // AXP192
        _Axp->SetLed(state);
      }
    }

    void setVibration(bool state) {
      static int8_t now = -1;

      if (now == state) {
        return;
      }
      now = state;

      if (_ledPin == 100) {
        // AXP192
        _Axp->SetVibration(state);
      }
    }

    void setPin(int8_t ledPin) {
      _ledPin = ledPin;
    }

    void screenshot(fs::FS &fs, String filename) {
      _Debug->screenshot(fs, filename);
    }

  private:
    int8_t _ledPin;
};

#endif
