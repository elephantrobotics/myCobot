#ifndef __I2C_SH200Q_H__
#define __I2C_SH200Q_H__

#include <Wire.h>

#define I2C_SH200Q_DEFAULT_ADDRESS 0x6C

class I2C_SH200Q {
  public:
    I2C_SH200Q(uint8_t deviceAddress = I2C_SH200Q_DEFAULT_ADDRESS, TwoWire &i2cPort = Wire) {
      _deviceAddress = deviceAddress;
      _i2cPort = &i2cPort;
    }

    int begin(void) {
      // WHO_AM_I : IMU Check
      if (WhoAmI() != 0x18) {
        return -1;
      }
      delay(1);

      bitOn(0xC2, 0x04);
      delay(1);

      bitOff(0xC2, 0x04);
      delay(1);

      bitOn(0xD8, 0x80);
      delay(1);

      bitOff(0xD8, 0x80);
      delay(1);

      writeByte(0x78, 0x61);
      delay(1);

      writeByte(0x78, 0x00);
      delay(1);

      // ACC_CONFIG(0x0E) : 256Hz
      writeByte(0x0E, 0x91);
      delay(1);

      // GYRO_CONFIG(0x0F) : 500Hz
      writeByte(0x0F, 0x13);
      delay(1);

      // GYRO_DLPF(0x11) : 50Hz
      writeByte(0x11, 0x03);
      delay(1);

      // FIFO_CONFIG(0x12)
      writeByte(0x12, 0x00);
      delay(1);

      // ACC_RANGE(0x16) : +-8G
      writeByte(0x16, 0x01);
      delay(1);

      // GYRO_RANGE(0x2B) : +-2000
      writeByte(0x2B, 0x00);
      delay(1);

      // REG_SET1(0xBA)
      writeByte(0xBA, 0xC0);
      delay(1);

      // REG_SET2(0xCA)
      bitOn(0xCA, 0x10);
      delay(1);

      // REG_SET2(0xCA)
      bitOff(0xCA, 0x10);
      delay(1);

      return 0;
    }

    uint8_t WhoAmI() {
      return readByte(0x30);
    }

    void getAccel(float* ax, float* ay, float* az) {
      float aRes = 8.0 / 32768.0;
      *ax = (int16_t)((readByte(0x01) << 8) | readByte(0x00)) * aRes;
      *ay = (int16_t)((readByte(0x03) << 8) | readByte(0x02)) * aRes;
      *az = (int16_t)((readByte(0x05) << 8) | readByte(0x04)) * aRes;
    }
    void getGyro(float* gx, float* gy, float* gz) {
      float gRes = 2000.0 / 32768.0;
      *gx = (int16_t)((readByte(0x07) << 8) | readByte(0x06)) * gRes;
      *gy = (int16_t)((readByte(0x09) << 8) | readByte(0x08)) * gRes;
      *gz = (int16_t)((readByte(0x0b) << 8) | readByte(0x0a)) * gRes;
    }
    void getTemp(float *t) {
      *t = 21.0 + ((readByte(0x0d) << 8) | readByte(0x0c)) / 333.87;
    }

  private:
    uint8_t readByte(uint8_t address) {
      _i2cPort->beginTransmission(_deviceAddress);
      _i2cPort->write(address);
      _i2cPort->endTransmission();
      _i2cPort->requestFrom(_deviceAddress, 1);
      uint8_t val = _i2cPort->read();

      ESP_LOGD("SH200Q", "readByte(%02X) = %02X", address, val);
      return val;
    }
    void writeByte(uint8_t address, uint8_t data) {
      _i2cPort->beginTransmission(_deviceAddress);
      _i2cPort->write(address);
      _i2cPort->write(data);
      _i2cPort->endTransmission();
      ESP_LOGD("SH200Q", "writeByte(%02X) = %02X", address, data);
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
