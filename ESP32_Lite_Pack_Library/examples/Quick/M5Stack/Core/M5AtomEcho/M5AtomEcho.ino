#include <M5Atom.h>     // http://librarymanager/All#M5Atom  https://github.com/m5stack/M5Atom
#include <FastLED.h>    // http://librarymanager/All#FastLED https://github.com/FastLED/FastLED
#include <driver/i2s.h>

#define CONFIG_I2S_BCK_PIN      19
#define CONFIG_I2S_LRCK_PIN     33
#define CONFIG_I2S_DATA_PIN     22
#define CONFIG_I2S_DATA_IN_PIN  23
 
#define SPEAKER_I2S_NUMBER      I2S_NUM_0
 
#define MODE_MIC                0
#define MODE_SPK                1

void InitI2SSpeakerOrMic(int mode)
{
  esp_err_t err = ESP_OK;
 
  i2s_driver_uninstall(SPEAKER_I2S_NUMBER);
  i2s_config_t i2s_config = {
    .mode                 = (i2s_mode_t)(I2S_MODE_MASTER),
    .sample_rate          = 16000,
    .bits_per_sample      = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format       = I2S_CHANNEL_FMT_ALL_RIGHT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags     = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count        = 6,
    .dma_buf_len          = 60,
    .use_apll             = false,
    .tx_desc_auto_clear   = true,
    .fixed_mclk           = 0
  };
  if (mode == MODE_MIC){
    i2s_config.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM);
  }else{
    i2s_config.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);
  }
 
  err += i2s_driver_install(SPEAKER_I2S_NUMBER, &i2s_config, 0, NULL);
 
  i2s_pin_config_t tx_pin_config = {
    .bck_io_num           = CONFIG_I2S_BCK_PIN,
    .ws_io_num            = CONFIG_I2S_LRCK_PIN,
    .data_out_num         = CONFIG_I2S_DATA_PIN,
    .data_in_num          = CONFIG_I2S_DATA_IN_PIN,
  };
  err += i2s_set_pin(SPEAKER_I2S_NUMBER, &tx_pin_config);
 
  if (mode != MODE_MIC) {
    err += i2s_set_clk(SPEAKER_I2S_NUMBER, 16000, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);
  }
 
  i2s_zero_dma_buffer(SPEAKER_I2S_NUMBER);
}

void setup() {
  // 初期化
  M5.begin(true, false, true);  // (Serial, I2C, NeoPixel)

  // GPIO初期化
  pinMode(21, INPUT); // PIN  (INPUT, OUTPUT,       )I2C, UART利用不可
  pinMode(25, INPUT); // PIN  (INPUT, OUTPUT, ANALOG)I2C, UART利用不可, 無線利用時にはANALOG利用不可
  pinMode(26, INPUT); // GROVE(INPUT, OUTPUT, ANALOG)無線利用時にはANALOG利用不可, DAC出力可
  pinMode(32, INPUT); // GROVE(INPUT, OUTPUT, ANALOG)

  // 内部ピン初期化
  pinMode(12, OUTPUT_OPEN_DRAIN); // IR赤外線(LOWで出力)
  digitalWrite(12, HIGH);

  // LED(0固定)
  M5.dis.drawpix(0, CRGB::Red);

  // MICで初期化
  InitI2SSpeakerOrMic(MODE_MIC);
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
