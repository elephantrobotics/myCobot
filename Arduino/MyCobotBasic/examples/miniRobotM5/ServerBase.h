#ifndef _SERVERBASE_H_
#define _SERVERBASE_H_
#include <MyCobotBasic.h>
class ServerBase
{
public:
    ServerBase();
    ~ServerBase();
    virtual void run(MyCobotBasic &myCobot) = 0;
};



#endif
