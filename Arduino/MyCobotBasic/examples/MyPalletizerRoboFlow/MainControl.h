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
    //The maincontrol interface displays GDataFlash-->get data from flash SDataFlash-->save data to flash
    enum UI : int {Menu = 0, PlayMenu = 1, RecordMenu = 2, PlayRam = 11, PlayFlash = 12, RecordRam = 21, RecordFlash = 22, pause = 32,
                   RecordSave = 33, GDataFlash = 41, SDataFlash = 42, IoState = 51, NotPlay = 52, NoData = 53
                  } ui = (enum UI)0;
    //Button              
    enum BTN : int {A = 1, B, C} btn;

};

#endif