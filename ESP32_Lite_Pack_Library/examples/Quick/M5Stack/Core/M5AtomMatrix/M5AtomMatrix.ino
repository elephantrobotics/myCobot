#include <M5Atom.h>   // http://librarymanager/All#M5Atom  https://github.com/m5stack/M5Atom
#include <FastLED.h>  // http://librarymanager/All#FastLED https://github.com/FastLED/FastLED

void setup() {
  // 初期化
  M5.begin(true, false, true);  // (Serial, I2C, NeoPixel)
  Wire.begin(25, 21, 10000);    // 内蔵I2C 0x68(MPU6886)

  // GPIO初期化
  pinMode(22, INPUT); // PIN  (INPUT, OUTPUT,       )
  pinMode(19, INPUT); // PIN  (INPUT, OUTPUT,       )
  pinMode(23, INPUT); // PIN  (INPUT, OUTPUT,       )
  pinMode(33, INPUT); // PIN  (INPUT, OUTPUT, ANALOG)
  pinMode(26, INPUT); // GROVE(INPUT, OUTPUT, ANALOG)無線利用時にはANALOG利用不可, DAC出力可
  pinMode(32, INPUT); // GROVE(INPUT, OUTPUT, ANALOG)

  // 内部ピン初期化
  pinMode(12, OUTPUT_OPEN_DRAIN); // IR赤外線(LOWで出力)
  digitalWrite(12, HIGH);

  // LED(0-24)
  for (int i = 0; i < 25; i++) {
    M5.dis.drawpix(i, CRGB::Red);
  }
}

void loop() {
  // ボタンの状態更新
  M5.update();

  if (M5.Btn.wasPressed()) {
    // ボタンが押された
    Serial.println("Btnが押された");
  }

  // ウエイト(1以上推奨)
  delay(1);
}
