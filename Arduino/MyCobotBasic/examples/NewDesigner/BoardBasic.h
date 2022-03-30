#ifndef __BoardBasic_H__
#define __BoardBasic_H__

//#define BOARD_SEEED_WIO
#define BOARD_M5_BASIC

#include "Common.h"
#include <stdio.h>
#include "WString.h"
#include <string>
#include <map>
#include <Printable.h>
using namespace std;

class BoardBasic
{
public:
    BoardBasic() {}
//    virtual ~BoardBasic() = 0;
    virtual void BtnInit() = 0;
    virtual void Seeedbegin() = 0;
    virtual void ClearScreen(uint32_t color) = 0;
    virtual void SetTextColor(uint32_t color) = 0;
    virtual void SetTextSize(uint8_t size) = 0;
    virtual void SetCursor(int16_t x, int16_t y) = 0;
    virtual void SetBitmapColor(uint16_t fgcolor, uint16_t bgcolor) = 0;
    virtual void SetRotation(uint8_t r) = 0;
    virtual void FillRect(int32_t x, int32_t y, int32_t w, int32_t h,
                          uint32_t color) = 0;
    virtual void PushImage(int32_t x0, int32_t y0, int32_t w, int32_t h,
                           uint16_t *data) = 0;
    virtual void Print(const __FlashStringHelper *) = 0;
    virtual void Print(const String &) = 0;
    virtual void Print(const char *) = 0;
    virtual void Print(char) = 0;
    //virtual void Print(unsigned char, int = DEC) = 0;
    virtual void Print(int, int = DEC) = 0;
    virtual void Print(unsigned int, int = DEC) = 0;
    virtual void Print(long, int = DEC) = 0;
    virtual void Print(unsigned long, int = DEC) = 0;
    virtual void Print(double, int = 2) = 0;
    virtual void Print(const Printable &) = 0;
    virtual void Println(const __FlashStringHelper *) = 0;
    virtual void Println(const String &s) = 0;
    virtual void Println(const char *) = 0;
    virtual void Println(char) = 0;
    virtual void Println(unsigned char, int = DEC) = 0;
    virtual void Println(int, int = DEC) = 0;
    virtual void Println(unsigned int, int = DEC) = 0;
    virtual void Println(long, int = DEC) = 0;
    virtual void Println(unsigned long, int = DEC) = 0;
    virtual void Println(double, int = 2) = 0;
    virtual void Println(void) = 0;
    virtual void Println(const Printable &);

    virtual void Printf(const char *, ...) = 0;

    virtual void EepromBegin(size_t size) = 0;
    virtual uint8_t EepromRead(int address) = 0;
    virtual void EepromWrite(int address, uint8_t val) = 0;
    virtual void EepromCommit() = 0;

    virtual void DrawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color) = 0;
    virtual bool IsBtnClicked(int btn) = 0;//0-->Down 1-up 2-ok 3-left
    virtual void DrawString(const char *string, int32_t poX, int32_t poY) = 0;
    virtual void DrawString(const char *string, int32_t poX, int32_t poY,
                            uint8_t font) = 0;
    virtual bool InitFlash() = 0;
    virtual void BtnUpdate() = 0;
    virtual void DrawButtonLine() = 0;
    virtual void DrawWLanExit() = 0;
    //virtual bool WlanExitClicked();
    virtual void HideBluetooth(std::map<int, string> &menuMap) = 0;
    virtual void DrawMainControlPlayStop() = 0;
    virtual bool MainControlBtnStop() = 0;
    virtual bool UartBtnExit() = 0;
    virtual uint16_t GetTOFDistance() = 0;
    //BT
    virtual void CreateBTServer(String Bt_name) = 0;
    virtual void DrawBtAddress() = 0;
    virtual bool IsConfirmRequestPending() const = 0;
    virtual int Read() = 0;
    virtual void Write(uint8_t c) = 0;
    virtual void Write(const uint8_t *buffer, size_t size) = 0;
    virtual bool Available() = 0;
    virtual void End() = 0;
    virtual bool HasClient() = 0;
    virtual void SetConnect() = 0;
    virtual void SetNoConnect() = 0;
    virtual void ConfirmReply(bool confirm) = 0;
    virtual void FixBtnClicked() = 0;
public:
    enum Board {m5stack, Seeed};
    //HardwareSerial hw_serial;
};
#endif
