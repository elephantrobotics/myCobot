#ifndef __M5LitePower_H__
#define __M5LitePower_H__

#include "I2C_IP5306.h"

#define SLEEP_MSEC(us)  (((uint64_t)us) * 1000L)
#define SLEEP_SEC(us)   (((uint64_t)us) * 1000000L)
#define SLEEP_MIN(us)   (((uint64_t)us) * 60L * 1000000L)
#define SLEEP_HR(us)    (((uint64_t)us) * 60L * 60L * 1000000L)

class M5LitePower
{
  public:
    M5LitePower() {
    }

    void setIP5306(I2C_IP5306 *ip5306) {
      _ip5306 = ip5306;
    }

    bool canControl() {
      return _ip5306->canControl();
    }
    void begin() {
      if (!_ip5306->canControl()) {
        return;
      }

      // 650mA
      _ip5306->setVinMaxCurrent(0x06);

      // 4.2V
      _ip5306->setChargeVolt(0x00);

      // 200mA
      _ip5306->setChargeStopCurrent(0x00);

      // 28mv
      _ip5306->setChargeAddVolt(0x02);

      // VIN
      _ip5306->setChargeCC(0x01);

      enable = true;
    }

    enum ShutdownTime {
      SHUTDOWN_8S = 0,
      SHUTDOWN_16S,
      SHUTDOWN_32S,
      SHUTDOWN_64S
    };

    bool setPowerBoostKeepOn(bool en) {
      if (!enable) {
        return false;
      }
      _ip5306->setBoostOut(en);
      return true;
    }
    bool setAutoBootOnLoad(bool en) {
      if (!enable) {
        return false;
      }
      _ip5306->setBoosOnLoad(en);
      return true;
    }
    bool setLowPowerShutdownTime(ShutdownTime time) {
      if (!enable) {
        return false;
      }
      _ip5306->setLowPowerShutdownTime(time >> 2);
      return true;
    }
    bool setPowerBoostOnOff(bool en) {
      if (!enable) {
        return false;
      }
      _ip5306->setBoostButtonType(en);
      return true;
    }
    bool setPowerBoostSet(bool en) {
      if (!enable) {
        return false;
      }
      _ip5306->setShortBoost(en);
      return true;
    }
    bool setPowerVin(bool en) {
      if (!enable) {
        return false;
      }
      _ip5306->setVin(en);
      return true;
    }
    bool setPowerWLEDSet(bool en) {
      if (!enable) {
        return false;
      }
      _ip5306->setWledButtonType(en);
      return true;
    }
    bool setPowerBtnEn(bool en) {
      if (!enable) {
        return false;
      }
      _ip5306->setBoostButton(en);
      return true;
    }

    bool setVinMaxCurrent(uint8_t cur) {
      if (!enable) {
        return false;
      }
      _ip5306->setVinMaxCurrent(cur);
      return true;
    }
    bool setChargeVolt(uint8_t volt) {
      if (!enable) {
        return false;
      }
      _ip5306->setChargeVolt(volt);
      return true;
    }

    bool setCharge(bool en) {
      if (!enable) {
        return false;
      }
      _ip5306->setCharger(en);
      return true;
    }
    bool isChargeFull() {
      if (!enable) {
        return false;
      }
      return _ip5306->isChargeFull();
    }
    bool isCharging() {
      if (!enable) {
        return false;
      }
      return _ip5306->isCharging();
    }
    int8_t getBatteryLevel() {
      if (!enable) {
        return false;
      }
      return _ip5306->getBatteryLevel();
    }

    void powerOFF() {
      if (!enable) {
        return;
      }
      _ip5306->setBoost(false);
    }

    void reset() {
      esp_restart();
    }

  private:
    uint8_t _wakeupPin;
    I2C_IP5306 *_ip5306;
    bool enable = false;
};
#endif
