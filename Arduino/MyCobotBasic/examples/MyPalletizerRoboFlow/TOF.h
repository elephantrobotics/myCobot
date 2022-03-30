#ifndef TOF_h
#define TOF_h
#include <M5Stack.h>

#define VL53L0X_REG_IDENTIFICATION_MODEL_ID         0xc0
#define VL53L0X_REG_IDENTIFICATION_REVISION_ID      0xc2
#define VL53L0X_REG_PRE_RANGE_CONFIG_VCSEL_PERIOD   0x50
#define VL53L0X_REG_FINAL_RANGE_CONFIG_VCSEL_PERIOD 0x70
#define VL53L0X_REG_SYSRANGE_START                  0x00
#define VL53L0X_REG_RESULT_INTERRUPT_STATUS         0x13
#define VL53L0X_REG_RESULT_RANGE_STATUS             0x14
#define address 0x29  //I2C address

class TOF
{
public:
    uint16_t VL53L0X_decode_vcsel_period(short vcsel_period_reg);
    void read_block_data_at(byte reg, int sz);
    uint16_t read_word_data_at(byte reg);
    byte read_byte_data_at(byte reg);
    byte read_byte_data();
    void write_word_data_at(byte reg, uint16_t data);
    void write_byte_data_at(byte reg, byte data);
    void write_byte_data(byte data);
    uint16_t makeuint16(int lsb, int msb);
    uint16_t bswap(byte b[]);
public:
    byte gbuf[16];

};

#endif