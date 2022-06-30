#ifndef __M5LiteRTC_H__
#define __M5LiteRTC_H__

#include <Wire.h>
#include "I2C_BM8563.h"

typedef struct {
  uint8_t Hours;
  uint8_t Minutes;
  uint8_t Seconds;
} RTC_TimeTypeDef;

typedef struct {
  uint8_t WeekDay;
  uint8_t Month;
  uint8_t Date;
  uint16_t Year;
} RTC_DateTypeDef;

class M5LiteRTC {
  public:
    void begin(void) {
      if (!enable) {
        return;
      }
      rtc.begin();
    }

    void SetTime(RTC_TimeTypeDef* RTC_TimeStruct) {
      if (!enable) {
        return;
      }
      rtc.setTime((I2C_BM8563_TimeTypeDef*)RTC_TimeStruct);
    }
    void SetData(RTC_DateTypeDef* RTC_DateStruct) {
      if (!enable) {
        return;
      }
      rtc.setDate((I2C_BM8563_DateTypeDef*)RTC_DateStruct);
    }

    void GetTime(RTC_TimeTypeDef* RTC_TimeStruct) {
      if (!enable) {
        memset(RTC_TimeStruct, 0, sizeof(RTC_TimeTypeDef));
        return;
      }
      rtc.getTime((I2C_BM8563_TimeTypeDef*)RTC_TimeStruct);
    }
    void GetData(RTC_DateTypeDef* RTC_DateStruct) {
      if (!enable) {
        memset(RTC_DateStruct, 0, sizeof(RTC_DateTypeDef));
        return;
      }
      rtc.getDate((I2C_BM8563_DateTypeDef*)RTC_DateStruct);
    }

    bool enable = false;

  private:
    I2C_BM8563 rtc = I2C_BM8563(I2C_BM8563_DEFAULT_ADDRESS, Wire1);
};

#endif
