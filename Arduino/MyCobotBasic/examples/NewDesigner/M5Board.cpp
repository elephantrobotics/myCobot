#include "BoardBasic.h"
#ifdef BOARD_M5_BASIC
#include "M5Board.h"

bool confirmRequestPending{false};


void M5Board::Seeedbegin()
{

}

void M5Board::ClearScreen(uint32_t color)
{
    M5.Lcd.clear(color);
}

void M5Board::SetTextColor(uint32_t color)
{
    M5.Lcd.setTextColor(color);
}

void M5Board::SetTextSize(uint8_t size)
{
    M5.Lcd.setTextSize(size);
}

void M5Board::SetCursor(int16_t x, int16_t y)
{
    M5.Lcd.setCursor(x, y);
}

void M5Board::SetBitmapColor(uint16_t fgcolor, uint16_t bgcolor)
{
    M5.Lcd.setBitmapColor(fgcolor, bgcolor);
}

void M5Board::SetRotation(uint8_t r)
{

}

void M5Board::FixBtnClicked()
{
    adc_power_acquire();
}

void M5Board::FillRect(int32_t x, int32_t y, int32_t w, int32_t h,
                       uint32_t color)
{
    M5.Lcd.fillRect(x, y, w, h, color);
}

void M5Board::PushImage(int32_t x0, int32_t y0, int32_t w, int32_t h,
                        uint16_t *data)
{
    M5.Lcd.pushImage(x0, y0, w, h, data);
}

void M5Board::Print(const __FlashStringHelper *f)
{
    M5.Lcd.print(f);
}

void M5Board::Print(const String &s)
{
    M5.Lcd.print(s);
}

void M5Board::Print(const char *data)
{
    M5.Lcd.print(data);
}

void M5Board::Print(char c)
{
    M5.Lcd.print(c);
}

void M5Board::Print(int data, int base)
{
    M5.Lcd.print(data, base);
}

void M5Board::Print(unsigned int data, int base)
{
    M5.Lcd.print(data, base);
}

void M5Board::Print(long l, int base)
{
    M5.Lcd.print(l, base);
}

void M5Board::Print(unsigned long l, int base)
{
    M5.Lcd.print(l, base);
}

void M5Board::Print(double d, int base)
{
    M5.Lcd.print(d, base);
}

void M5Board::Print(const Printable &p)
{
    M5.Lcd.print(p);
}

void M5Board::Println(const __FlashStringHelper *f)
{
    M5.Lcd.println(f);
}

void M5Board::Println(const String &s)
{
    M5.Lcd.println(s);
}

void M5Board::Println(const char *data)
{
    M5.Lcd.println(data);
}

void M5Board::Println(char c)
{
    M5.Lcd.println(c);
}

void M5Board::Println(unsigned char c, int base)
{
    M5.Lcd.println(c, base);
}

void M5Board::Println(int data, int base)
{
    M5.Lcd.println(data, base);
}

void M5Board::Println(unsigned int data, int base)
{
    M5.Lcd.println(data, base);
}

void M5Board::Println(long l, int base)
{
    M5.Lcd.println(l, base);
}

void M5Board::Println(unsigned long l, int base)
{
    M5.Lcd.println(l, base);
}

void M5Board::Println(double d, int base)
{
    M5.Lcd.println(d, base);
}

void M5Board::Println(void)
{
    M5.Lcd.println();
}

void M5Board::Println(const Printable &p)
{
    M5.Lcd.println(p);
}

void M5Board::Printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    M5.Lcd.printf(fmt, args);
    va_end(args);
}

void M5Board::EepromBegin(size_t size)
{
    if (!EEPROM.begin(size)) {
        Serial.println("failed to initialise EEPROM");
        delay(1000000);
    }
}

uint8_t M5Board::EepromRead(int address)
{
    return EEPROM.read(address);
}

void M5Board::EepromWrite(int address, uint8_t val)
{
    EEPROM.write(address, val);
}

void M5Board::EepromCommit()
{
    EEPROM.commit();
}

void M5Board::DrawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color)
{
    M5.Lcd.drawFastHLine(x, y, w, color);
}

bool M5Board::IsBtnClicked(int btn)
{
    bool flag = false;
    switch (btn) {
        case 0: {
            flag = (M5.BtnA.wasReleased());
        }
        break;
        case 1: {
            flag = (M5.BtnB.wasReleased());
        }
        break;
        case 2: {
            flag = (M5.BtnC.wasReleased());
        }
        break;
    defalut:
        break;
    }
    return flag;
}

void M5Board::DrawString(const char *string, int32_t poX, int32_t poY)
{
    M5.Lcd.drawString(string, poX, poY);
}

void M5Board::DrawString(const char *string, int32_t poX, int32_t poY,
                         uint8_t font)
{
    M5.Lcd.drawString(string, poX, poY, font);
}

