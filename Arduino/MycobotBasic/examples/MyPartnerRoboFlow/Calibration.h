#ifndef Calibration_h
#define Calibration_h

#include <MyPartnerBasic.h>
#include "config.h"
#include "ServerBase.h"


class Calibration: public ServerBase{
private:
    void info();
    void init(MyPartnerBasic &myCobot);
    void test(MyPartnerBasic &myCobot);
    void reset(MyPartnerBasic &myCobot);
    void DisplayHead(bool isClearAll);
public:
    void run(MyPartnerBasic &myCobot);
    static ServerBase* createInstance() {return new Calibration();}
};

#endif 