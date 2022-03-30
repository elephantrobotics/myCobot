#ifndef Calibration_h
#define Calibration_h

#include <MyCobotBasic.h>
#include "config.h"
#include "ServerBase.h"
#include <TFT_eSPI.h>


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
    TFT_eSPI tft;
    int pos_y[2] = {90, 120};
    int rect1[4] = {0, 90, 26, 60};
    int rect2[4] = {26, 90, 200, 60};
    DisplayTemplate distep;
};

#endif
