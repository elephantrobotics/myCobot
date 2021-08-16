#ifndef Calibration_h
#define Calibration_h

#include <MycobotBasic.h>
#include "config.h"
#include "ServerBase.h"


class Calibration: public ServerBase{
private:
    void info();
    void init(MycobotBasic &myCobot);
    void test(MycobotBasic &myCobot);
    void reset(MycobotBasic &myCobot);
    void DisplayHead(bool isClearAll);
public:
    void run(MycobotBasic &myCobot);
    static ServerBase* createInstance() {return new Calibration();}
};

#endif 