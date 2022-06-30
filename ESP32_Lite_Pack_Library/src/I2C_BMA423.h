#ifndef __I2C_BMA423_H__
#define __I2C_BMA423_H__

#include <Wire.h>
#include "I2C_BMA423_config.h"

#define I2C_BMA423_DEFAULT_ADDRESS 0x19

class I2C_BMA423 {
  public:
    I2C_BMA423(uint8_t deviceAddress = I2C_BMA423_DEFAULT_ADDRESS, TwoWire &i2cPort = Wire) {
      _deviceAddress = deviceAddress;
      _i2cPort = &i2cPort;
    }

    int begin(void) {
      // Reset
      writeByte(0x7E, 0xB6);
      delay(1);

      // WHO_AM_I : IMU Check
      if (WhoAmI() != 0x13) {
        return -1;
      }
      delay(1);

      writeByte(0x7C, 0x02);
      delay(1);

      writeByte(0x59, 0x00);
      delay(1);

      int len = 8;
      for (int i = 0; i < sizeof(_bma423_config_data); i += len) {
        uint8_t asic_msb = (uint8_t)((i / 2) >> 4);
        uint8_t asic_lsb = ((i / 2) & 0x0F);
        writeByte(0x5B, asic_lsb);
        writeByte(0x5C, asic_msb);
        writeBytes(0x5E, &_bma423_config_data[i], len);
      }

      writeByte(0x59, 0x01);
      delay(1);

      writeByte(0x7C, 0x03);
      delay(1);

      writeByte(0x53, 0x0A);
      delay(1);

      writeByte(0x40, 0xA8);
      delay(1);

      writeByte(0x41, 0x00);
      delay(1);

      // Enable Accel
      writeByte(0x7D, 0x04);
      delay(1);

      return 0;
    }

    uint8_t WhoAmI() {
      return readByte(0x00);
    }

    void getAccel(float* ax, float* ay, float* az) {
      *ax = (int16_t)((readByte(0x13) << 8) | readByte(0x12)) / 0x10 / 1000.0;
      *ay = (int16_t)((readByte(0x15) << 8) | readByte(0x14)) / 0x10 / 1000.0;
      *az = (int16_t)((readByte(0x17) << 8) | readByte(0x16)) / 0x10 / 1000.0;
    }

  private:
    uint8_t readByte(uint8_t address) {
      _i2cPort->beginTransmission(_deviceAddress);
      _i2cPort->write(address);
      _i2cPort->endTransmission();
      _i2cPort->requestFrom(_deviceAddress, 1);
      uint8_t val = _i2cPort->read();

      ESP_LOGD("BMA423", "readByte(%02X, %02X) = %02X", _deviceAddress, address, val);
      return val;
    }
    void writeByte(uint8_t address, uint8_t data) {
      _i2cPort->beginTransmission(_deviceAddress);
      _i2cPort->write(address);
      _i2cPort->write(data);
      _i2cPort->endTransmission();
      ESP_LOGD("BMA423", "writeByte(%02X, %02X) = %02X", _deviceAddress, address, data);
    }
    void writeBytes(uint8_t address, const uint8_t *data, uint8_t len) {
      _i2cPort->beginTransmission(_deviceAddress);
      _i2cPort->write(address);
      _i2cPort->write(data, len);
      _i2cPort->endTransmission();
      ESP_LOGD("BMA423", "writeByte(%02X, %02X, len=%d) = %02X", _deviceAddress, address, len, data[0]);
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
