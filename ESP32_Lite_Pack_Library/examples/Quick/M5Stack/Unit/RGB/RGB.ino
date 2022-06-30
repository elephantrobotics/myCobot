#define FASTLED_INTERNAL  // FastLEDの警告抑制
#include <FastLED.h>      // http://librarymanager/All#FastLED https://github.com/FastLED/FastLED

#define NUM_LEDS 3        // LEDの数
#define DATA_PIN 32       // M5StickC(内側のデータ線)

CRGB leds[NUM_LEDS];      // 色データ保存用

void setup() {
  // 初期化
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(20);

  // 色をセット
  leds[0] = CRGB::Red;
  leds[1] = CRGB::Yellow;
  leds[2] = CRGB::Green;
}

void loop() {
  // 定期的に出力しないとユニットを抜いたときに再点灯しなくなる
  FastLED.show();

  delay(1000);
}
