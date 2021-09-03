#ifndef Information_h
#define Information_h

#include "MyPartnerBasic.h"
#include "SCServo.h"
#include "config.h"
#include "ServerBase.h"

class Connect: public ServerBase{
private:
    /* data */
    void info();
    void testServo(MyPartnerBasic &myCobot);
    void ReadConfig(MyPartnerBasic &myCobot);
public:
    void run(MyPartnerBasic &myCobot);
    static ServerBase* createInstance() {return new Connect();}
};

#endif
