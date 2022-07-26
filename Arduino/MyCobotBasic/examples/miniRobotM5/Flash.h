#ifndef Flash_h
#define Flash_h

#include "MyCobotBasic.h"
#include "config.h"
#include "ServerBase.h"
#include <esp_sleep.h>

class Flash: public ServerBase
{
private:
    void info();
    void SetIo();
    void SetInfo();
public:
    void run(MyCobotBasic &myCobot);
    static ServerBase *createInstance()
    {
        return new Flash();
    }
};

#endif
