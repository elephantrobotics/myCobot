#ifndef MainControl_h
#define MainControl_h

#include <MyCobotBasic.h>
#include "config.h"
#include "ServerBase.h"


class MainControl: public ServerBase {
private:
    void updateMode(MyCobotBasic &myCobot, byte btn_pressed);
    void displayInfo(MyCobotBasic &myCobot, byte mc_mode);
    void record(MyCobotBasic &myCobot);  // is stop;
    void play(MyCobotBasic &myCobot);  // is stop  is pause
    void playFromFlash(MyCobotBasic &myCobot);
    void recordIntoFlash(MyCobotBasic &myCobot);
    void IO(MyCobotBasic &myCobot);
    // bool checkDataLen();
public:
    void run(MyCobotBasic &myCobot);
    static ServerBase* createInstance() {return new MainControl();}
};

#endif