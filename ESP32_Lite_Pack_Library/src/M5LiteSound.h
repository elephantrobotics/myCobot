#ifndef __M5LiteSound_H__
#define __M5LiteSound_H__

#define M5LITE_SOUND_I2S_NUMBER I2S_NUM_0

class M5LiteSound {
  public:
    enum {
      M5LITE_SOUND_NONE,
      M5LITE_SOUND_SPEAKER,
      M5LITE_SOUND_MIC
    };

    M5LiteSound(void) {
    }

    void begin() {
      _state = true;
    }

    void setAXP(M5LiteAXP192 *Axp) {
      _Axp = Axp;
    }

    void setBoard(int board) {
      _board = board;
    }

    void setMode(uint8_t mode, int sampleRate = 16000) {
      esp_err_t err = ESP_OK;

      _mode = mode;

      i2s_driver_uninstall(M5LITE_SOUND_I2S_NUMBER);

      if (mode == M5LITE_SOUND_NONE) {
        return;
      }

      int8_t bckPin     = -1;
      int8_t lrckPin    = -1;
      int8_t dataOutPin = -1;
      int8_t dataInPin  = -1;

      if (_board == lgfx::board_M5Stack) {
        // DAC
        _i2s = false;
      } else if (_board == lgfx::board_M5StackCore2) {
        // I2S
        bckPin     = 12;
        lrckPin    = 0;
        dataOutPin = 2;
        dataInPin  = 34;
      } else if (_board == lgfx::board_M5StickC) {
        // Speaker HAT
        _i2s = false;
      } else if (_board == lgfx::board_M5StickCPlus) {
        // Speaker HAT
        _i2s = false;
      } else if (_board == lgfx::board_unknown) {
        // ATOM Echo
        bckPin     = 19;
        lrckPin    = 33;
        dataOutPin = 22;
        dataInPin  = 23;
      }

      if (_i2s) {
        i2s_config_t i2s_config = {
          .mode                 = (i2s_mode_t)(I2S_MODE_MASTER),
          .sample_rate          = sampleRate,
          .bits_per_sample      = I2S_BITS_PER_SAMPLE_16BIT,
          .channel_format       = I2S_CHANNEL_FMT_ALL_RIGHT,
          .communication_format = I2S_COMM_FORMAT_I2S,
          .intr_alloc_flags     = ESP_INTR_FLAG_LEVEL1,
          .dma_buf_count        = 4,
          .dma_buf_len          = buffSize,
          .use_apll             = false,
          .tx_desc_auto_clear   = true,
          .fixed_mclk           = 0
        };

        if (mode == M5LITE_SOUND_MIC) {
          i2s_config.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM);
        } else {
          i2s_config.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);
        }

        err += i2s_driver_install(M5LITE_SOUND_I2S_NUMBER, &i2s_config, 0, NULL);

        i2s_pin_config_t tx_pin_config = {
          .bck_io_num     = bckPin,
          .ws_io_num      = lrckPin,
          .data_out_num   = dataOutPin,
          .data_in_num    = dataInPin,
        };
        err += i2s_set_pin(M5LITE_SOUND_I2S_NUMBER, &tx_pin_config);

        if (mode != M5LITE_SOUND_MIC) {
          err += i2s_set_clk(M5LITE_SOUND_I2S_NUMBER, sampleRate, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);
        }
      } else {
        i2s_config_t i2s_config = {
          .mode                 = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN),
          .sample_rate          = sampleRate,
          .bits_per_sample      = I2S_BITS_PER_SAMPLE_16BIT,
          .channel_format       = I2S_CHANNEL_FMT_ALL_LEFT,
          .communication_format = I2S_COMM_FORMAT_I2S_MSB,
          .intr_alloc_flags     = ESP_INTR_FLAG_LEVEL1,
          .dma_buf_count        = 4,
          .dma_buf_len          = buffSize,
          .use_apll             = false,
          .tx_desc_auto_clear   = true,
          .fixed_mclk           = 0
        };
        err += i2s_driver_install(M5LITE_SOUND_I2S_NUMBER, &i2s_config, 0, NULL);
        err += i2s_set_pin(M5LITE_SOUND_I2S_NUMBER, NULL);
      }

      i2s_zero_dma_buffer(M5LITE_SOUND_I2S_NUMBER);
    }

    void play(const unsigned char *playWav, size_t playSize, int sampleRate = 16000, int bit = 8) {
      setMode(M5LITE_SOUND_SPEAKER, sampleRate);

      if (_board == lgfx::board_M5StackCore2) {
        _Axp->SetSpkEnable(true);
      }

      // Write Speaker
      size_t bytes_written;
      if (_i2s) {
        // I2S
        int16_t data[buffSize / 2];
        uint8_t *wave8 = (uint8_t*)playWav;
        int16_t *wave16 = (int16_t*)playWav;
        int index = 0;
        int waveSize = 0;
        if (bit == 16) {
          waveSize = playSize / 2;
        } else {
          waveSize = playSize;
        }

        for (int i; i < waveSize; i++) {
          int16_t val;
          if (bit == 16) {
            val = wave16[i];
          } else {
            val = (wave8[i] - 128) * 256;
          }

          data[index] = val;
          index += 1;
          if ((buffSize / 2) <= index) {
            index = 0;
            i2s_write(M5LITE_SOUND_I2S_NUMBER, data, buffSize, &bytes_written, portMAX_DELAY);
          }
        }
        if (index != 0) {
          i2s_write(M5LITE_SOUND_I2S_NUMBER, data, index, &bytes_written, portMAX_DELAY);
        }
        delay(100);
      } else {
        // DAC Out
        unsigned char data[buffSize];
        uint8_t *wave8 = (uint8_t*)playWav;
        int16_t *wave16 = (int16_t*)playWav;
        int index = 0;
        int waveSize = 0;
        if (bit == 16) {
          waveSize = playSize / 2;
        } else {
          waveSize = playSize;
        }

        for (int i; i < waveSize; i++) {
          uint8_t val;
          if (bit == 16) {
            val = (wave16[i] / 256) + 128;
          } else {
            val = wave8[i];
          }

          data[index] = 0;
          data[index + 1] = val;
          data[index + 2] = 0;
          data[index + 3] = 0;
          index += 4;
          if (buffSize <= index) {
            index = 0;
            i2s_write(M5LITE_SOUND_I2S_NUMBER, data, buffSize, &bytes_written, portMAX_DELAY);
            Serial.printf("len = %d\n", bytes_written);
          }
        }
        if (index != 0) {
          i2s_write(M5LITE_SOUND_I2S_NUMBER, data, index, &bytes_written, portMAX_DELAY);
          Serial.printf("len = %d\n", bytes_written);
        }
      }

      i2s_zero_dma_buffer(M5LITE_SOUND_I2S_NUMBER);

      if (_board == lgfx::board_M5StackCore2) {
        _Axp->SetSpkEnable(false);
      }
    }

  private:
    bool _state = false;
    bool _i2s = true;
    M5LiteAXP192 *_Axp;
    int _board;
    int _mode = M5LITE_SOUND_NONE;
    const int buffSize = 256;
};
#endif
