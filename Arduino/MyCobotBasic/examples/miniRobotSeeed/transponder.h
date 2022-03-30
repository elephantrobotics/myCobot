#ifndef transponder_h
#define transponder_h

#include <MyCobotBasic.h>
#include "config.h"
#include <vector>
#include "ServerBase.h"
#include <TFT_eSPI.h>
#include <WiFiMulti.h>
#include <rpcWiFi.h>

#define MAX_SRV_CLIENTS 1

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
    bool CreateWlanServer();
    void WlanTransponder();
    void ConnectingInfo();
    void ConnectedInfo();
    void SetBaud();
    String GetWlanInfo();
    void SendData(int *data, int len);
public:
    void run(MyCobotBasic &myCobot);
    void init();
    static ServerBase *createInstance()
    {
        return new Transponder();
    }
private:
    TFT_eSPI tft;
    int pos_y[3] = {90, 120};
    int rect1[4] = {0, 90, 26, 60};
    int rect2[4] = {26, 90, 200, 60};
    DisplayTemplate distep;
    WiFiMulti wifiMulti;
    String ssid = "";
    String password = "";
    uint16_t server_port = 9000;
    IPAddress ip;
    bool wifi_state = false;
    int transponder_mode{0};
    WiFiClient serverClients[MAX_SRV_CLIENTS];
};

#endif
