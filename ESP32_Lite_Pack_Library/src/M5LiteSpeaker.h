#ifndef __M5LiteSpeaker_H__
#define __M5LiteSpeaker_H__

class M5LiteSpeaker {
  public:
    M5LiteSpeaker(void) {
    }
    void setPin(uint8_t pin, uint8_t pwm_ch) {
      _pin = pin;
      _pwm_ch = pwm_ch;
      _volume = 11;
      if (_pin == 25 || _pin == 26) {
        dac = true;
      } else  {
        dac = false;
      }
    }

    void begin() {
      if (_pin == -1) {
        return;
      }
      _begun = true;
      ledcSetup(_pwm_ch, 0, 13);
      ledcAttachPin(_pin, _pwm_ch);
      setBeep(1000, 100);
    }
    void end() {
      mute();
      ledcDetachPin(_pin);
      _begun = false;
    }
    void mute() {
      ledcWriteTone(_pwm_ch, 0);
      digitalWrite(_pin, 0);
    }
    void tone(uint16_t frequency) {
      if (!_begun) {
        begin();
      }
      ledcSetup(_pwm_ch, frequency, 11);
      int vol = _volume;
      if (!dac) {
        vol = (1024 / 2 / 11) * _volume;
      }
      ledcWrite(_pwm_ch, vol);
    }
    void tone(uint16_t frequency, uint32_t duration) {
      tone(frequency);
      _count = millis() + duration;
      speaker_on = 1;
    }
    void beep() {
      if (!_begun) {
        begin();
      }
      tone(_beep_freq, _beep_duration);
    }
    void setBeep(uint16_t frequency, uint16_t duration) {
      _beep_freq = frequency;
      _beep_duration = duration;
    }
    void update() {
      if (speaker_on) {
        if (millis() > _count) {
          speaker_on = 0;
          mute();
        }
      }
    }

    void write(uint8_t value) {
      if (dac) {
        dacWrite(_pin, value);
      }
    }
    void setVolume(uint8_t volume) {
      if (dac == false && 11 < volume) {
        volume = 11;
      }
      _volume = volume;
    }
    void playMusic(const uint8_t *music_data, uint16_t sample_rate) {
      if (!dac) {
        return;
      }
      uint32_t length = strlen((char*)music_data);
      uint16_t delay_interval = ((uint32_t)1000000 / sample_rate);
      if (_volume != 11) {
        for (int i = 0; i < length; i++) {
          write(music_data[i] / _volume);
          delayMicroseconds(delay_interval);
        }

        for (int t = music_data[length - 1] / _volume; t >= 0; t--) {
          write(t);
          delay(2);
        }
      }
      ledcAttachPin(_pin, _pwm_ch);
    }

  private:
    int8_t _pin = -1;
    int8_t _pwm_ch = -1;
    uint32_t _count;
    uint8_t _volume = 8;
    uint16_t _beep_duration;
    uint16_t _beep_freq;
    bool _begun = false;
    bool speaker_on;
    bool dac = false;
};
#endif
