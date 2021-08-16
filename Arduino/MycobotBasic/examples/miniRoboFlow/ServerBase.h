#ifndef _SERVERBASE_H_
#define _SERVERBASE_H_
#include <MycobotBasic.h>
class ServerBase{
public:
    ServerBase();
    ~ServerBase();
    virtual void run(MycobotBasic &myCobot) = 0;
};



#endif