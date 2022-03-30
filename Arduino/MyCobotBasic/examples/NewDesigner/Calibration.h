#ifndef Calibration_h
#define Calibration_h

#include <MyCobotBasic.h>
#include "config.h"
#include "ServerBase.h"


class Calibration: public ServerBase
{
private:
    void info();
    void init(MyCobotBasic &myCobot);
    void test(MyCobotBasic &myCobot);
    void reset(MyCobotBasic &myCobot);
    void DisplayHead(bool isClearAll);
public:
    void run(MyCobotBasic &myCobot);
    static ServerBase *createInstance()
    {
        return new Calibration();
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
