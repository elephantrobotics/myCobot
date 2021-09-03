#ifndef MainControl_h
#define MainControl_h

#include <MyPartnerBasic.h>
#include "config.h"
#include "ServerBase.h"


class MainControl: public ServerBase {
private:
    void updateMode(MyPartnerBasic &myCobot, byte btn_pressed);
    void displayInfo(MyPartnerBasic &myCobot, byte mc_mode);
    void record(MyPartnerBasic &myCobot);  // is stop;
    void play(MyPartnerBasic &myCobot);  // is stop  is pause
    void playFromFlash(MyPartnerBasic &myCobot);
    void recordIntoFlash(MyPartnerBasic &myCobot);
    void IO(MyPartnerBasic &myCobot);
    // bool checkDataLen();
public:
    void run(MyPartnerBasic &myCobot);
    static ServerBase* createInstance() {return new MainControl();}
};

#endif