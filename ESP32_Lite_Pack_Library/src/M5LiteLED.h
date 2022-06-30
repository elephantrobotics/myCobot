#ifndef __M5LiteLED_H__
#define __M5LiteLED_H__

#define FASTLED_INTERNAL
#include <FastLED.h>

class M5LiteLED {
  public:
    const static uint8_t NUM_LEDS = 25;
    const static uint8_t DATA_PIN = 27;

    M5LiteLED() {
      _xSemaphore = xSemaphoreCreateMutex();
    }

    void begin() {
      // LED Reset
      digitalWrite(DATA_PIN, LOW);
      delay(50);

      // LED Start
      FastLED.addLeds<WS2812, DATA_PIN, GRB>(_ledbuff, NUM_LEDS);
      xTaskCreateUniversal(
        task,
        "M5LiteLED",
        8192,
        this,
        5,
        NULL,
        APP_CPU_NUM
      );
    }

    static void task(void *pvParameters) {
      M5LiteLED *led = (M5LiteLED*)pvParameters;
      led->run();
    }

    void run(void) {
      clear();
      FastLED.show();
      FastLED.setBrightness(20);

      while (1) {
        FastLED.show();
        delay(10);
      }
    }

    void setBrightness(uint8_t brightness) {
      if (20 < brightness) {
        brightness = 20;
      }
      xSemaphoreTake(_xSemaphore, portMAX_DELAY);
      FastLED.setBrightness(brightness);
      xSemaphoreGive(_xSemaphore);
    }

    void drawpix(uint8_t xpos, uint8_t ypos, CRGB Color) {
      if ((5 <= xpos) || (5 <= ypos))   {
        return;
      }
      xSemaphoreTake(_xSemaphore, portMAX_DELAY);
      _ledbuff[ypos * 5 + xpos] = Color;
      xSemaphoreGive(_xSemaphore);
    }

    void drawpix(uint8_t Number, CRGB Color) {
      if (Number >= 25) {
        return;
      }
      xSemaphoreTake(_xSemaphore, portMAX_DELAY);
      _ledbuff[Number] = Color;
      xSemaphoreGive(_xSemaphore);
    }

    void clear() {
      xSemaphoreTake(_xSemaphore, portMAX_DELAY);
      for (int8_t i = 0; i < NUM_LEDS; i++) {
        _ledbuff[i] = 0;
      }
      xSemaphoreGive(_xSemaphore);
    }

    CRGB _ledbuff[NUM_LEDS];
  private:
    uint8_t _numberled;

    uint8_t _mode;
    uint16_t _am_speed;
    uint8_t _am_mode;
    int32_t _count_x, _count_y;
    int32_t _am_count = -1;
    uint8_t *_am_buffptr;

    SemaphoreHandle_t _xSemaphore = NULL;
};

#endif
