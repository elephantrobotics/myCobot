#ifndef MainControl_h
#define MainControl_h

#include <MyCobotBasic.h>
#include "config.h"
#include "ServerBase.h"
#include <TFT_eSPI.h>
#include <Seeed_FS.h>
#include "SD/Seeed_SD.h"


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
    TFT_eSPI tft;
    int pos_y[2] = {90, 120};
    int rect1[4] = {0, 90, 26, 60};
    int rect2[4] = {26, 90, 200, 60};
    DisplayTemplate distep;
};

#endif
