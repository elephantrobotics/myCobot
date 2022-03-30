#ifndef _SERVERBASE_H_
#define _SERVERBASE_H_
#include <MyPalletizerBasic.h>
class ServerBase
{
public:
    ServerBase();
    ~ServerBase();
    virtual void run(MyPalletizerBasic &myCobot) = 0;
};



#endif