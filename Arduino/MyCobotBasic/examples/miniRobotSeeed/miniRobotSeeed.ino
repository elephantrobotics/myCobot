#include <MyCobotBasic.h>
#include <vector>
#include <string>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <map>
//#include <FlashStorage_SAMD.h>
#include "MycobotLogo.h"
#include "transponder.h"
#include "MainControl.h"
#include "Calibration.h"
#include "Information.h"
#include "config.h"
#include "Factory.h"
#include "ServerBase.h"

extern const unsigned char mycobot_bmp[153604];
TFT_eSPI tft;
MyCobotBasic myCobot;
//int address = 0;

static int state = 0;
static int display_start_state = 0;
static int display_pos = 0;
unsigned long t_begin = 0;
// bool EXIT = false;
int y_pos[] = {100, 125, 150, 175};
std::map<int, std::string> menuMap;

void setup()
{
    myCobot.setup();                                                                         //启动机械臂
    delay(50);
    tft.begin();
    tft.setRotation(3);
    DisplayStartUp();

    tft.fillScreen(TFT_BLACK);//黑色填充屏幕
    pinMode(WIO_5S_UP, INPUT_PULLUP);
    pinMode(WIO_5S_DOWN, INPUT_PULLUP);
    pinMode(WIO_5S_LEFT, INPUT_PULLUP);
    pinMode(WIO_5S_RIGHT, INPUT_PULLUP);

    /*state = EEPROM.read(address);
    Serial.print("read state====");
    Serial.println(state);*/

    menu_init();
    DisplayAll();
    menu_choice();
    t_begin = millis();
    Serial.println("start");
}

void loop()
{
    if (digitalRead(WIO_5S_DOWN) == LOW) {
        state += 1;
        t_begin = millis();
        menu_choice();
    }
    if (digitalRead(WIO_5S_UP) == LOW) {
        state -= 1;
        t_begin = millis();
        menu_choice();
    }
    if (digitalRead(WIO_5S_RIGHT) == LOW) {
        /*EEPROM.begin(EEPROM_SIZE); //申请操作到地址4095,size=目标地址+1
        EEPROM.write(state_addr, state + 1); //写数据
        EEPROM.commit(); //保存更改的数据*/
        /*EEPROM.write(state, (uint8_t) analogRead(0));
        Serial.print("write state====");
        Serial.println(state);
        EEPROM.commit();*/
        tft.fillScreen(TFT_BLACK);//黑色填充屏幕
        program_selection(myCobot, state);
        t_begin = millis();
        DisplayAll();
        menu_choice();
    }
    delay(200);
}

void displayScreenProtect()
{
    //tft.drawJpg(mycobot_start_PIC, sizeof(mycobot_start_PIC), 0, 0, 320, 240);
    while (1) {
        if (digitalRead(WIO_5S_DOWN) == LOW || digitalRead(WIO_5S_UP) == LOW
                || digitalRead(WIO_5S_RIGHT) == LOW) {
            tft.fillScreen(TFT_BLACK);//黑色填充屏幕
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
void menu_init()
{
    menuMap.insert(std::make_pair(MAINCONTROL_INDEX, "Maincontrol"));
    menuMap.insert(std::make_pair(CALIBRATION_INDEX, "Calibration"));
    menuMap.insert(std::make_pair(TRANSPONDER_INDEX, "Transponder"));
    menuMap.insert(std::make_pair(CONNECT_INDEX, "Information"));

}

void menu_choice()
{
    int temp_start_state = display_start_state;
    int temp_pos = display_pos;
    if (state < 0) {
        state = menuMap.size() - 1;
        display_start_state = state - 3;
        display_pos = 3;
    }
    if (state > (menuMap.size() - 1)) {
        state = 0;
        display_start_state = 0;
        display_pos = 0;
    }

    if (display_pos == 3 && (state - display_start_state) > 3) {
        display_start_state = state - 3;
    }
    if (display_pos == 0 && (state - display_start_state) < 0) {
        display_start_state = state;
    }
    if ((state - display_start_state) <= 3) {
        display_pos = state - display_start_state;
    }

    if (temp_start_state != display_start_state) {
        DisplayState(display_start_state);
    }

    if (temp_pos != display_pos) {
        DisplayPos(display_pos);
    }

}
void DisplayPos(int display_pos)
{
    tft.fillRect(0, 100, 26, 90, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(0, y_pos[display_pos]);
    tft.setTextColor(TFT_WHITE);
    tft.print(" >");
}

void DisplayState(int display_start_state)
{
    if (display_start_state > menuMap.size() - 4) {
        return;
    }
    tft.fillRect(26, 100, 200, 90, TFT_BLACK);
    for (int i = 0; i < 4; i++) {
        tft.setTextSize(2);
        tft.setCursor(30, y_pos[i]);
        tft.setTextColor(TFT_WHITE);
        tft.print(menuMap[display_start_state + i].c_str());
    }
}

void DisplayAll()
{
    unsigned long t_begin = millis();
    tft.fillScreen(TFT_BLACK);//黑色填充屏幕
    tft.setTextSize(3);
    tft.setTextColor(TFT_RED);
    tft.setCursor(20, 10);
    tft.println(TYPE);
    tft.setTextSize(2);
    tft.setCursor(20, 40);
    tft.print("miniRobot");

    tft.setTextSize(2);
    tft.setCursor(250, 60);
    tft.setTextColor(GREY);
    tft.print("v1.0");

    tft.drawFastHLine(0, 75, 320, GREY);

    //tft.drawJpg(ToDown, sizeof(ToDown), 10, 200, 12, 20);

    DisplayState(display_start_state);
    DisplayPos(display_pos);
}


void DisplayStartUp()
{
    tft.pushImage(0, 0, 320, 240, (uint16_t *)mycobot_bmp);
    //drawImage<uint16_t>("test.bmp", 0, 0);

    delay(2000);
}
