#ifndef Calibration_h
#define Calibration_h

#include <MyPalletizerBasic.h>
#include "config.h"
#include "ServerBase.h"


class Calibration: public ServerBase
{
private:
    void info();
    void init(MyPalletizerBasic &myCobot);
    void test(MyPalletizerBasic &myCobot);
    void reset(MyPalletizerBasic &myCobot);
    void DisplayHead(bool isClearAll);
public:
    void run(MyPalletizerBasic &myCobot);
    static ServerBase *createInstance()
    {
        return new Calibration();
    }
};

#endif