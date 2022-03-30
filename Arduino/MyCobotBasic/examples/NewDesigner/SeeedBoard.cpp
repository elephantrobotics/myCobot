#include "BoardBasic.h"
#ifdef BOARD_SEEED_WIO
#include "SeeedBoard.h"

void SeeedBoard::Seeedbegin()
{
    tft.begin();
}

void SeeedBoard::BtnInit()
{
    int btn[4] = {WIO_5S_UP, WIO_5S_DOWN, WIO_5S_RIGHT, WIO_5S_LEFT};
    for (int i = 0; i < 4; i++) {
        pinMode(btn[i], INPUT_PULLUP);
    }
}

void SeeedBoard::ClearScreen(uint32_t color)
{
    tft.fillScreen(color);
}

void SeeedBoard::SetTextColor(uint32_t color)
{
    tft.setTextColor(color);
}

void SeeedBoard::SetTextSize(uint8_t size)
{
    tft.setTextSize(size);
}

void SeeedBoard::SetBitmapColor(uint16_t fgcolor, uint16_t bgcolor)
{
    tft.setBitmapColor(fgcolor, bgcolor);
}

void SeeedBoard::SetRotation(uint8_t r)
{
    tft.setRotation(r);
}

void SeeedBoard::FillRect(int32_t x, int32_t y, int32_t w, int32_t h,
                          uint32_t color)
{
    tft.fillRect(x, y, w, h, color);
}

void SeeedBoard::PushImage(int32_t x0, int32_t y0, int32_t w, int32_t h,
                           uint16_t *data)
{
    tft.pushImage(x0, y0, w, h, data);
}

void SeeedBoard::SetCursor(int16_t x, int16_t y)
{
    tft.setCursor(x, y);
}

void SeeedBoard::Print(const __FlashStringHelper *p)
{
    tft.print(p);
}

void SeeedBoard::Print(const String &s)
{
    tft.print(s);
}

void SeeedBoard::Print(const char *data)
{
    tft.print(data);
}

void SeeedBoard::Print(char c)
{
    tft.print(c);
}

void SeeedBoard::Print(unsigned char c, int base)
{
    tft.print(c, base);
}

void SeeedBoard::Print(int data, int base)
{
    tft.print(data, base);
}

void SeeedBoard::Print(unsigned int data, int base)
{
    tft.print(data, base);
}
void SeeedBoard::Print(long l, int base)
{
    tft.print(l, base);
}

void SeeedBoard::Print(unsigned long l, int base)
{
    tft.print(l, base);
}

void SeeedBoard::Print(double d, int base)
{
    tft.print(d, base);
}

void SeeedBoard::Print(const Printable &p)
{
    tft.print(p);
}

void SeeedBoard::Println(const __FlashStringHelper *p)
{
    tft.println(p);
}

void SeeedBoard::Println(const String &s)
{
    tft.println(s);
}

void SeeedBoard::Println(const char *data)
{
    tft.println(data);
}

void SeeedBoard::Println(char c)
{
    tft.println(c);
}

void SeeedBoard::Println(unsigned char c, int base)
{
    tft.println(c, base);
}

void SeeedBoard::Println(int data, int base)
{
    tft.println(data, base);
}

void SeeedBoard::Println(unsigned int data, int base)
{
    tft.println(data, base);
}

void SeeedBoard::Println(long l, int base)
{
    tft.println(l, base);
}

void SeeedBoard::Println(unsigned long l, int base)
{
    tft.println(l, base);
}

void SeeedBoard::Println(double d, int base)
{
    tft.println(d, base);
}

void SeeedBoard::Println(const Printable &p)
{
    tft.println(p);
}

void SeeedBoard::Println(void)
{
    tft.println();
}

void SeeedBoard::Printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    tft.printf(fmt, args);
    va_end(args);
}

void SeeedBoard::DrawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color)
{
    tft.drawFastHLine(x, y, w, color);
}

void SeeedBoard::EepromBegin(size_t size)
{

}

uint8_t SeeedBoard::EepromRead(int address)
{
    return -1;
}

void SeeedBoard::EepromWrite(int address, uint8_t val)
{

}

void SeeedBoard::EepromCommit()
{

}

bool SeeedBoard::IsBtnClicked(int btn)
{
    bool flag = false;
    switch (btn) {
        case 0: {
            flag = (digitalRead(WIO_5S_DOWN) == LOW);
        }
        break;
        case 1: {
            flag = (digitalRead(WIO_5S_UP) == LOW);
        }
        break;
        case 2: {
            flag = (digitalRead(WIO_5S_RIGHT) == LOW);
        }
        break;
        case 3: {
            flag = (digitalRead(WIO_5S_LEFT) == LOW);
        }
        break;
    defalut:
        break;
    }
    return flag;
}

void SeeedBoard::DrawString(const char *string, int32_t poX, int32_t poY)
{
    tft.drawString(string, poX, poY);
}

void SeeedBoard::DrawString(char const *string, int32_t poX, int32_t poY,
                            unsigned char c)
{
    tft.drawString(string, poX, poY, c);
}

bool SeeedBoard::InitFlash()
{
    return SD.begin(SDCARD_SS_PIN, SDCARD_SPI);
}

void SeeedBoard::BtnUpdate()
{

}

void SeeedBoard::DrawButtonLine()
{

}

void SeeedBoard::DrawWLanExit()
{

}

void SeeedBoard::HideBluetooth(std::map<int, string> &menuMap)
{
    string str[2] = {"USB UART", "WLAN Server"};
    for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++) {
        menuMap.insert(std::make_pair(i, str[i]));
    }
}

void SeeedBoard::DrawMainControlPlayStop()
{

}

bool SeeedBoard::MainControlBtnStop()
{
    return digitalRead(WIO_5S_LEFT) == LOW;//left键为stop
}

bool SeeedBoard::UartBtnExit()
{
    return digitalRead(WIO_5S_LEFT) == LOW;//A键为stop
}

uint16_t SeeedBoard::GetTOFDistance()
{
    return -1;
}

//BT
void SeeedBoard::CreateBTServer(String Bt_name)
{

}

void SeeedBoard::DrawBtAddress()
{

}

int SeeedBoard::Read()
{
    return -1;
}

void SeeedBoard::Write(uint8_t c)
{

}

void SeeedBoard::Write(const uint8_t *buffer, size_t size)
{

}

bool SeeedBoard::Available()
{
    return false;
}

void SeeedBoard::End()
{

}

bool SeeedBoard::HasClient()
{
    return false;
}

void SeeedBoard::SetConnect()
{

}

void SeeedBoard::SetNoConnect()
{

}

void SeeedBoard::ConfirmReply(bool confirm)
{

}

void SeeedBoard::FixBtnClicked()
{

}
#endif
