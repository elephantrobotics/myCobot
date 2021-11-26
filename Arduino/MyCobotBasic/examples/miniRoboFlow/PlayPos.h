#ifndef PlayPos_h
#define PlayPos_h

#include <MyCobotBasic.h>
#include "config.h"
#include "ServerBase.h"


class PlayPos: public ServerBase {
private:
    void displayPointInfo( MyCobotBasic& myCobot, int mode, byte n);
    void update(MyCobotBasic& myCobot, byte btn_pressed);
    //void displayInfo(MyCobotBasic &myCobot, byte mc_mode);
    //void record(MyCobotBasic &myCobot);  // is stop;
   void point_play(MyCobotBasic &myCobot);  
   // void playFromFlash(MyCobotBasic &myCobot);
   // void recordIntoFlash(MyCobotBasic &myCobot);
   void getIO(MyCobotBasic &myCobot);
   int setPoint(MyCobotBasic& myCobot, int mode, byte pSetmode);
   void setPointInfo(MyCobotBasic& myCobot, int mode, byte Infomode);
    // bool checkDataLen();
    //void prgramming(MyCobotBasic& myCobot);
public:
    void run(MyCobotBasic &myCobot);
    static ServerBase* createInstance() {return new PlayPos();}
};

#endif