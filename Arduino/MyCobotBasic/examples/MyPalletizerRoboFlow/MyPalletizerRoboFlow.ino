#include <MyPalletizerBasic.h>
#include <vector>
#include <string>
#include "transponder.h"
#include "MainControl.h"
#include "Calibration.h"
#include "Information.h"
#include "config.h"
#include "Factory.h"
#include "ServerBase.h"
#include <driver/adc.h>

extern const unsigned char mycobot_start_PIC[29523];


MyPalletizerBasic myCobot;

static int state = 0;
static int display_start_state = 0;
static int display_pos = 0;
unsigned long t_begin = 0;
// bool EXIT = false;
int y_pos[] = {70, 95, 120, 145};
std::map<int, std::string> menuMap;
bool state_on{false};

void setup()
{
    adc_power_acquire();
    myCobot.setup();
    //myCobot.powerOn();                                    //启动机械臂
    delay(50);

    if (!EEPROM.begin(EEPROM_SIZE)) {
        Serial.println("failed to initialise EEPROM");
        delay(1000000);
    }
    Serial.print("read data==");
    Serial.println(byte(EEPROM.read(state_addr)));
    //两个功能下打开串口有用：wlan、uart
    if (byte(EEPROM.read(state_addr)) == 0 || byte(EEPROM.read(state_addr)) == 1) {
        state = 2;
        state_on = true;
    }

    DisplayStartUp();
    M5.Lcd.clear(BLACK);
    menu_init();
    DisplayAll();
    menu_choice();
    t_begin = millis();
}

void loop()
{

    M5.update();

    /*if ((millis() - t_begin) > 60000) {
      displayScreenProtect();
    }*/
    if (M5.BtnA.wasReleased()) {
        state += 1;
        t_begin = millis();
        menu_choice();
    }
    if (M5.BtnB.wasReleased()) {
        state -= 1;
        t_begin = millis();
        menu_choice();
    }
    if (M5.BtnC.wasReleased() || state_on) {
        // EEPROM.begin(EEPROM_SIZE); //申请操作到地址4095,size=目标地址+1
        // EEPROM.write(state_addr, state + 1); //写数据
        // EEPROM.commit(); //保存更改的数据
        state_on = false;
        program_selection(myCobot, state);
        M5.Lcd.clear(BLACK);
        t_begin = millis();
        DisplayAll();
        menu_choice();
    }
}

void displayScreenProtect()
{
    M5.Lcd.drawJpg(mycobot_start_PIC, sizeof(mycobot_start_PIC), 0, 0, 320, 240);
    while (1) {
        M5.update();
        if (M5.BtnA.wasReleased() || M5.BtnB.wasReleased() || M5.BtnC.wasReleased()) {
            M5.Lcd.clear(BLACK);
            DisplayAll();
            t_begin = millis();
            M5.update();
            break;
        }
    }
}

void program_selection(MyPalletizerBasic &myCobot, int state)
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
    M5.Lcd.fillRect(0, 70, 26, 90, BLACK);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(0, y_pos[display_pos]);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.print(" >");
}

void DisplayState(int display_start_state)
{
    if (display_start_state > menuMap.size() - 4) {
        return;
    }
    M5.Lcd.fillRect(26, 70, 200, 90, BLACK);
    for (int i = 0; i < 4; i++) {
        M5.Lcd.setTextSize(2);
        M5.Lcd.setCursor(30, y_pos[i]);
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.print(menuMap[display_start_state + i].c_str());
    }
}

void DisplayAll()
{
    unsigned long t_begin = millis();
    M5.Lcd.setTextSize(3);
    M5.Lcd.setTextColor(RED);
    M5.Lcd.setCursor(20, 10);
    M5.Lcd.print("miniRoboFlow");

    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(250, 30);
    M5.Lcd.setTextColor(GREY);
    M5.Lcd.print("v1.0");

    M5.Lcd.drawFastHLine(0, 45, 320, GREY);
    M5.Lcd.drawFastHLine(0, 195, 320, GREY);

    //M5.Lcd.drawJpg(ToDown, sizeof(ToDown), 10, 200, 12, 20);
    M5.Lcd.setCursor(35, 210);
    M5.Lcd.print(" DOWN ");
    //M5.Lcd.drawJpg(ToUp, sizeof(ToUp), 115, 200, 12, 20);
    M5.Lcd.setCursor(140, 210);
    M5.Lcd.print(" UP ");
    //M5.Lcd.drawJpg(ToRight, sizeof(ToRight), 210, 200, 20, 12);
    M5.Lcd.setCursor(235, 210);
    M5.Lcd.print(" OK ");

    DisplayState(display_start_state);
    DisplayPos(display_pos);
}


void DisplayStartUp()
{
    M5.Lcd.drawJpg(mycobot_start_PIC, sizeof(mycobot_start_PIC), 0, 0, 320, 240);
    //M5.Lcd.drawJpg(ToDown, sizeof(ToDown), 0, 0, 12, 20);
    //M5.Lcd.pushImage(0, 0, 320, 240, (uint16_t *)mycobot_start_PIC);
    delay(2000);
}
