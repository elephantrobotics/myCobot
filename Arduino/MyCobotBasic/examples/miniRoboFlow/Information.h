#ifndef Information_h
#define Information_h

#include "MyCobotBasic.h"
#include "SCServo.h"
#include "config.h"
#include "ServerBase.h"

class Connect: public ServerBase{
private:
    /* data */
    void info();
    void testServo(MyCobotBasic &myCobot);
    void ReadConfig(MyCobotBasic &myCobot);
public:
    void run(MyCobotBasic &myCobot);
    static ServerBase* createInstance() {return new Connect();}
};

#endif
