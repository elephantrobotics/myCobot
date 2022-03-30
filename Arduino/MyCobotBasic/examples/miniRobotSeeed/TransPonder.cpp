#include "transponder.h"

// MyCobotBasic myCobot;

// #define
typedef  unsigned char u8;
WiFiServer server(9000);

void Transponder::init()
{
    // myCobot.setup();
    // myCobot.powerOn();
    pinMode(15, OUTPUT); // 1
    pinMode(5, OUTPUT); // 2
    pinMode(35, INPUT); // 2
    pinMode(36, INPUT); // 2
    delay(100);
    digitalWrite(15, 1); // 1
    digitalWrite(5, 1); // 2
    tft.fillScreen(TFT_BLACK);//黑色填充屏幕
    tft.setRotation(3);

    distep.y_pos = pos_y;
    distep.rect_pos1 = rect1;
    distep.rect_pos2 = rect2;

    info();
}

void Transponder::run(MyCobotBasic &myCobot)
{
    init();
    EXIT = false;
    while (!EXIT) {
        EventResponse(myCobot);
    }


}

bool Transponder::checkHeader(MyCobotBasic &myCobot)
{
    u8 bDat;
    u8 bBuf[2] = { 0, 0 };
    u8 Cnt = 0;
    while (true) {
        if (!readSerial(myCobot, &bDat, 1)) {
            return 0;
        }
        bBuf[1] = bBuf[0];
        bBuf[0] = bDat;
        if (bBuf[0] == HEADER && bBuf[1] == HEADER) {
            break;
        }
        ++Cnt;
        if (Cnt > 64)
            return 0;
    }
    return 1;
}

//按钮事件的响应 --》need place run
void Transponder::EventResponse(MyCobotBasic &myCobot)
{
    if (digitalRead(WIO_5S_DOWN) == LOW) {
        distep.state += 1;
        distep.MenuChoice();
    }
    if (digitalRead(WIO_5S_UP) == LOW) {
        distep.state -= 1;
        distep.MenuChoice();
    }
    if (digitalRead(WIO_5S_RIGHT) == LOW) {
        switch (distep.state) {
            case 0: {
                transponder_mode = 0;
                connect_ATOM(myCobot);
                /*if (digitalRead(WIO_5S_RIGHT) == LOW) {
                  SetBaud();
                }*/
                while (true) {
                    readData(myCobot);
                    if (digitalRead(WIO_5S_LEFT) == LOW) {
                        info();
                        break;
                    }
                }
            }
            break;
            case 1: {
                ConnectingInfo();
                while (ssid == "" || password == "") {
                    transponder_mode = 0;
                    readData(myCobot);
                }
                transponder_mode = 1;
                if (CreateWlanServer()) {
                    ConnectedInfo();
                    while (true) {
                        WlanTransponder();
                        readData(myCobot);
                        if (digitalRead(WIO_5S_LEFT) == LOW) {
                            info();
                            break;
                        } else if (digitalRead(WIO_5S_RIGHT) == LOW) {
                            WiFi.disconnect();
                            server.stop();
                            ConnectingInfo();
                            if (CreateWlanServer())
                                ConnectedInfo();
                        }
                    }
                }
            }
            WiFi.disconnect();
            server.stop();
            break;
            default:
                break;
        }
    }
    delay(200);
    if (digitalRead(WIO_5S_LEFT) == LOW) {
        EXIT = true;
    }
}

int Transponder::readSerial(MyCobotBasic &myCobot, unsigned char *nDat,
                            int nLen)
{
    int Size = 0;
    int rec_data;
    unsigned long t_begin = millis();
    unsigned long t_use;

    while (true) {
        if ((Serial.available() > 0) || (serverClients[0]
                                         && serverClients[0].connected() && serverClients[0].available() > 0)) {
            if (transponder_mode == 0)
                rec_data = Serial.read();   // readSerial
            else if (transponder_mode == 1) {
                rec_data = serverClients[0].read();
//        Serial.print("data==");
//        Serial.println(rec_data);
            } else
                break;
            Serial1.write(rec_data);
            if (rec_data != IORecWrong) {
                if (nDat)
                    nDat[Size] = rec_data;
                ++Size;
                t_begin = millis();
            }
            if (Size >= nLen)
                break;
            t_use = millis() - t_begin;

            if (t_use > IO_TimeOut)
                break;
        } else if (Serial1.available() > 0) {     // If anything comes in Serial 2
            if (transponder_mode == 0) {
                Serial.write(Serial1.read());    // read it and send it out Serial (USB)
            } else if (transponder_mode == 1) {
                size_t len = Serial1.available();
                uint8_t sbuf[len];
                Serial1.readBytes(sbuf, len);
                if (serverClients[0] && serverClients[0].connected())
                    serverClients[0].write(sbuf, len);
            }
        } /*else if (serverClients[0] && serverClients[0].connected() && serverClients[0].available() > 0) {
        rec_data = serverClients[0].read();   // readSerial
        Serial.print("rec_data");
        Serial.println(rec_data);
        Serial1.write(rec_data);
        if (rec_data != IORecWrong)
        {
          if (nDat)
            nDat[Size] = rec_data;
            ++Size;
            t_begin = millis();
        }
        if (Size >= nLen)
          break;
        t_use = millis() - t_begin;

        if (t_use > IO_TimeOut)
          break;
      } else if(SerialBT.available()>0) {
        rec_data = SerialBT.read();   // readSerial
        Serial1.write(rec_data);
        if (rec_data != IORecWrong)
        {
          if (nDat)
            nDat[Size] = rec_data;
            ++Size;
            t_begin = millis();
        }
        if (Size >= nLen)
          break;
        t_use = millis() - t_begin;

        if (t_use > IO_TimeOut)
          break;
    }*/ else {
            if (transponder_mode == 0) {
                if (digitalRead(WIO_5S_LEFT) == LOW) {
                    break;
                }
            } else if (transponder_mode == 1) {
                break;//server not only call readdata
            }
        }
    }
    return Size;
}

