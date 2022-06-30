#include <M5Lite.h>

TwoWire *i2cWire;

uint8_t sda = -1;
uint8_t scl = -1;
uint8_t i2cMode = 0;

void updateI2c() {
  if (M5.Ex.board == lgfx::board_M5Stack) {
    i2cMode = 0;

    // Internal
    sda = 21;
    scl = 22;
    i2cWire = &Wire1;
  } else if (M5.Ex.board == lgfx::board_M5StackCore2) {
    // M5Stack Core2
    if (i2cMode == 1) {
      // GROVE
      sda = 32;
      scl = 33;
      Wire.begin(sda, scl);
      i2cWire = &Wire;
    } else {
      i2cMode = 0;

      // Internal
      sda = 21;
      scl = 22;
      i2cWire = &Wire1;
    }
  } else if (M5.Ex.board == lgfx::board_M5StickC || M5.Ex.board == lgfx::board_M5StickCPlus) {
    // M5StickC
    if (i2cMode == 1) {
      // GROVE
      sda = 32;
      scl = 33;
      Wire.begin(sda, scl);
      i2cWire = &Wire;
    } else if (i2cMode == 2) {
      // PIN Header
      sda = 0;
      scl = 26;
      Wire.begin(sda, scl);
      i2cWire = &Wire;
    } else {
      i2cMode = 0;

      // Internal
      sda = 21;
      scl = 22;
      i2cWire = &Wire1;
    }
  } else if (M5.Ex.board == lgfx::board_TTGO_TWatch) {
    i2cMode = 0;

    // Internal
    sda = 21;
    scl = 22;
    i2cWire = &Wire1;
  } else if (M5.Ex.board == lgfx::board_unknown) {
    // ATOM
    if (i2cMode == 1) {
      // GROVE
      sda = 26;
      scl = 32;
      Wire.begin(sda, scl);
      i2cWire = &Wire;
    } else {
      i2cMode = 0;

      // Internal
      sda = 21;
      scl = 25;
      i2cWire = &Wire1;
    }
  }
}

void setup() {
  M5.begin();
  M5.Lcd.fillScreen(BLACK);
}

void loop() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);

  M5.Lcd.printf("I2C Scan\n");
  Serial.printf("===================\n");
  Serial.printf("I2C Scan\n");

  i2cMode = 0;
  updateI2c();

  while (1) {
    M5.Lcd.println();
    M5.Lcd.printf("SDA:%2d SCL:%2d\n", sda, scl);
    Serial.println();
    Serial.printf("SDA:%2d SCL:%2d\n", sda, scl);

    for (byte address = 0; address <= 127; address++) {
      i2cWire->beginTransmission(address);
      byte error = i2cWire->endTransmission();
      if (error == 0) {
        M5.Lcd.printf("%02X ", address);
        Serial.printf("%02X ", address);
      } else {
        if (240 <= M5.Lcd.width()) {
          M5.Lcd.print(".. ");
          if (address % 16 == 15) {
            M5.Lcd.println();
          }
        }
      }
      delay(1);
    }

    M5.Lcd.println();
    Serial.println();

    i2cMode++;
    updateI2c();
    if (i2cMode == 0) {
      break;
    }
  }

  delay(3000);
}
