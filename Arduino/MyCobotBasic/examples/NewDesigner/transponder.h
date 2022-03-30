#ifndef transponder_h
#define transponder_h

#include <MyCobotBasic.h>
#include "config.h"
#include "ServerBase.h"
#include <WiFi.h>
#include <vector>
#include <string>

using namespace std;

#define MAX_SRV_CLIENTS 1
#define REMOVE_BONDED_DEVICES 0
#define PAIR_MAX_DEVICES 20

class Transponder: public ServerBase
{
private:
    bool EXIT = false;
    bool checkHeader(MyCobotBasic &myCobot);
    void EventResponse(MyCobotBasic &myCobot);
    int  readSerial(MyCobotBasic &myCobot, unsigned char *nDat, int nLen);
    void rFlushSerial();
    int  readData(MyCobotBasic &myCobot);
    void connect_ATOM(MyCobotBasic &myCobot);
    void info();
    void CreateWlanServer();
    void WlanTransponder();
    void ConnectingInfo();
    void ConnectedInfo();
    void SetBaud();
    string GetWlanInfo();
    void BTConnectedInfo();
    void BTWaitInfo();
    void SendData(int *data, int len);
    void ConnectFailedInfo(bool flag);
    void TimeOutInfo();
public:
    void run(MyCobotBasic &myCobot);
    void init();
    static ServerBase *createInstance()
    {
        return new Transponder();
    }
    void BTConnectingInfo(uint32_t numVal);
private:
#ifdef BOARD_M5_BASIC
    BoardBasic *board = new M5Board();
#elif defined BOARD_SEEED_WIO
    BoardBasic *board = new SeeedBoard();
#endif
    bool state_on {false};
    int pos_y[4] = {70, 100, 130, 160};
    int rect1[4] = {0, 70, 26, 120};
    int rect2[4] = {26, 70, 200, 120};
    DisplayTemplate distep;
    string ssid = "ElephantWiFi";
    string password = "Aria6666";
    string bak_ssid;
    string bak_password;
    string i_ssid = "ssid: ";
    string i_password = "pssword: ";
    bool is_first{true};//是否未输入ssid、pwd
    uint16_t server_port = 9000;
    IPAddress ip;
    bool wifi_state = false;
    int transponder_mode{0};
    WiFiClient serverClients[MAX_SRV_CLIENTS];
    bool wlan_uart{true};
    bool is_timeout{false};
    //bt
    String Bt_name = "mycobot280-m5";
    uint8_t mac_addr[6] = {0};//定义Mac地址存储空间
    char bda_str[18];
    bool loop_on{false};
    bool is_paired{false};
};

#endif
