#ifndef __I2C_IP5306_H__
#define __I2C_IP5306_H__

#include <Wire.h>

#define I2C_IP5306_DEFAULT_ADDRESS 0x75

class I2C_IP5306 {
  public:
    I2C_IP5306(uint8_t deviceAddress = I2C_IP5306_DEFAULT_ADDRESS, TwoWire &i2cPort = Wire) {
      _deviceAddress = deviceAddress;
      _i2cPort = &i2cPort;
    }

    bool canControl() {
      _i2cPort->beginTransmission(_deviceAddress);
      _i2cPort->write(0x70);
      uint8_t ret = _i2cPort->endTransmission();
      return (ret == 0);
    }
    int begin(void) {
      return !canControl();
    }

    void setBoost(bool enable) {
      if (enable) {
        bitOn(0x00, 1 << 5);
      } else {
        bitOff(0x00, 1 << 5);
      }
    }
    void setCharger(bool enable) {
      if (enable) {
        bitOn(0x00, 1 << 4);
      } else {
        bitOff(0x00, 1 << 4);
      }
    }
    void setBoosOnLoad(bool enable) {
      if (enable) {
        bitOn(0x00, 1 << 2);
      } else {
        bitOff(0x00, 1 << 2);
      }
    }
    void setBoostOut(bool enable) {
      if (enable) {
        bitOn(0x00, 1 << 1);
      } else {
        bitOff(0x00, 1 << 1);
      }
    }
    void setBoostButton(bool enable) {
      if (enable) {
        bitOn(0x00, 1 << 0);
      } else {
        bitOff(0x00, 1 << 0);
      }
    }
    void setBoostButtonType(bool enable) {
      if (enable) {
        bitOn(0x01, 1 << 7);
      } else {
        bitOff(0x01, 1 << 7);
      }
    }
    void setWledButtonType(bool enable) {
      if (enable) {
        bitOn(0x01, 1 << 6);
      } else {
        bitOff(0x01, 1 << 6);
      }
    }
    void setShortBoost(bool enable) {
      if (enable) {
        bitOn(0x01, 1 << 5);
      } else {
        bitOff(0x01, 1 << 5);
      }
    }
    void setVin(bool enable) {
      if (enable) {
        bitOn(0x01, 1 << 2);
      } else {
        bitOff(0x01, 1 << 2);
      }
    }
    void setLowBatteryShutdown(bool enable) {
      if (enable) {
        bitOn(0x01, 1 << 0);
      } else {
        bitOff(0x01, 1 << 0);
      }
    }
    void setLowPowerShutdownTime(uint8_t set) {
      uint8_t val = readByte(0x02);
      val = ( val & ~(1 << 2 | 1 << 3) ) | ((set & 0x03) << 2);
      writeByte(0x02, val);
    }
    void setChargeVolt(uint8_t set) {
      uint8_t val = readByte(0x20);
      val = ( val & ~(1 << 0 | 1 << 1) ) | ((set & 0x03) << 0);
      writeByte(0x20, val);
    }
    void setChargeStopCurrent(uint8_t set) {
      uint8_t val = readByte(0x21);
      val = ( val & ~(1 << 6 | 1 << 7) ) | ((set & 0x03) << 6);
      writeByte(0x21, val);
    }
    void setChargeAddVolt(uint8_t set) {
      uint8_t val = readByte(0x22);
      val = ( val & ~(1 << 0 | 1 << 1) ) | ((set & 0x03) << 0);
      writeByte(0x22, val);
    }
    void setChargeCC(uint8_t set) {
      uint8_t val = readByte(0x23);
      val = ( val & ~(1 << 5) ) | ((set & 0x01) << 5);
      writeByte(0x23, val);
    }
    void setVinMaxCurrent(uint8_t set) {
      uint8_t val = readByte(0x24);
      val = ( val & ~(1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4) ) | ((set & 0x1F) << 0);
      writeByte(0x24, val);
    }
    bool isCharging() {
      uint8_t val = readByte(0x70);
      return val & (1 << 3);
    }
    bool isChargeFull() {
      uint8_t val = readByte(0x71);
      return val & (1 << 3);
    }
    bool isLightLoad() {
      uint8_t val = readByte(0x72);
      return val & (1 << 2);
    }
    int8_t getBatteryLevel() {
      uint8_t val = readByte(0x78);
      if (val & 0x10) {
        return 0;
      }
      if (val & 0x20) {
        return 25;
      }
      if (val & 0x40) {
        return 50;
      }
      if (val & 0x80) {
        return 75;
      }
      return 100;
    }

  private:
    uint8_t readByte(uint8_t address) {
      _i2cPort->beginTransmission(_deviceAddress);
      _i2cPort->write(address);
      _i2cPort->endTransmission();
      _i2cPort->requestFrom(_deviceAddress, 1);
      uint8_t val = _i2cPort->read();

      ESP_LOGD("IP5306", "readByte(%02X, %02X) = %02X", _deviceAddress, address, val);
      return val;
    }
    void writeByte(uint8_t address, uint8_t data) {
      _i2cPort->beginTransmission(_deviceAddress);
      _i2cPort->write(address);
      _i2cPort->write(data);
      _i2cPort->endTransmission();
      ESP_LOGD("IP5306", "writeByte(%02X, %02X) = %02X", _deviceAddress, address, data);
    }
    void writeBytes(uint8_t address, const uint8_t *data, uint8_t len) {
      _i2cPort->beginTransmission(_deviceAddress);
      _i2cPort->write(address);
      _i2cPort->write(data, len);
      _i2cPort->endTransmission();
      ESP_LOGD("IP5306", "writeByte(%02X, %02X, len=%d) = %02X", _deviceAddress, address, len, data[0]);
    }
    void bitOn(uint8_t address, uint8_t bit) {
      uint8_t add = address;
      uint8_t val = readByte(add) | bit;
      writeByte(add, val);
    }
    void bitOff(uint8_t address, uint8_t bit) {
      uint8_t add = address;
      uint8_t val = readByte(add) & ~bit;
      writeByte(add, val);
    }

    TwoWire *_i2cPort;
    int _deviceAddress;
};

#endif
