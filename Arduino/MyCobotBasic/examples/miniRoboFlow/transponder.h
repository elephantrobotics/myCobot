#ifndef transponder_h
#define transponder_h

#include <MyCobotBasic.h>
#include "config.h"
#include "ServerBase.h"


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
};

#endif


