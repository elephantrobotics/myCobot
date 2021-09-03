#ifndef transponder_h
#define transponder_h

#include <MyPartnerBasic.h>
#include "config.h"
#include "ServerBase.h"


class Transponder: public ServerBase {
private:
    bool EXIT = false;
    bool checkHeader(MyPartnerBasic &myCobot);
    int  readSerial(MyPartnerBasic &myCobot, unsigned char* nDat, int nLen);
    void rFlushSerial();
    int  readData(MyPartnerBasic &myCobot);
    void connect_ATOM(MyPartnerBasic &myCobot);
    void info();
public:
    void run(MyPartnerBasic &myCobot);
    void init();
    static ServerBase* createInstance() {return new Transponder();}
};

#endif


