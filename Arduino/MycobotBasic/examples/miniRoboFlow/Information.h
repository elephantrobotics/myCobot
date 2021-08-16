#ifndef Information_h
#define Information_h

#include "MycobotBasic.h"
#include "SCServo.h"
#include "config.h"
#include "ServerBase.h"

class Connect: public ServerBase{
private:
    /* data */
    void info();
    void testServo(MycobotBasic &myCobot);
    void ReadConfig(MycobotBasic &myCobot);
public:
    void run(MycobotBasic &myCobot);
    static ServerBase* createInstance() {return new Connect();}
};

#endif
