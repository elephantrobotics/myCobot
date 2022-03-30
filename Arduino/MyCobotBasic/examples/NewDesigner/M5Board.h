#ifndef __M5Board_H__
#define __M5Board_H__
#include <M5Stack.h>
#include <FS.h>
#include <SPIFFS.h>
#include <EEPROM.h>
#include <BluetoothSerial.h>
#include <driver/adc.h>
#include "TOF.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define FORMAT_SPIFFS_IF_FAILED true
#define board_serial Serial2

class M5Board : public BoardBasic
{
public:
    M5Board()
    {
        Serial.println("M5Board()");
    }
    virtual ~M5Board()
    {
        Serial.println("~M5Board()");
    }
    virtual void Seeedbegin();
    virtual void BtnInit() {}
    virtual void ClearScreen(uint32_t color);
    virtual void SetTextColor(uint32_t color);
    virtual void SetTextSize(uint8_t size);
    virtual void SetCursor(int16_t x, int16_t y);
    virtual void SetBitmapColor(uint16_t fgcolor, uint16_t bgcolor);
    virtual void SetRotation(uint8_t r);
    virtual void FillRect(int32_t x, int32_t y, int32_t w, int32_t h,
                          uint32_t color);
    virtual void PushImage(int32_t x0, int32_t y0, int32_t w, int32_t h,
                           uint16_t *data);
    virtual void Print(const __FlashStringHelper *);
    virtual void Print(const String &);
    virtual void Print(const char *);
    virtual void Print(char);
    //virtual void Print(unsigned char, int = DEC);
    virtual void Print(int, int = DEC);
    virtual void Print(unsigned int, int = DEC);
    virtual void Print(long, int = DEC);
    virtual void Print(unsigned long, int = DEC);
    virtual void Print(double, int = 2);
    virtual void Print(const Printable &);

    virtual void Println(const __FlashStringHelper *);
    virtual void Println(const String &s);
    virtual void Println(const char *);
    virtual void Println(char);
    virtual void Println(unsigned char, int = DEC);
    virtual void Println(int, int = DEC);
    virtual void Println(unsigned int, int = DEC);
    virtual void Println(long, int = DEC);
    virtual void Println(unsigned long, int = DEC);
    virtual void Println(double, int = 2);
    virtual void Println(void);
    virtual void Println(const Printable &);

    virtual void Printf(const char *, ...);

    virtual void EepromBegin(size_t size);
    virtual uint8_t EepromRead(int address);
    virtual void EepromWrite(int address, uint8_t val);
    virtual void EepromCommit();
    virtual void FixBtnClicked();

    virtual void DrawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color);
    virtual bool IsBtnClicked(int btn);//1-->Down 2-up 3-ok 4-left
    virtual void DrawString(const char *string, int32_t poX, int32_t poY);
    virtual void DrawString(const char *string, int32_t poX, int32_t poY,
                            uint8_t font);
    virtual bool InitFlash();
    virtual void BtnUpdate();
    virtual void DrawButtonLine();
    virtual void DrawWLanExit();
    virtual void HideBluetooth(std::map<int, string> &menuMap);
    virtual void DrawMainControlPlayStop();
    virtual bool MainControlBtnStop();
    virtual bool UartBtnExit();
    virtual uint16_t GetTOFDistance(); //tof
    //BT
    virtual void CreateBTServer(String Bt_name);
    virtual void DrawBtAddress();
    //virtual void BTConfirmRequestCallback(uint32_t numVal);
    //virtual void BTAuthCompleteCallback(bool success);
    bool IsConfirmRequestPending() const;
    virtual int Read();
    virtual void Write(uint8_t c);
    virtual void Write(const uint8_t *buffer, size_t size);
    virtual bool Available();
    virtual void End();
    virtual bool HasClient();
    virtual void SetConnect();
    virtual void SetNoConnect();
    virtual void ConfirmReply(bool confirm);
public:
    enum Board {m5stack, Seeed};
private:
    BluetoothSerial SerialBT;
    uint8_t mac_addr[6] = {0};
};
#endif
