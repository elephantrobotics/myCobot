#ifndef Calibration_h
#define Calibration_h

#include <MyCobotBasic.h>
#include "config.h"
#include "ServerBase.h"


class Calibration: public ServerBase
{
private:
    void info();
    void init(MyCobotBasic &myCobot);
    void test(MyCobotBasic &myCobot);
    void reset(MyCobotBasic &myCobot);
    void DisplayHead(bool isClearAll);
public:
    void run(MyCobotBasic &myCobot);
    static ServerBase *createInstance()
    {
        return new Calibration();
    }
};

#endif
