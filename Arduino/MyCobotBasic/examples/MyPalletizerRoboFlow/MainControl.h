#ifndef MainControl_h
#define MainControl_h

#include <MyPalletizerBasic.h>
#include "config.h"
#include "ServerBase.h"


class MainControl: public ServerBase
{
private:
    void updateMode(MyPalletizerBasic &myCobot, byte btn_pressed);
    void displayInfo(MyPalletizerBasic &myCobot, byte mc_mode);
    void record(MyPalletizerBasic &myCobot);  // is stop;
    void play(MyPalletizerBasic &myCobot);  // is stop  is pause
    void playFromFlash(MyPalletizerBasic &myCobot);
    void recordIntoFlash(MyPalletizerBasic &myCobot);
    void IO(MyPalletizerBasic &myCobot);
    // bool checkDataLen();
public:
    void run(MyPalletizerBasic &myCobot);
    static ServerBase *createInstance()
    {
        return new MainControl();
    }
public:
    //maincontrol 界面显示 GDataFlash--从flash中获取数据 SDataFlash--保存数据到flash
    enum UI::int {Menu = 0, PlayMenu = 1, RecordMenu = 2, PlayRam = 11, PlayFlash = 12, RecordRam = 21, RecordFlash = 22, pause = 32,
     RecordSave = 33, GDataFlash = 41, SDataFlash = 42, IoState = 51, NotPlay = 52, NoData = 53};
    enum BTN::int {A = 1, B, C};//按钮
    enum LAN::int {Chinese = 1, English};

};

#endif