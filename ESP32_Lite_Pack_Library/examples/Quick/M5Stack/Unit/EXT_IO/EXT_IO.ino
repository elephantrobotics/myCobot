#include <TCA9534.h>  // http://librarymanager/All#TCA9534 https://github.com/hideakitai/TCA9534

TCA9534 ioex;
const uint8_t IOEX_ADDR = 0x27;

void setup()
{
  Serial.begin(115200);
  delay(2000);

  Wire.begin(32, 33);

  ioex.attach(Wire);
  ioex.setDeviceAddress(IOEX_ADDR);
  ioex.config(TCA9534::Config::IN);
  //ioex.polarity(TCA9534::Polarity::INVERSE);

  Serial.print("config  : ");
  Serial.println(ioex.config(), HEX);
  Serial.print("polarity: ");
  Serial.println(ioex.polarity(), HEX);
}

void loop()
{
  for (int i = 0; i < 8; i++) {
    uint8_t raw = ioex.input(i);
    Serial.print(raw != 0);
  }
  Serial.println();
  delay(1000);
}
