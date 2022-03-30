#ifndef Information_h
#define Information_h

#include "MyCobotBasic.h"
#include "config.h"
#include "ServerBase.h"
#include <stdio.h>
class Connect: public ServerBase
{
private:
    /* data */
    void info();
    void testServo(MyCobotBasic &myCobot);
    void ReadConfig(MyCobotBasic &myCobot);
public:
    void run(MyCobotBasic &myCobot);
    static ServerBase *createInstance()
    {
        return new Connect();
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
    bool Exit {false};
};

#endif
