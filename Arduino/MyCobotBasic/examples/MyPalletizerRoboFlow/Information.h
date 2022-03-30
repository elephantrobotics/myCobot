#ifndef Information_h
#define Information_h

#include "MyPalletizerBasic.h"
//#include "SCServo.h"
#include "config.h"
#include "ServerBase.h"

class Connect: public ServerBase
{
private:
    /* data */
    void info();
    void testServo(MyPalletizerBasic &myCobot);
    void ReadConfig(MyPalletizerBasic &myCobot);
public:
    void run(MyPalletizerBasic &myCobot);
    static ServerBase *createInstance()
    {
        return new Connect();
    }
};

#endif
