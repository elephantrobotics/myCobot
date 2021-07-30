#ifndef Information_h
#define Information_h

#include "MycobotBasic.h"
#include "SCServo.h"
#include "config.h"

class Connect
{
private:
    /* data */
    void info();
    void testServo(MycobotBasic &myCobot);
    void ReadConfig();
public:
    void test(MycobotBasic &myCobot);
};

#endif
