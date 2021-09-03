#ifndef _SERVERBASE_H_
#define _SERVERBASE_H_
#include <MyPartnerBasic.h>
class ServerBase{
public:
    ServerBase();
    ~ServerBase();
    virtual void run(MyPartnerBasic &myCobot) = 0;
};



#endif