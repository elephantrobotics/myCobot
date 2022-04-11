#ifndef transponder_h
#define transponder_h

#include <MyPalletizerBasic.h>
#include "config.h"
#include "ServerBase.h"
#include <WiFi.h>
#include <vector>
#include <string>
#include <BluetoothSerial.h>
#include "TOF.h"

using namespace std;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#define ARDUINOOSC_DEBUGLOG_ENABLE
//#include <ArduinoOSC.h>

#define MAX_SRV_CLIENTS 1
#define REMOVE_BONDED_DEVICES 0
#define PAIR_MAX_DEVICES 20

class Transponder: public ServerBase
{
private:
    bool checkHeader(vector<unsigned char> v_data);
    bool HandleStickyPackets(vector<unsigned char> &temp,
                             vector<unsigned char> &v_data);
    bool HandleAtomData(vector<unsigned char> &v_data);
    void EventResponse(MyPalletizerBasic &myCobot);
    static void UITemplate(vector<unsigned short> color, vector<unsigned char> size,
                           vector<short> x, vector<short> y, vector<string> msg, vector<int> line_feed);
    void rFlushSerial();
    void connect_ATOM(MyPalletizerBasic &myCobot);
    void info();
    void CreateWlanServer();
    void WlanTransponder();
    void ConnectingInfo();
    void ConnectedInfo();
    void SetBaud();
    string GetWlanInfo();
    void BTConnectedInfo();
    void BTWaitInfo();
    void CreateBTServer();

    void GetUserData(string &data);
    void GetUserData(vector<unsigned char> &data);
    void SendDataToUser(vector<unsigned char> &v_data);
    void SendDataToUser(const string str_data);
    void GetAtomData(vector<unsigned char> &data);
    void SendDataToAtom(vector<unsigned char> &v_data);
    bool HandleOtherMsg(vector<unsigned char> &v_data);

    void ConnectFailedInfo(bool flag);
    void TimeOutInfo();
    void GetTOFDistance();

public:
    void run(MyPalletizerBasic &myCobot);
    void init();
    static ServerBase *createInstance()
    {
        return new Transponder();
    }
    static void BTConnectingInfo(uint32_t numVal);

    //task call
    void readData();

    //task
    static void TaskReadData(void *p);

private:
    bool EXIT = false;
    bool state_on{false};
    int pos_y[4] = {70, 100, 130, 160};
    int rect1[4] = {0, 70, 26, 120};
    int rect2[4] = {26, 70, 200, 120};
    DisplayTemplate distep;
    string ssid = "EleWiFiTest";
    string password = "ele123456";
    string bak_ssid;
    string bak_password;
    string i_ssid = "ssid: ";
    string i_password = "pssword: ";
    //Whether ssid and pwd are not entered
    bool is_first{true};
    uint16_t server_port = 9000;
    IPAddress ip;
    bool wifi_state = false;
    WiFiClient serverClients[MAX_SRV_CLIENTS];
    bool wlan_uart{true};
    bool is_timeout{false};
    //bt
    BluetoothSerial SerialBT;
    String Bt_name = "mycobot280-m5";
    uint8_t pairedDeviceBtAddr[PAIR_MAX_DEVICES][6];
    //Define Mac address storage space
    uint8_t mac_addr[6] = {0};
    char bda_str[18];
    bool loop_on{false};
    bool is_paired{false};
    TOF tof;
    enum MODE : int {Uart = 0, Wlan = 1, Bt = 2, Exit = 3} transponder_mode;
};

#endif
