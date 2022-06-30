// @file Adafruit_SGP30.h

#ifndef ADAFRUIT_SGP30_H
#define ADAFRUIT_SGP30_H

#include "Arduino.h"
#include <Wire.h>

// the i2c address
#define SGP30_I2CADDR_DEFAULT 0x58 ///< SGP30 has only one I2C address

// commands and constants
#define SGP30_FEATURESET 0x0020    ///< The required set for this library
#define SGP30_CRC8_POLYNOMIAL 0x31 ///< Seed for SGP30's CRC polynomial
#define SGP30_CRC8_INIT 0xFF       ///< Init value for CRC
#define SGP30_WORD_LEN 2           ///< 2 bytes per word

/*!
 *  @brief  Class that stores state and functions for interacting with
 *          SGP30 Gas Sensor
 */
class Adafruit_SGP30 {
public:
  Adafruit_SGP30();
  boolean begin(TwoWire *theWire = &Wire, boolean initSensor = true);
  boolean softReset();
  boolean IAQinit();
  boolean IAQmeasure();
  boolean IAQmeasureRaw();

  boolean getIAQBaseline(uint16_t *eco2_base, uint16_t *tvoc_base);
  boolean setIAQBaseline(uint16_t eco2_base, uint16_t tvoc_base);
  boolean setHumidity(uint32_t absolute_humidity);

  /** The last measurement of the IAQ-calculated Total Volatile Organic
   *  Compounds in ppb. This value is set when you call {@link IAQmeasure()} **/
  uint16_t TVOC;

  /** The last measurement of the IAQ-calculated equivalent CO2 in ppm. This
   *  value is set when you call {@link IAQmeasure()} **/
  uint16_t eCO2;

  /** The last measurement of the IAQ-calculated equivalent CO2 in ppm. This
   *  value is set when you call {@link IAQmeasureRaw()} **/
  uint16_t rawH2;

  /** The last measurement of the IAQ-calculated equivalent CO2 in ppm. This
   *  value is set when you call {@link IAQmeasureRaw()} **/
  uint16_t rawEthanol;

  /** The 48-bit serial number, this value is set when you call {@link begin()}
   * **/
  uint16_t serialnumber[3];

private:
  TwoWire *_i2c;
  uint8_t _i2caddr;

  void write(uint8_t address, uint8_t *data, uint8_t n);
  void read(uint8_t address, uint8_t *data, uint8_t n);
  boolean readWordFromCommand(uint8_t command[], uint8_t commandLength,
                              uint16_t delay, uint16_t *readdata = NULL,
                              uint8_t readlen = 0);
  uint8_t generateCRC(uint8_t data[], uint8_t datalen);
};
#endif // ndef ADAFRUIT_SGP30_H
