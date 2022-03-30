#include "TOF.h"
uint16_t TOF::bswap(byte b[])
{
    // Big Endian unsigned short to little endian unsigned short
    uint16_t val = ((b[0] << 8) & b[1]);
    return val;
}

uint16_t TOF::makeuint16(int lsb, int msb)
{
    return ((msb & 0xFF) << 8) | (lsb & 0xFF);
}

void TOF::write_byte_data(byte data)
{
    Wire.beginTransmission(address);
    Wire.write(data);
    Wire.endTransmission();
}

void TOF::write_byte_data_at(byte reg, byte data)
{
    // write data word at address and register
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
}

void TOF::write_word_data_at(byte reg, uint16_t data)
{
    // write data word at address and register
    byte b0 = (data & 0xFF);
    byte b1 = ((data >> 8) && 0xFF);

    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(b0);
    Wire.write(b1);
    Wire.endTransmission();
}

byte TOF::read_byte_data()
{
    Wire.requestFrom(address, 1);
    while (Wire.available() < 1) delay(1);
    byte b = Wire.read();
    return b;
}

byte TOF::read_byte_data_at(byte reg)
{
    //write_byte_data((byte)0x00);
    write_byte_data(reg);
    Wire.requestFrom(address, 1);
    while (Wire.available() < 1) delay(1);
    byte b = Wire.read();
    return b;
}

uint16_t TOF::read_word_data_at(byte reg)
{
    write_byte_data(reg);
    Wire.requestFrom(address, 2);
    while (Wire.available() < 2) delay(1);
    gbuf[0] = Wire.read();
    gbuf[1] = Wire.read();
    return bswap(gbuf);
}

void TOF::read_block_data_at(byte reg, int sz)
{
    int i = 0;
    write_byte_data(reg);
    Wire.requestFrom(address, sz);
    for (i = 0; i < sz; i++) {
        while (Wire.available() < 1) delay(1);
        gbuf[i] = Wire.read();
    }
}


uint16_t TOF::VL53L0X_decode_vcsel_period(short vcsel_period_reg)
{
    // Converts the encoded VCSEL period register value into the real
    // period in PLL clocks
    uint16_t vcsel_period_pclks = (vcsel_period_reg + 1) << 1;
    return vcsel_period_pclks;
}
