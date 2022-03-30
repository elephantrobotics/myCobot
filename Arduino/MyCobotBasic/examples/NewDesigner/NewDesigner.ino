#include "config.h"

#include <MyCobotBasic.h>
#include <vector>
#include <string>
#include <map>
#include "MycobotLogo.h"
#include "transponder.h"
#include "MainControl.h"
#include "Calibration.h"
#include "Information.h"
#include "Factory.h"
#include "ServerBase.h"

#define EEPROM_SIZE 4096

extern const unsigned char mycobot_bmp[153604];
MyCobotBasic myCobot;
#ifdef BOARD_M5_BASIC
BoardBasic *board = new M5Board();
#elif defined BOARD_SEEED_WIO
BoardBasic *board = new SeeedBoard();
#endif
DisplayTemplate distep;

unsigned long t_begin = 0;
// bool EXIT = false;
int y_pos[4] = {90, 115, 140, 165};
int rect1[4] = {0, 90, 26, 120};
int rect2[4] = {26, 90, 200, 120};

bool state_on{false};

void setup()
{
    board->FixBtnClicked();
    myCobot.setup();
    //启动机械臂
    delay(50);
    board->Seeedbegin();
    board->SetRotation(3);
    Serial.println("start");
    board->EepromBegin(EEPROM_SIZE);
    //两个功能下打开串口有用：wlan、uart
    if (byte(board->EepromRead(state_addr)) == 0
            || byte(board->EepromRead(state_addr)) == 1) {
        distep.state = 2;
        state_on = true;
    }

    DisplayStartUp();

    board->ClearScreen(Board_BLACK);//黑色填充屏幕
    board->BtnInit();
    Serial.println("Next");
    distep.y_pos = y_pos;
    distep.rect_pos1 = rect1;
    distep.rect_pos2 = rect2;
    int num[4] = {MAINCONTROL_INDEX, CALIBRATION_INDEX, TRANSPONDER_INDEX, CONNECT_INDEX};
    string menu[4] = {"Maincontrol", "Calibration", "Transponder", "Information"};
    distep.MenuInit(num, menu, 4);
    DisplayAll();
    distep.MenuChoice();
    t_begin = millis();
}

void loop()
{
    board->BtnUpdate();
    if (board->IsBtnClicked(0)) {
        distep.state += 1;
        t_begin = millis();
        distep.MenuChoice();
    } else if (board->IsBtnClicked(1)) {
        distep.state -= 1;
        t_begin = millis();
        distep.MenuChoice();
    } else if (board->IsBtnClicked(2) || state_on) {
        board->ClearScreen(Board_BLACK);//黑色填充屏幕
        state_on = false;
        program_selection(myCobot, distep.state);
        t_begin = millis();
        DisplayAll();
        distep.MenuChoice();
    }
    delay(200);
}

void displayScreenProtect()
{
    //board->drawJpg(mycobot_start_PIC, sizeof(mycobot_start_PIC), 0, 0, 320, 240);
    while (1) {
        if (board->IsBtnClicked(0) || board->IsBtnClicked(1)
                || board->IsBtnClicked(2)) {
            board->ClearScreen(Board_BLACK);//黑色填充屏幕
            DisplayAll();
            t_begin = millis();
            break;
        }
    }
}

void program_selection(MyCobotBasic &myCobot, int state)
{
    Factory *factory = Factory::getFactoryInstance();
    ServerBase *server = factory->getServerInstance(state);
    if (server == nullptr) {
        Serial.println("there is no server");
        return;
    }
    server->run(myCobot);
}

void DisplayAll()
{
    unsigned long t_begin = millis();
    board->ClearScreen(Board_BLACK);//黑色填充屏幕
    board->SetTextSize(3);
    board->SetTextColor(Board_RED);
    board->SetCursor(20, 10);
    board->Println(TYPE);
    board->SetTextSize(2);
    board->SetCursor(20, 40);
    board->Print("miniRobot");

    board->SetTextSize(2);
    board->SetCursor(250, 60);
    board->SetTextColor(Board_GREY);
    board->Print("v1.0");

    board->DrawFastHLine(0, 75, 320, Board_GREY);

    //board->drawJpg(ToDown, sizeof(ToDown), 10, 200, 12, 20);

    distep.Start();
}

void DisplayStartUp()
{
    board->PushImage(0, 0, 320, 240, (uint16_t *)mycobot_bmp);
    //drawImage<uint16_t>("test.bmp", 0, 0);

    delay(2000);
}
