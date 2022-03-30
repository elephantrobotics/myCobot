#include "transponder.h"

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

    distep.y_pos = pos_y;
    distep.rect_pos1 = rect1;
    distep.rect_pos2 = rect2;

    if (board->EepromRead(state_addr) == 0) {
        distep.state = 0;
        state_on = true;
    } else if (board->EepromRead(state_addr) == 1) {
        distep.state = 1;
        state_on = true;
    }
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
    board->BtnUpdate();
    if (board->IsBtnClicked(0)) {
        distep.state += 1;
        distep.MenuChoice();
        board->BtnUpdate();
    } else if (board->IsBtnClicked(1)) {
        distep.state -= 1;
        distep.MenuChoice();
        board->BtnUpdate();
    } else if (board->IsBtnClicked(2) || state_on) {
        board->EepromWrite(state_addr, byte(distep.state)); //写数据
        board->EepromCommit(); //保存更改的数据
        state_on = false;
        board->BtnUpdate();
        switch (distep.state) {
            case 0: {
                transponder_mode = 0;
                connect_ATOM(myCobot);
                while (true) {
                    readData(myCobot);
                    if (board->UartBtnExit()) {
                        info();
                        break;
                    }
                }
            }
            break;
            case 1: {
                ConnectingInfo();
                CreateWlanServer();
                while (true) {
                    board->BtnUpdate();
                    if (!wlan_uart) {
                        WlanTransponder();
                    }
                    readData(myCobot);
                    if (is_timeout) {
                        TimeOutInfo();
                        is_timeout = false;
                        delay(500);
                        if (!wlan_uart)
                            ConnectedInfo();
                        else
                            ConnectFailedInfo(false);
                    }
                    //超时时无点击事件响应
                    if (board->IsBtnClicked(0) && !is_timeout) {
                        info();
                        break;
                    } else if (board->IsBtnClicked(2) && !is_timeout) {
                        //如果没有使用串口，表示wifi连接成功，成功才断连，停服务
                        if (!wlan_uart) {
                            WiFi.disconnect();
                            server.stop();
                        }
                        ConnectingInfo();
                        CreateWlanServer();
                    }
                }
            }
            WiFi.disconnect();
            server.stop();
            break;
            default:
                break;
            case 2: {
                board->CreateBTServer(Bt_name);
                BTWaitInfo();
                transponder_mode = 2;
                while (true) {
                    board->BtnUpdate();
                    if (board->HasClient() && !loop_on) {
                        BTConnectedInfo();
                        board->SetNoConnect();//如果已经有连接，既不可发现也不可连接
                        loop_on = true;
                    } else if (!board->HasClient() && loop_on) {
                        BTWaitInfo();
                        board->SetConnect();
                        loop_on = false;
                    }
                    if (board->IsConfirmRequestPending()) {
                        if (board->IsBtnClicked(0)) {
                            board->ConfirmReply(true);
                        }
                    }
                    readData(myCobot);
                    if (board->UartBtnExit()) {
                        info();
                        break;
                    }
                }
            }
            board->End();
            break;
            case 3:
                EXIT = true;
                break;
        }
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
        if ((Serial.available() > 0) || (board->Available() > 0) || (serverClients[0]
                && serverClients[0].connected() && serverClients[0].available() > 0)) {
            if (transponder_mode == 0)
                rec_data = Serial.read();   // readSerial
            else if (transponder_mode == 1) {
                rec_data = serverClients[0].read();
            } else if (transponder_mode == 2)
                rec_data = board->Read();
            else
                break;
            board_serial.write(rec_data);
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
        } else if (board_serial.available() > 0) {     // If anything comes in Serial 2
            if (transponder_mode == 0) {
                Serial.write(board_serial.read());    // read it and send it out Serial (USB)
            } else if (transponder_mode == 1) {
                size_t len = board_serial.available();
                uint8_t sbuf[len];
                board_serial.readBytes(sbuf, len);
                if (serverClients[0] && serverClients[0].connected())
                    serverClients[0].write(sbuf, len);
            } else if (transponder_mode == 2) {
                board->Write(board_serial.read());
            }
        } else {
            if (transponder_mode == 0) {
                board->BtnUpdate();
                if (board->UartBtnExit() || (board->IsBtnClicked(0) && wlan_uart))
                    break;
            } else if (transponder_mode == 1 || transponder_mode == 2) {
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
    vector<int> vector;
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
        } else if (transponder_mode == 2) {
            board->Write(vector[i]);
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
        //b0-set ssid pwd  b1 get s+p b2-port
        case 2: {
            Transponder::readSerial(myCobot, r_data_2, 2);
            switch (int(r_data_2[0])) {
                case 0xc0: {
                    uint16_t dist = board->GetTOFDistance();
                    int data[4] = {0x04, 0xc0, ((dist | 0xff) >> 8), (dist & 0xff)};
                    SendData(data, sizeof(data) / sizeof(data[0]));
                }
                break;
                case 0xb0: {
                    int data[2] = {0x02, 0xb0};
                    SendData(data, sizeof(data) / sizeof(data[0]));
                    unsigned long t_begin = millis();
                    string info;
                    while (true) {
                        if ((millis() - t_begin < 10000)) {
                            info = GetWlanInfo();
                            int i = info.find(")");
                            if (i != string::npos) {
                                is_timeout = false;
                                is_first = false;
                                string bak_info = info;
                                int f_index = info.find("'");
                                int l_index = info.find_last_of("'");
                                i_ssid = "ssid: ";
                                i_password = "pssword: ";
                                ssid = info.substr(f_index + 1, l_index - f_index - 1);
                                i_ssid += ssid;
                                f_index = bak_info.find("(");
                                l_index = bak_info.find_last_of(")");
                                password = bak_info.substr(f_index + 1, l_index - f_index - 1);
                                i_password += password;
                                SendData(data, sizeof(data) / sizeof(data[0]));
                                break;
                            }
                        } else if (info == "" && (millis() - t_begin > 10000)) {
                            is_timeout = true;
                            break;
                        }
                    }
                }
                break;
                case 0xb1: {
                    int data[2] = {0x02, 0xb1};
                    SendData(data, sizeof(data) / sizeof(data[0]));
                    string str_data = "";

                    if (is_first)
                        str_data = "ssid: " + ssid + " " + "password: " + password;
                    else
                        str_data = i_ssid + " " + i_password;
                    if (transponder_mode == 0) {
                        Serial.write(str_data.c_str(), str_data.size());
                    } else if (transponder_mode == 1) {
                        serverClients[0].write(str_data.c_str(), str_data.size());
                    } else if (transponder_mode == 2) {
                        board->Write((uint8_t *)str_data.c_str(), str_data.size());
                    }
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
                    int data[4] = {0x04, 0xa1, pin_no, pin_state};
                    SendData(data, sizeof(data) / sizeof(data[0]));
                }
                break;
            }
            break;

        default: {
            //此处逻辑后面可能需要修改，兼顾server，server除2 3 4指令长度外没问题，暂时不改
            if (transponder_mode == 0) {
                while (Serial.available() > 0) {
                    board_serial.write(Serial.read());
                }
                while (board_serial.available() > 0) {
                    Serial.write(board_serial.read());
                }
            }
        }
        break;
    }
    return 0;
}

void Transponder::connect_ATOM(MyCobotBasic &myCobot)
{
    board->ClearScreen(Board_BLACK);//黑色填充屏幕
    delay(50);
    board->SetTextColor(Board_RED);
    board->SetTextSize(2);
    board->SetCursor(55, 20);
    board->Println("Connect test");
    board->DrawFastHLine(0, 70, 320, Board_GREY);

    board->SetCursor(10, 120);
    board->SetTextSize(2);
    board->SetTextColor(Board_WHITE);
    board->Print("Atom: ");
    board->SetTextColor(Board_GREEN);
    int state = myCobot.isPoweredOn();
    if (state == 1) {
        board->Println("ok");
    } else {
        board->Println("no");
    }
    board->SetCursor(230, 220);
    board->SetTextSize(2);
    board->SetTextColor(Board_WHITE);
    board->Println("Exit");
    board->BtnUpdate();
    //delay(1000);
    //info();
}

void Transponder::info()
{
    board->ClearScreen(Board_BLACK);//黑色填充屏幕
    board->SetTextColor(Board_BLACK);
    board->SetTextColor(Board_RED);
    board->SetTextSize(3);
    board->SetCursor(10, 10);
    board->Printf(TYPE);
    board->SetCursor(10, 40);
    //board->DrawFastHLine(0,70,320,Board_GREY);
    board->SetTextSize(2);
    board->Println("Basic Transponder");
    std::map<int, string> menuMap;
    board->HideBluetooth(menuMap);
    distep.MenuInit(menuMap);
    distep.MenuChoice();

    distep.Start();
    board->BtnUpdate();
    delay(10);
}

void Transponder::CreateWlanServer()
{
    WiFi.begin((char *)ssid.c_str(), (char *)password.c_str());
    for (int loops = 10; loops > 0; loops--) {
        if (WiFi.status() == WL_CONNECTED) {
            ip = WiFi.localIP();
            Serial.println(ip);
            bak_ssid = ssid;
            bak_password = password;
            transponder_mode = 1;
            wlan_uart = false;
            ConnectedInfo();
            break;
        } else {
            Serial.println(loops);
            delay(1000);
        }
    }
    if (WiFi.status() != WL_CONNECTED) {
        if (!wlan_uart) {
            ssid = bak_ssid;
            password = bak_password;
            ConnectFailedInfo(true);
            delay(500);
            CreateWlanServer();//重新连接上次成功的网络
        } else {
            transponder_mode = 0;
            wlan_uart = true;
            ConnectFailedInfo(false);
            //delay(1000);
        }
    }

    server.begin(server_port);
    server.setNoDelay(true);
    return;
}

void Transponder::WlanTransponder()
{
    uint8_t i;
    if (WiFi.status() == WL_CONNECTED) {
        //check if there are any new clients
        if (server.hasClient()) {
            for (i = 0; i < MAX_SRV_CLIENTS; i++) {
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

void WlanInfo()
{

}

void Transponder::ConnectingInfo()
{
    board->ClearScreen(Board_BLACK);//黑色填充屏幕
    board->FillRect(0, 0, 320, 30, Board_GREY);
    board->SetBitmapColor(Board_GREY, Board_GREY);
    board->SetTextColor(Board_WHITE);
    board->SetTextSize(2);
    board->SetCursor(10, 10);
    board->Println(ssid.c_str());
    board->SetTextColor(Board_WHITE);
    board->SetBitmapColor(Board_BLACK, Board_BLACK);
    board->SetCursor(10, 80);
    board->SetTextSize(2);
    board->Print("WIFI Connecting");
}

void Transponder::ConnectedInfo()
{
    board->ClearScreen(Board_BLACK);//黑色填充屏幕
    board->FillRect(0, 0, 320, 30, Board_GREY);
    board->SetBitmapColor(Board_GREY, Board_GREY);
    board->SetTextColor(Board_GREEN);
    board->SetTextSize(2);
    board->SetCursor(10, 10);
    board->Println(ssid.c_str());
    board->SetTextColor(Board_WHITE);
    board->SetCursor(10, 80);
    board->SetTextSize(2);
    board->Print("WIFI Connected");
    //board->FillRect(10, 108, 220, 60, Board_GREY);
    board->SetCursor(10, 110);
    board->SetTextSize(2);
    board->SetTextColor(Board_WHITE);
    board->Print("IP: ");
    board->SetTextColor(Board_RED);
    board->Println(ip);
    board->SetCursor(10, 140);
    board->SetTextSize(2);
    board->SetTextColor(Board_WHITE);
    board->Print("Port: ");
    board->SetTextColor(Board_RED);
    board->Println(server_port);
    board->SetCursor(200, 220);
    board->SetTextSize(2);
    board->SetTextColor(Board_WHITE);
    board->Println("ReConnect");
    board->DrawWLanExit();
}

void Transponder::ConnectFailedInfo(bool flag)
{
    board->ClearScreen(Board_BLACK);//黑色填充屏幕
    board->FillRect(0, 0, 320, 30, Board_GREY);
    board->SetBitmapColor(Board_GREY, Board_GREY);
    board->SetTextColor(Board_RED);
    board->SetTextSize(2);
    board->SetCursor(10, 10);
    board->Println(ssid.c_str());
    board->SetTextColor(Board_WHITE);
    board->SetCursor(10, 80);
    board->SetTextSize(2);
    board->Print("WIFI Connect Failed");
    board->SetTextColor(Board_WHITE);
    board->SetCursor(10, 110);
    board->SetTextSize(2);
    board->Print("ssid or password error");
    if (flag) {
        board->SetTextColor(Board_WHITE);
        board->SetCursor(10, 140);
        board->SetTextSize(2);
        board->Print("Connecting last wifi");
    }
    board->SetCursor(200, 220);
    board->SetTextSize(2);
    board->SetTextColor(Board_WHITE);
    board->Println("ReConnect");
    board->DrawWLanExit();
}

void Transponder::TimeOutInfo()
{
    board->ClearScreen(Board_BLACK);//黑色填充屏幕
    board->FillRect(0, 0, 320, 30, Board_GREY);
    board->SetBitmapColor(Board_GREY, Board_GREY);
    board->SetTextColor(Board_GREEN);
    board->SetTextSize(2);
    board->SetCursor(10, 10);
    board->Println(ssid.c_str());
    board->SetTextColor(Board_WHITE);
    board->SetCursor(10, 80);
    board->SetTextSize(2);
    board->Print("Input timeout(200ms)");
}

void Transponder::SetBaud()
{

}

string Transponder::GetWlanInfo()
{
    string str = "";
    while (Serial.available() > 0) {
        str += (char)Serial.read();
    }
    while (serverClients[0].available() > 0) {
        str += (char)serverClients[0].read();
    }
    while (board->Available() > 0) {
        str += (char)board->Read();
    }
    return str;
}

//bt
/*
void BTConfirmRequestCallback(uint32_t numVal)
{
  confirmRequestPending = true;
  Transponder::BTConnectingInfo(numVal);
}

void BTAuthCompleteCallback(boolean success)
{
  confirmRequestPending = false;
  if (success)
  {
   board_static->FillRect(10, 110, 260, 20, Board_BLACK);
   board_static->FillRect(10, 220, 60, 30, Board_BLACK);
    Serial.println("Pairing success!!");
  }
  else
  {
    Serial.println("Pairing failed, rejected by user!!");
  }
}

void Transponder::CreateBTServer()
{
  SerialBT.enableSSP();
  SerialBT.onConfirmRequest(&BTConfirmRequestCallback);
  SerialBT.onAuthComplete(&BTAuthCompleteCallback);
  SerialBT.begin(Bt_name); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  esp_efuse_mac_get_default(mac_addr);//获取mac地址
  // esp_bt_dev_get_address(void);
}
*/
void Transponder::BTWaitInfo()
{
    board->ClearScreen(Board_BLACK);//黑色填充屏幕
    board->FillRect(0, 0, 320, 30, Board_GREY);
    board->SetBitmapColor(Board_GREY, Board_GREY);
    board->SetTextColor(Board_WHITE);
    board->SetTextSize(2);
    board->SetCursor(10, 10);
    board->Println(Bt_name.c_str());
    board->SetTextColor(Board_WHITE);
    board->SetBitmapColor(Board_BLACK, Board_BLACK);
    board->SetCursor(10, 80);
    board->SetTextSize(2);
    board->Print("Bluetooth enabled");
    board->SetCursor(10, 130);
    board->SetTextSize(2);
    board->Print("BT Mac: ");
    board->SetCursor(100, 130);
    board->SetTextSize(2);
    board->DrawBtAddress();
    board->SetCursor(230, 220);
    board->SetTextSize(2);
    board->SetTextColor(Board_WHITE);
    board->Println("Exit");
}

void Transponder::BTConnectingInfo(uint32_t numVal)
{
    board->FillRect(10, 110, 260, 20, Board_BLACK);
    board->FillRect(10, 220, 60, 30, Board_BLACK);
    board->SetCursor(20, 220);
    board->SetTextSize(2);
    board->SetTextColor(Board_WHITE);
    board->Println("Pair");
    board->SetCursor(10, 110);
    board->SetTextSize(2);
    board->Print("Pairing code: ");
    board->SetCursor(200, 110);
    board->SetTextSize(2);
    board->Print(numVal);
}

void Transponder::BTConnectedInfo()
{
    board->ClearScreen(Board_BLACK);//黑色填充屏幕
    board->FillRect(0, 0, 320, 30, Board_GREY);
    board->SetBitmapColor(Board_GREY, Board_GREY);
    board->SetTextColor(Board_WHITE);
    board->SetTextSize(2);
    board->SetCursor(10, 10);
    board->Println(Bt_name.c_str());
    board->SetTextColor(Board_WHITE);
    board->SetCursor(10, 80);
    board->SetTextSize(2);
    board->Print("A client connected");
    board->SetCursor(10, 130);
    board->SetTextSize(2);
    board->Print("BT Mac: ");
    board->SetCursor(100, 130);
    board->SetTextSize(2);
    for (int i = 0; i < 6; i++) {
        board->Print(mac_addr[i], HEX);
        if (i != 5)
            board->Print(":");
    }
    board->SetCursor(230, 220);
    board->SetTextSize(2);
    board->SetTextColor(Board_WHITE);
    board->Println("Exit");
}
