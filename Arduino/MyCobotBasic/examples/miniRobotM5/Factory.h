#ifndef _FACTORY_H_
#define _FACTORY_H_

#include "ServerBase.h"
#include "MainControl.h"
#include "Calibration.h"
#include "transponder.h"
#include "Information.h"
#if defined MyCobot_Pro_350
#include "Flash.h"
#endif

typedef ServerBase *(*ServerFunction)();
class Factory
{
public:
    Factory();
    ~Factory();
    void addServer(int index, ServerFunction instanceServer);
    int deleteServer(int index);
    ServerBase *getServerInstance(int index);
    static Factory *getFactoryInstance()
    {
        return new Factory();
    }
public:
    std::map<int, ServerFunction> mFactoryMap;
};

#endif
