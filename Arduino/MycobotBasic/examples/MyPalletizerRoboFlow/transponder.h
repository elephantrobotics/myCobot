#ifndef transponder_h
#define transponder_h

#include <MyPalletizerBasic.h>
#include "config.h"
#include "ServerBase.h"


class Transponder: public ServerBase {
private:
    bool EXIT = false;
    bool checkHeader(MyPalletizerBasic &myCobot);
    int  readSerial(MyPalletizerBasic &myCobot, unsigned char* nDat, int nLen);
    void rFlushSerial();
    int  readData(MyPalletizerBasic &myCobot);
    void connect_ATOM(MyPalletizerBasic &myCobot);
    void info();
public:
    void run(MyPalletizerBasic &myCobot);
    void init();
    static ServerBase* createInstance() {return new Transponder();}
};

#endif


