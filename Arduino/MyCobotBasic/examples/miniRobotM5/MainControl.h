#ifndef MainControl_h
#define MainControl_h

#include <MyCobotBasic.h>
#include "config.h"
#include "ServerBase.h"

class MainControl: public ServerBase
{
private:
    void updateMode(MyCobotBasic &myCobot, byte btn_pressed);
    void displayInfo(MyCobotBasic &myCobot, byte mc_mode);
    void record(MyCobotBasic &myCobot);
    void play(MyCobotBasic &myCobot);
    void playFromFlash(MyCobotBasic &myCobot);
    void recordIntoFlash(MyCobotBasic &myCobot);
    void IO(MyCobotBasic &myCobot);
    bool IsInposition(MyCobotBasic &myCobot, Angles target_encoders, Angles move_encoders);
public:
    void run(MyCobotBasic &myCobot);
    static ServerBase *createInstance()
    {
        return new MainControl();
    }

public:
    //The maincontrol interface displays GDataFlash-->get data from flash SDataFlash-->save data to flash
    enum UI : int {Menu = 0, PlayMenu = 1, RecordMenu = 2, PlayRam = 11, PlayFlash = 12, RecordRam = 21, RecordFlash = 22, pause = 32,
                   RecordSave = 33, GDataFlash = 41, SDataFlash = 42, IoState = 51, NotPlay = 52, NoData = 53
                  } ui = (enum UI)0;
    //Button              
    enum BTN : int {A = 1, B, C} btn;
    bool gripper_state{false};
};

#endif
