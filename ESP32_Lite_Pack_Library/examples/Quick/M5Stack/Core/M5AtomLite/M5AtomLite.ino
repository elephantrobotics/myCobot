#include <M5Atom.h>   // http://librarymanager/All#M5Atom  https://github.com/m5stack/M5Atom
#include <FastLED.h>  // http://librarymanager/All#FastLED https://github.com/FastLED/FastLED

void setup() {
  // 初期化
  M5.begin(true, false, true);  // (Serial, I2C, NeoPixel)

  // GPIO初期化
  pinMode(22, INPUT); // PIN  (INPUT, OUTPUT,       )
  pinMode(19, INPUT); // PIN  (INPUT, OUTPUT,       )
  pinMode(23, INPUT); // PIN  (INPUT, OUTPUT,       )
  pinMode(33, INPUT); // PIN  (INPUT, OUTPUT, ANALOG)
  pinMode(21, INPUT); // PIN  (INPUT, OUTPUT,       )
  pinMode(25, INPUT); // PIN  (INPUT, OUTPUT, ANALOG)無線利用時にはANALOG利用不可
  pinMode(26, INPUT); // GROVE(INPUT, OUTPUT, ANALOG)無線利用時にはANALOG利用不可, DAC出力可
  pinMode(32, INPUT); // GROVE(INPUT, OUTPUT, ANALOG)

  // 内部ピン初期化
  pinMode(12, OUTPUT_OPEN_DRAIN); // IR赤外線(LOWで出力)
  digitalWrite(12, HIGH);

  // LED(0固定)
  M5.dis.drawpix(0, CRGB::Red);
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
