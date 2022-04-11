#ifndef Config_h
#define Config_h

#include <MyCobotLanguage.h>
#include "DisplayTemplate.h"

#define TYPE "MyCobot"

enum FuncIndex : int {
    MAINCONTROL_INDEX = 0,
    CALIBRATION_INDEX,
    TRANSPONDER_INDEX,
    CONNECT_INDEX
};

//language settings
static enum LAN : int {English = 1, Chinese} language = (enum LAN)1;
#define GREY 0x5AEB
#define lan 1

#define state_addr 0X0f

#define HEADER 0XFE
#define END 0XFA

#define GET_TOF_DISTANCE 0xc0
#define SET_SSID_PWD 0XB0
#define GET_SSID_PWD 0xb1
#define SET_PORT 0xb2
#define SET_BASIC_OUT 0xa0
#define GET_BASIC_IN 0xa1

#endif
