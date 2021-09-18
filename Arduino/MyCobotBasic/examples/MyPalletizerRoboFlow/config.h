#ifndef Config_h
#define Config_h

#include <MyCobotLanguage.h>

enum FuncIndex: int {
    MAINCONTROL_INDEX = 0,
    CALIBRATION_INDEX,
    TRANSPONDER_INDEX,
    CONNECT_INDEX
};

#define lan 1

#define GREY 0x5AEB

#define state_addr 0X0f

#define HEADER 0XFE

#endif
