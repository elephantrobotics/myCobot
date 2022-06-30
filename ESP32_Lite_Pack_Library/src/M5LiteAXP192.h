#ifndef __M5LiteAXP192_H__
#define __M5LiteAXP192_H__

#include <I2C_AXP192.h>

class M5LiteAXP192 {
  public:
    void begin(bool disableLDO2 = false, bool disableLDO3 = false, bool disableRTC = false, bool disableDCDC1 = false, bool disableDCDC3 = false) {
      if (!enable) {
        return;
      }

      if (_board == lgfx::board_M5StackCore2) {
        // M5Stack Core2
        writeByte(0x92, 0x00);  // GPIO1 OpenDrain
      } else if (_board == lgfx::board_M5StickC || _board == lgfx::board_M5StickCPlus) {
        // M5StickC
        I2C_AXP192_InitDef initDef = {
          .EXTEN  = true,
          .BACKUP = true,
          .DCDC1  = disableDCDC1 ? -1 : 3300,
          .DCDC2  = 0,
          .DCDC3  = disableDCDC3 ? -1 : -1,
          .LDO2   = disableLDO2  ? -1 : 3000,
          .LDO3   = disableLDO3  ? -1 : 3000,
          .GPIO0  = disableRTC   ? -1 : 2800,
          .GPIO1  = -1,
          .GPIO2  = -1,
          .GPIO3  = -1,
          .GPIO4  = -1,
        };
        _axp192->begin(initDef);
      }
    }

    void setAXP192(I2C_AXP192 *axp192) {
      _axp192 = axp192;
    }

    void setBoard(int board) {
      _board = board;
    }

    void ScreenBreath(uint8_t brightness) {
      if (!enable) {
        return;
      }

      if (brightness > 12) {
        brightness = 12;
      }
      _axp192->setLDO2(1800 + brightness * 100);
    }

    float GetBatVoltage() {
      if (!enable) {
        return 0;
      }
      return _axp192->getBatteryVoltage() / 1000.0;
    }

    float GetBatCurrent() {
      if (!enable) {
        return 0;
      }
      return _axp192->getBatteryChargeCurrent() - _axp192->getBatteryDischargeCurrent();
    }

    float GetVinVoltage() {
      if (!enable) {
        return 0;
      }
      if (_board == lgfx::board_M5StackCore2) {
        return _axp192->getVbusVoltage() / 1000.0;
      } else {
        return _axp192->getAcinVolatge() / 1000.0;
      }
    }

    float GetVinCurrent() {
      if (!enable) {
        return 0;
      }
      if (_board == lgfx::board_M5StackCore2) {
        return _axp192->getVbusCurrent();
      } else {
        return _axp192->getAcinCurrent();
      }
    }

    float GetVBusVoltage() {
      if (!enable) {
        return 0;
      }
      if (_board == lgfx::board_M5StackCore2) {
        return _axp192->getAcinVolatge() / 1000.0;
      } else {
        return _axp192->getVbusVoltage() / 1000.0;
      }
    }

    float GetVBusCurrent() {
      if (!enable) {
        return 0;
      }
      if (_board == lgfx::board_M5StackCore2) {
        return _axp192->getAcinCurrent();
      } else {
        return _axp192->getVbusCurrent();
      }
    }

    float GetTempInAXP192() {
      if (!enable) {
        return 0;
      }
      return _axp192->getInternalTemperature();
    }

    float GetBatPower() {
      if (!enable) {
        return 0;
      }
      return _axp192->getBatteryPower();
    }

    float GetBatChargeCurrent() {
      if (!enable) {
        return 0;
      }
      return _axp192->getBatteryChargeCurrent();
    }

    float GetAPSVoltage() {
      if (!enable) {
        return 0;
      }
      return _axp192->getApsVoltage() / 1000.0;
    }

    void PowerOff() {
      if (!enable) {
        return;
      }
      _axp192->powerOff();
    }

    void SetLed(uint8_t state) {
      if (state) {
        bitOff(0x94, 0x02);
      } else {
        bitOn(0x94, 0x02);
      }
    }

    void SetVibration(uint8_t state) {
      if (!state) {
        bitOff(0x12, 0x08);
      } else {
        bitOn(0x12, 0x08);
      }
    }

    void SetSpkEnable(uint8_t state) {
      if (!state) {
        bitOff(0x94, 0x04);
      } else {
        bitOn(0x94, 0x04);
      }
    }

    uint8_t readByte(uint8_t address) {
      _i2cPort->beginTransmission(_deviceAddress);
      _i2cPort->write(address);
      _i2cPort->endTransmission();
      _i2cPort->requestFrom(_deviceAddress, 1);
      uint8_t val = _i2cPort->read();

      ESP_LOGD("AXP192", "readByte(%02X) = %02X", address, val);
      return val;
    }

    void writeByte(uint8_t address, uint8_t data) {
      _i2cPort->beginTransmission(_deviceAddress);
      _i2cPort->write(address);
      _i2cPort->write(data);
      _i2cPort->endTransmission();
      ESP_LOGD("AXP192", "writeByte(%02X) = %02X", address, data);
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

    int enable = 0;

  private:
    I2C_AXP192 *_axp192;
    int _board;

    TwoWire *_i2cPort = &Wire1;
    int _deviceAddress = 0x34;
};

#endif
