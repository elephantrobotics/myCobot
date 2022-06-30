#ifndef __M5LiteCommUtil_H__
#define __M5LiteCommUtil_H__

class M5LiteCommUtil {
  public:
    M5LiteCommUtil(TwoWire &i2cPort = Wire) {
      _i2cPort = &i2cPort;
    }
    bool writeCommand(uint8_t address, uint8_t subAddress) {
      _i2cPort->beginTransmission(address);
      _i2cPort->write(subAddress);
      uint8_t ret = _i2cPort->endTransmission();
      ESP_LOGD("M5LiteCommUtil", "writeCommand(%02X) = %02X", address, subAddress);
      return (ret == 0);
    }
    bool writeByte(uint8_t address, uint8_t subAddress, uint8_t data) {
      _i2cPort->beginTransmission(address);
      _i2cPort->write(subAddress);
      _i2cPort->write(data);
      uint8_t ret = _i2cPort->endTransmission();
      ESP_LOGD("M5LiteCommUtil", "writeByte(%02X) = %02X", address, subAddress);
      return (ret == 0);
    }
    bool writeBytes(uint8_t address, uint8_t subAddress, uint8_t *data, uint8_t length) {
      _i2cPort->beginTransmission(address);
      _i2cPort->write(subAddress);
      for (int i = 0; i < length; i++) {
        _i2cPort->write(data[i]);
        ESP_LOGD("M5LiteCommUtil", "writeBytes(%02X) = %02X", address + i, data[i]);
      }
      uint8_t ret = _i2cPort->endTransmission();
      return (ret == 0);
    }
    bool readByte(uint8_t address, uint8_t *result) {
      _i2cPort->requestFrom(address, (uint8_t)1);
      *result = _i2cPort->read();

      ESP_LOGD("M5LiteCommUtil", "readByte(%02X) = %02X", address, *result);
      return true;
    }
    bool readByte(uint8_t address, uint8_t subAddress, uint8_t *result) {
      if (writeCommand(address, subAddress)) {
        readByte(address, result);
        return true;
      }
      return false;
    }
    bool readBytes(uint8_t address, uint8_t count, uint8_t *dest) {
      _i2cPort->requestFrom(address, count);
      for (int i = 0; i < count; i++) {
        dest[i] = _i2cPort->read();
        ESP_LOGD("M5LiteCommUtil", "readBytes(%02X) = %02X", address + i, dest[i]);
      }
      return true;
    }
    bool readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest) {
      if (writeCommand(address, subAddress)) {
        readBytes(address, count, dest);
        return true;
      }
      return false;
    }
    void scanID(bool *result) {
      for (int i = 0; i <= 0x7f; i++) {
        result[i] = writeCommand(i, 0x00);
      }
    }

  private:
    TwoWire *_i2cPort;
};

#endif
