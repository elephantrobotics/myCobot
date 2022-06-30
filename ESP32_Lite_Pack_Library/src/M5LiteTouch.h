#ifndef __M5LiteTouch_H__
#define __M5LiteTouch_H__

typedef struct point
{
  int x;
  int y;
} TouchPoint_t;

class M5LiteTouch {
  public:
    void setLcd(TFT_eSPI *Lcd) {
      _Lcd = Lcd;
    }

    bool ispressed() {
      return (_TouchPoint.x != -1);
    }
    bool ispressedRaw() {
      return (_TouchPointRaw.x != -1);
    }

    TouchPoint_t getPressPoint() {
      return _TouchPoint;
    }
    TouchPoint_t getPressPointRaw() {
      return _TouchPointRaw;
    }

    void update() {
      if (enable) {
        if (!_Lcd->getTouch(&_TouchPoint.x, &_TouchPoint.y)) {
          _TouchPoint.x = -1;
          _TouchPoint.y = -1;
        }
        if (!_Lcd->getTouchRaw(&_TouchPointRaw.x, &_TouchPointRaw.y)) {
          _TouchPointRaw.x = -1;
          _TouchPointRaw.y = -1;
        }
      }
    }

    bool enable = false;

  private:
    TouchPoint_t _TouchPoint = { -1, -1};
    TouchPoint_t _TouchPointRaw = { -1, -1};
    TFT_eSPI *_Lcd;
};

#endif
