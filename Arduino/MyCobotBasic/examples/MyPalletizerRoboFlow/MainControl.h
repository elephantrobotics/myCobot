#ifndef MainControl_h
#define MainControl_h

#include <MyPalletizerBasic.h>
#include "config.h"
#include "ServerBase.h"


class MainControl: public ServerBase {
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
    static ServerBase* createInstance() {return new MainControl();}
};

#endif