bool M5Board::InitFlash()
{
    return SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED);
}

void M5Board::BtnUpdate()
{
    M5.update();
}

void M5Board::DrawButtonLine()
{
    M5.Lcd.drawFastHLine(0, 195, 320, 0x5AEB);
    M5.Lcd.setCursor(30, 210);
    M5.Lcd.print(" DOWN ");
    M5.Lcd.setCursor(140, 210);
    M5.Lcd.print(" UP ");
    M5.Lcd.setCursor(235, 210);
    M5.Lcd.print(" OK ");
}

void M5Board::DrawWLanExit()
{
    M5.Lcd.setCursor(20, 220);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.println("Exit");
}

void M5Board::HideBluetooth(std::map<int, string> &menuMap)
{
    string str[4] = {"USB UART", "WLAN Server", "Bluetooth", "EXIT"};
    for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++) {
        menuMap.insert(std::make_pair(i, str[i]));
    }
}

void M5Board::DrawMainControlPlayStop()
{
    M5.Lcd.setCursor(40, 210);
    M5.Lcd.print("Stop");
}

bool M5Board::MainControlBtnStop()
{
    return M5.BtnA.wasReleased();//A键为stop
}

bool M5Board::UartBtnExit()
{
    return M5.BtnC.wasReleased();//C键为Exit
}

uint16_t M5Board::GetTOFDistance()
{
    TOF tof;
    Wire.begin();
    tof.write_byte_data_at(VL53L0X_REG_SYSRANGE_START, 0x01);
    byte val = 0;
    int cnt = 0;
    while (cnt < 100) { // 1 second waiting time max
        delay(10);
        val = tof.read_byte_data_at(VL53L0X_REG_RESULT_RANGE_STATUS);
        if (val & 0x01) break;
        cnt++;
    }
    tof.read_block_data_at(0x14, 12);
    return tof.makeuint16(tof.gbuf[11], tof.gbuf[10]);
}
//BT
void M5Board::DrawBtAddress()
{
    for (int i = 0; i < 6; i++) {
        if (mac_addr[i] < 10)
            M5.Lcd.print('0');
        M5.Lcd.print(mac_addr[i] & 0xff, HEX);
        if (i != 5)
            M5.Lcd.print(":");
    }
}

void BTConfirmRequestCallback(uint32_t numVal)
{
    confirmRequestPending = true;
    M5.Lcd.fillRect(10, 110, 260, 20, Board_BLACK);
    M5.Lcd.fillRect(10, 220, 60, 30, Board_BLACK);
    M5.Lcd.setCursor(20, 220);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(Board_WHITE);
    M5.Lcd.println("Pair");
    M5.Lcd.setCursor(10, 110);
    M5.Lcd.setTextSize(2);
    M5.Lcd.print("Pairing code: ");
    M5.Lcd.setCursor(200, 110);
    M5.Lcd.setTextSize(2);
    M5.Lcd.print(numVal);
}

void BTAuthCompleteCallback(bool success)
{
    confirmRequestPending = false;
    if (success) {
        M5.Lcd.fillRect(10, 110, 260, 20, Board_BLACK);
        M5.Lcd.fillRect(10, 220, 60, 30, Board_BLACK);
        Serial.println("Pairing success!!");
    } else {
        Serial.println("Pairing failed, rejected by user!!");
    }
}

void M5Board::CreateBTServer(String Bt_name)
{
    SerialBT.enableSSP();
    SerialBT.onConfirmRequest(BTConfirmRequestCallback);
    SerialBT.onAuthComplete(BTAuthCompleteCallback);
    SerialBT.begin(Bt_name); //Bluetooth device name
    Serial.println("The device started, now you can pair it with bluetooth!");
    esp_efuse_mac_get_default(mac_addr);//获取mac地址
}

bool M5Board::IsConfirmRequestPending() const
{
    return confirmRequestPending;
}

int M5Board::Read()
{
    return SerialBT.read();
}

void M5Board::Write(uint8_t c)
{
    SerialBT.write(c);
}

void M5Board::Write(const uint8_t *buffer, size_t size)
{
    SerialBT.write(buffer, size);
}

bool M5Board::Available()
{
    return SerialBT.available();
}

void M5Board::End()
{
    SerialBT.end();
}

bool M5Board::HasClient()
{
    return SerialBT.hasClient();
}

void M5Board::SetConnect()
{
    esp_bt_gap_set_scan_mode(ESP_BT_NON_CONNECTABLE, ESP_BT_NON_DISCOVERABLE);
}

void M5Board::SetNoConnect()
{
    esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);
}

void M5Board::ConfirmReply(bool confirm)
{
    SerialBT.confirmReply(confirm);
}

#endif
