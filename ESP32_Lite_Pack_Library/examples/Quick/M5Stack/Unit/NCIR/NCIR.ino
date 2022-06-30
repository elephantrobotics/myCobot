#include <Wire.h>
#include <Adafruit_MLX90614.h> // http://librarymanager/All#Adafruit_MLX90614_shop https://github.com/adafruit/Adafruit-MLX90614-Library

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(115200);
  delay(100);

  Wire.begin(32, 33); // M5StickC

  mlx.begin();
}

void loop() {
  Serial.print(mlx.readAmbientTempC()); // 環境温度
  Serial.print(",");
  Serial.print(mlx.readObjectTempC());  // 物質温度
  Serial.println();

  delay(100);
}
