#ifndef Calibration_h
#define Calibration_h

#include <MycobotBasic.h>
#include "config.h"



class Calibration
{
private:
    void info();
    void init(MycobotBasic &myCobot);
    void test(MycobotBasic &myCobot);
    void reset(MycobotBasic &myCobot);
public:
    void bration(MycobotBasic &myCobot);
};

#endif 