void Transponder::rFlushSerial()
{
    while (Serial.read() != -1)
        ;
}

void Transponder::SendData(int *data, int len)
{
    std::vector<int> vector;
    vector.push_back(0xfe);
    vector.push_back(0xfe);
    for (int i = 0; i < len; i++) {
        vector.push_back(data[i]);
    }
    vector.push_back(0xfa);
    for (int i = 0; i < len + 3; i++) {
        if (transponder_mode == 0) {
            Serial.write(vector[i]);
        } else if (transponder_mode == 1) {
            serverClients[0].write(vector[i]);
        }
    }
}

int Transponder::readData(MyCobotBasic &myCobot)
{
    rFlushSerial();
    if (!Transponder::checkHeader(myCobot)) {
        return -1;
    }

    u8 data_len[1];
    u8 r_data_4[4];
    u8 r_data_2[2];
    u8 r_data_3[3];
    if (Transponder::readSerial(myCobot, data_len, 1) != 1) {
        return -1;
    }
    switch (static_cast<int>(data_len[0])) {
        //b0-ssid b1-pwd b2-port
        case 2: {
            Transponder::readSerial(myCobot, r_data_2, 2);
            switch (int(r_data_2[0])) {
                case 0xb0: {
                    int data[2] = {0x02, 0xb0};
                    SendData(data, sizeof(data) / sizeof(data[0]));
                    delay(20000);//wait 20ms
                    ssid = GetWlanInfo();
//           Serial.print("ssid===");
//           Serial.println(ssid.c_str());
                    SendData(data, sizeof(data) / sizeof(data[0]));
                }
                break;
                case 0xb1: {
                    int data[2] = {0x02, 0xb1};
                    SendData(data, sizeof(data) / sizeof(data[0]));
                    delay(20000);//wait 20ms
                    password = GetWlanInfo();
                    //Serial.print("password===");
                    //Serial.println(password.c_str());
                    SendData(data, sizeof(data) / sizeof(data[0]));
                }
                break;
            }
        }
        break;
        case 4:
            Transponder::readSerial(myCobot, r_data_4, 4);
            switch (int(r_data_4[0])) {
                case 0xb2: {
                    uint8_t high_port = r_data_4[1];//fe fe 04 b2 port fa
                    uint8_t low_port = r_data_4[2];
                    server_port = (high_port << 8) | low_port;
                    int data[4] = {0x04, 0xb2, high_port, low_port};
                    SendData(data, sizeof(data) / sizeof(data[0]));
                }
                break;
                case 0xa0: {
                    //0xfe 0xfe 0x04 0xa0 pin_no pin_data 0xfa
                    byte pin_no = r_data_4[1];
                    pinMode(pin_no, OUTPUT);
                    delay(5);
                    bool pin_data = r_data_4[2];
                    digitalWrite(pin_no, pin_data);
                    int data[4] = {0x04, 0xa0, pin_no, pin_data};
                    SendData(data, sizeof(data) / sizeof(data[0]));
                }
                break;
            }
            break;
        case 3:
            Transponder::readSerial(myCobot, r_data_3, 3);
            switch (int(r_data_3[0])) {
                case 0xa1: {
                    byte pin_no = r_data_3[1];
                    pinMode(pin_no, INPUT);
                    delay(5);
                    bool pin_state = digitalRead(pin_no);
                    delay(5);
                    int data[4] = {0x03, 0xa1, pin_no, pin_state};
                    SendData(data, sizeof(data) / sizeof(data[0]));
                }
                break;
            }
            break;

        default: {
            //此处逻辑后面可能需要修改，兼顾server，server除2 3 4指令长度外没问题，暂时不改
            if (transponder_mode == 0) {
                while (Serial.available() > 0) {
                    Serial1.write(Serial.read());
                }
                while (Serial1.available() > 0) {
                    Serial.write(Serial1.read());
                }
            }
        }
        break;
    }
    return 0;
}

