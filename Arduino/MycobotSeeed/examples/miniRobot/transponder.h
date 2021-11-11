#ifndef transponder_h
#define transponder_h

#include <MyCobotBasic.h>
#include "config.h"
#include "ServerBase.h"
#include <TFT_eSPI.h>


class Transponder: public ServerBase {
private:
    bool EXIT = false;
    bool checkHeader(MyCobotBasic &myCobot);
    int  readSerial(MyCobotBasic &myCobot, unsigned char* nDat, int nLen);
    void rFlushSerial();
    int  readData(MyCobotBasic &myCobot);
    void connect_ATOM(MyCobotBasic &myCobot);
    void info();
public:
    void run(MyCobotBasic &myCobot);
    void init();
    static ServerBase* createInstance() {return new Transponder();}
private:
    TFT_eSPI tft;
    int pos_y[1] = {90};
    int rect1[4] = {0, 90, 26, 30};
    int rect2[4] = {26, 90, 200, 30};
    DisplayTemplate distep;
};

#endif
