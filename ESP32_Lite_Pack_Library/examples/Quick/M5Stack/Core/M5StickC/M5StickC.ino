#include <M5StickC.h> // http://librarymanager/All#M5StickC https://github.com/m5stack/M5StickC

void setup() {
  // 初期化
  M5.begin();
  M5.Axp.ScreenBreath(12);            // 明るさ(7-12)
  M5.Lcd.setRotation(0);              // 画面方向(0:縦, 1:ボタンB上, 2:逆さ, 3:ボタンB下)
  M5.Lcd.setTextSize(1);              // 文字サイズ(1-7) 元の高さの倍数
  M5.Lcd.setTextColor(WHITE, BLACK);  // (文字色, 背景色)同じ色を指定すると背景色無し
  M5.Lcd.fillScreen(BLACK);           // 塗りつぶし

  // GPIO初期化
  pinMode(26, INPUT); // PIN  (INPUT, OUTPUT, ANALOG)無線利用時にはANALOG利用不可, DAC出力可
  pinMode(36, INPUT); // PIN  (INPUT,       , ANALOG)入力専用、INPUT_PULLUP等も不可
  pinMode( 0, INPUT); // PIN  (INPUT, OUTPUT,       )外部回路でプルアップ済み
  pinMode(32, INPUT); // GROVE(INPUT, OUTPUT, ANALOG)
  pinMode(33, INPUT); // GROVE(INPUT, OUTPUT, ANALOG)

  // 内部ピン初期化
  pinMode(9, OUTPUT_OPEN_DRAIN);  // IR赤外線(LOWで出力)
  digitalWrite(9, HIGH);
  pinMode(10, OUTPUT_OPEN_DRAIN); // 赤色LED(LOWで出力)
  digitalWrite(10, HIGH);

  // タイトル描画
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("TITLE\n");
}

void loop() {
  // ボタンの状態更新
  M5.update();

  if (M5.BtnA.wasPressed()) {
    // ボタンAが押された
    Serial.println("BtnAが押された");
  }
  if (M5.BtnB.wasPressed()) {
    // ボタンBが押された
    Serial.println("BtnBが押された");
  }
  int btn = M5.Axp.GetBtnPress();
  if (btn == 2) {
    // 電源ボタン(1秒以下)
    Serial.println("電源Btnが押された");
  } else if (btn == 1) {
    Serial.println("電源Btnが長押し");
  }

  // ウエイト(1以上推奨)
  delay(1);
}
