#ifndef Information_h
#define Information_h

#include "MyCobotBasic.h"
#include "config.h"
#include "ServerBase.h"

class Connect: public ServerBase
{
private:
    void info();
    template <typename T>
    void testServo(T &myCobot);
    void ReadConfig(T &myCobot);
public:
    void run(T &myCobot);
    static ServerBase *createInstance()
    {
        return new Connect();
    }
};

#endif
