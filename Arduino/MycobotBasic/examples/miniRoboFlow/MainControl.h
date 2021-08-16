#ifndef MainControl_h
#define MainControl_h

#include <MycobotBasic.h>
#include "config.h"
#include "ServerBase.h"


class MainControl: public ServerBase {
private:
    void updateMode(MycobotBasic &myCobot, byte btn_pressed);
    void displayInfo(MycobotBasic &myCobot, byte mc_mode);
    void record(MycobotBasic &myCobot);  // is stop;
    void play(MycobotBasic &myCobot);  // is stop  is pause
    void playFromFlash(MycobotBasic &myCobot);
    void recordIntoFlash(MycobotBasic &myCobot);
    void IO(MycobotBasic &myCobot);
    // bool checkDataLen();
public:
    void run(MycobotBasic &myCobot);
    static ServerBase* createInstance() {return new MainControl();}
};

#endif