#include "Factory.h"
#include "config.h"
#include <map>

Factory::Factory()
{
    addServer(MAINCONTROL_INDEX, &MainControl::createInstance);
    addServer(CALIBRATION_INDEX, &Calibration::createInstance);
    addServer(TRANSPONDER_INDEX, &Transponder::createInstance);
    addServer(CONNECT_INDEX, &Connect::createInstance);
}
Factory::~Factory()
{
//todo
}

void Factory::addServer(int index, ServerFunction instanceServer)
{
    mFactoryMap.insert(std::make_pair(index, instanceServer));
}

int Factory::deleteServer(int index)
{
    auto it = mFactoryMap.find(index);
    if (it != mFactoryMap.end()) {
        mFactoryMap.erase(it);
    } else {
        Serial.println("it has no this function!");
        return -1;
    }
    return 0;
}

ServerBase *Factory::getServerInstance(int index)
{
    if (mFactoryMap.count(index)) {
        return (*mFactoryMap[index])();
    }
    return nullptr;
}