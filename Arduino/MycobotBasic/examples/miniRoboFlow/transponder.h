#ifndef transponder_h
#define transponder_h

#include <MycobotBasic.h>
#include "config.h"
#include "ServerBase.h"


class Transponder: public ServerBase {
private:
    bool EXIT = false;
    bool checkHeader(MycobotBasic &myCobot);
    int  readSerial(MycobotBasic &myCobot, unsigned char* nDat, int nLen);
    void rFlushSerial();
    int  readData(MycobotBasic &myCobot);
    void connect_ATOM(MycobotBasic &myCobot);
    void info();
public:
    void run(MycobotBasic &myCobot);
    void init();
    static ServerBase* createInstance() {return new Transponder();}
};

#endif