void Transponder::connect_ATOM(MyCobotBasic &myCobot)
{
    tft.fillScreen(TFT_BLACK);//黑色填充屏幕
    delay(50);
    tft.setTextColor(TFT_RED);
    tft.setTextSize(2);
    tft.setCursor(55, 20);
    tft.println("Connect test");
    tft.drawFastHLine(0, 70, 320, GREY);

    tft.setCursor(10, 120);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    tft.print("Atom: ");
    tft.setTextColor(TFT_GREEN);
    int state = myCobot.isPoweredOn();
    if (state == 1) {
        tft.println("ok");
    } else {
        tft.println("no");
    }
    /*tft.setCursor(220, 210);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    tft.print("Set Baud"); */
    //delay(1000);
    //info();
}

void Transponder::info()
{
    tft.fillScreen(TFT_BLACK);//黑色填充屏幕
    tft.setTextColor(TFT_BLACK);
    tft.setTextColor(TFT_RED);
    tft.setTextSize(3);
    tft.setCursor(10, 10);
    tft.printf(TYPE);
    tft.setCursor(10, 40);
    tft.drawFastHLine(0, 70, 320, GREY);
    tft.setTextSize(2);
    tft.println("Basic Transponder");

    String menu[3] = {"USB UART", "WLAN Server"};
    int num[2] = {0, 1};
    distep.MenuInit(num, menu, 2);
    distep.MenuChoice();

    distep.Start();
    delay(10);
}

bool Transponder::CreateWlanServer()
{
    bool flag = false;
    WiFi.disconnect();
    delay(500);
    wifiMulti.addAP(ssid.c_str(), password.c_str());
    Serial.println("Connecting Wifi ");
    for (int loops = 10; loops > 0; loops--) {
        if (wifiMulti.run() == WL_CONNECTED) {
            flag = true;
            Serial.println("");
            Serial.print("WiFi connected ");
            Serial.print("IP address: ");
            ip = WiFi.localIP();
            Serial.println(ip);
            break;
        } else {
            Serial.println(loops);
            Serial.print("loops:");
            Serial.println(loops);
            Serial.println("connecting");
            delay(1000);
        }
    }
    if (wifiMulti.run() != WL_CONNECTED) {
        Serial.println("WiFi connect failed");
        delay(1000);
    }
    server.begin(server_port);
    server.setNoDelay(true);
    return flag;
}

void Transponder::WlanTransponder()
{
    uint8_t i;
    if (wifiMulti.run() == WL_CONNECTED) {
        //check if there are any new clients
        if (server.hasClient()) {
            for (i = 0; i < MAX_SRV_CLIENTS; i++) {
                Serial.println("have client");
                //find free/disconnected spot
                if (!serverClients[i] || !serverClients[i].connected()) {
                    if (serverClients[i]) serverClients[i].stop();
                    serverClients[i] = server.available();
                    if (!serverClients[i]) Serial.println("available broken");
                    Serial.print("New client: ");
                    Serial.print(i);
                    Serial.print(' ');
                    Serial.println(serverClients[i].remoteIP());
                    break;
                }
            }
            if (i >= MAX_SRV_CLIENTS) {
                //no free/disconnected spot so reject
                server.available().stop();
            }
        }
    } else {
        Serial.println("WiFi not connected!");
        for (i = 0; i < MAX_SRV_CLIENTS; i++) {
            if (serverClients[i]) serverClients[i].stop();
        }
        delay(1000);
    }
}

void Transponder::ConnectingInfo()
{
    tft.fillScreen(TFT_BLACK);//黑色填充屏幕
    tft.fillRect(0, 0, 320, 30, GREY);
    tft.setBitmapColor(GREY, GREY);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.setCursor(10, 10);
    tft.println(ssid);
    tft.setTextColor(TFT_WHITE);
    tft.setBitmapColor(TFT_BLACK, TFT_BLACK);
    tft.setCursor(10, 80);
    tft.setTextSize(2);
    tft.print("WIFI Connecting");
}

void Transponder::ConnectedInfo()
{
    tft.fillScreen(TFT_BLACK);//黑色填充屏幕
    tft.fillRect(0, 0, 320, 30, GREY);
    tft.setBitmapColor(GREY, GREY);
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(2);
    tft.setCursor(10, 10);
    tft.println(ssid);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(10, 80);
    tft.setTextSize(2);
    tft.print("WIFI Connected");
    //tft.fillRect(10, 108, 220, 60, GREY);
    tft.setCursor(10, 110);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    tft.print("ip: ");
    tft.setTextColor(TFT_RED);
    tft.println(ip);
    tft.setCursor(10, 140);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    tft.print("port: ");
    tft.setTextColor(TFT_RED);
    tft.println(server_port);
    tft.setCursor(200, 220);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    tft.println("ReConnect");
}

void Transponder::SetBaud()
{

}

String Transponder::GetWlanInfo()
{
    String str = "";
    while (Serial.available() > 0) {
        str += (char)Serial.read();
    }
    while (serverClients[0].available() > 0) {
        str += (char)serverClients[0].read();
    }
    return str;
}
