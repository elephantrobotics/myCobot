#ifndef MainControl_h
#define MainControl_h

#include <MyCobotBasic.h>
#include "config.h"
#include "ServerBase.h"

class MainControl: public ServerBase
{
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
    static ServerBase *createInstance()
    {
        return new MainControl();
    }
private:
    int pos_y[3] = {90, 120, 150};
    int rect1[4] = {0, 90, 26, 90};
    int rect2[4] = {26, 90, 200, 90};
    DisplayTemplate distep;
#ifdef BOARD_M5_BASIC
    BoardBasic *board = new M5Board();
#elif defined BOARD_SEEED_WIO
    BoardBasic *board = new SeeedBoard();
#endif
};

#endif
