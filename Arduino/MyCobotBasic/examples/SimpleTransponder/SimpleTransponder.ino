#include <SCServo.h>
#include <MyCobotBasic.h>
#include <ParameterList.h>

typedef  unsigned char u8;

MyCobotBasic myCobot;
SMSBL sm;

byte IO_TIME_OUT = 25;
int IO_REC_WRONG = -1;
byte HEADER = 0xfe;
byte FOOTER = 0xfa;
int count = 0;
int PID[6][3] = {{10, 0, 1}, {10, 0, 1}, {10, 0, 1}, {32, 32, 0}, {10, 0, 1}, {10, 0, 1}};
int pid_hex[3] = {21, 22, 23};

void setup()
{
    Serial.begin(115200);
    Serial2.begin(BAUD_RATE);
    delay(100);
    sm.pSerial = &Serial2;
    myCobot.setup();
    delay(500);

    myCobot.powerOn();
    delay(500);   
    
    pinMode(15, OUTPUT); // 1
    pinMode(5, OUTPUT); // 2
    pinMode(2, OUTPUT); // 2

    while (!myCobot.isPoweredOn()) {
        delay(100);
    }
    info();
}

void loop()
{
    readData();
    delay(5);
}

bool checkHeader()
{
  u8 bDat;
  u8 bBuf[2] = { 0, 0 };
  u8 Cnt = 0;
  while (true)
  {
    if (!readSerial(&bDat, 1))
      return 0;
    bBuf[1] = bBuf[0];
    bBuf[0] = bDat;
    if (bBuf[0] == HEADER && bBuf[1] == HEADER){
      break;
    }
    ++Cnt;
    if (Cnt > 64)
      return 0;
  }
  return 1;
}

int readSerial(unsigned char* nDat, int nLen)
{
  int Size = 0;
  int rec_data;
  unsigned long t_begin = millis();
  unsigned long t_use;

  while (true)
  {
    M5.update();
    if (M5.BtnA.wasReleased()) {
        connect_ATOM();
    } else if(M5.BtnC.wasReleased()) {
        WaitInfo();
        Set();
        GripperInfo();
    }
    if(Serial.available()>0)
    {
      rec_data = Serial.read();   // readSerial
      Serial2.write(rec_data);

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
    }
    // read serial 2
    if (Serial2.available() > 0) {     // If anything comes in Serial 2
         Serial.write(Serial2.read());    // read it and send it out Serial (USB)
    } 
  }
  return Size;
}

void rFlushSerial()
{
  while (Serial.read() != -1)
    ;
}

void readData()
{
  rFlushSerial();
  if (! checkHeader())
    return;
  
  u8 data_len[1];
  u8 r_data_4[4];
  u8 r_data_3[3];
  if ( readSerial(data_len, 1) != 1)
    return;
  switch (static_cast<int>(data_len[0]))
  {
    case 4:
       readSerial(r_data_4, 4);
      switch (int(r_data_4[0]))
      {
        case 0xa0:
        { 
          //0xfe 0xfe 0x04 0xa0 pin_no pin_data 0xfa
          byte pin_no = r_data_4[1];
          pinMode(pin_no, OUTPUT);
          delay(5);
          bool pin_data = r_data_4[2];
          digitalWrite(pin_no,pin_data);
          Serial.write(0xfe);
          Serial.write(0xfe);
          Serial.write(0x04);
          Serial.write(0xa0);
          Serial.write(pin_no);
          Serial.write(pin_data);
          Serial.write(0xfa);
        }
        break;
      }
      break;
    case 3:
       readSerial(r_data_3, 3);
      switch (int(r_data_3[0]))
      {
        case 0xa1:
        {
          byte pin_no = r_data_3[1];
          pinMode(pin_no, INPUT);
          delay(5);
          bool pin_state = digitalRead(pin_no);
          delay(5);
          Serial.write(0xfe);
          Serial.write(0xfe);
          Serial.write(0x04);
          Serial.write(0xa1);
          Serial.write(pin_no);
          Serial.write(pin_state);
          Serial.write(0xfa);
        }
        break;
      }
      break;

    default:
      break;
  }
  
  while(Serial.available()>0) {Serial2.write(Serial.read()); }
  while(Serial2.available()>0) {Serial.write(Serial2.read());} 

}

void connect_ATOM()
{
    int m = 0;
    M5.Lcd.clear(BLACK);
    delay(50);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.println("Connect test");
    M5.Lcd.setCursor(10, 80);
    M5.Lcd.print("atom - ");
    for (int c = 1; c < 4; c++) {
        int state = myCobot.isPoweredOn();
        delay(20);
        if (state == 1) {
            m = m + 1;
        } else {
            m = m;
        }
    }
    for (int c = 1; c < 4; c++) {
        int state = myCobot.isPoweredOn();
        delay(20);
        if (state == 1) {
            m = m + 1;
        } else {
            m = m;
        }
    }
    if (m >= 2) {
        M5.Lcd.setTextColor(GREEN);
        M5.Lcd.println("ok");
    } else {
        M5.Lcd.setTextColor(RED);
        M5.Lcd.println("no");
        delay(50);
    }
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(WHITE);
    for (int i = 1; i < 7; i++) {
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.print("servo ");
        M5.Lcd.print(i);
        M5.Lcd.print(" - ");
        int servo_state = myCobot.isServoEnabled(i);
        if (servo_state == 1) {
            M5.Lcd.setTextColor(GREEN);
            M5.Lcd.println("ok");
        } else {
            M5.Lcd.setTextColor(RED);
            M5.Lcd.println("no");
        }
        delay(50);
    }
    delay(2000);
    info();
}

void info()
{
    M5.Lcd.clear(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(4);
    M5.Lcd.setCursor(10, 20);
    M5.Lcd.printf("myCobot");
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(10, 70);
    M5.Lcd.printf("Basic Transponder");
    M5.Lcd.setCursor(10, 120);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.print("Power: ");
    int state = myCobot.isPoweredOn();
    if (state == 1) {
        M5.Lcd.setTextColor(GREEN);
        M5.Lcd.println(" ON");
    } else {
        M5.Lcd.setTextColor(RED);
        M5.Lcd.println(" OFF");
    }
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(40, 215);
    M5.Lcd.setTextColor(BLUE);
    M5.Lcd.println("TEST");
    
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(220, 215);
    M5.Lcd.setTextColor(BLUE);
    M5.Lcd.println("Set");
}

void SetPDI()
{
    for (int i = 0; i + 1 < 7; i++) {
        for (int j = 0; j < 3; j++) {
            delay(100);
            while (myCobot.getServoData(i+1, pid_hex[j]) != PID[i][j]) {
                myCobot.setServoData(i+1, pid_hex[j], PID[i][j]);
                delay(100);
           }
        }
    }
}

// 参数设置 PDI 夹爪
void Set()
{
    SetPDI(); 
    SetGripperTorque();
}

//夹爪零位校准 最大力矩设为400
void SetGripperTorque()
{
    if (sm.Ping(7) == 7) {
        Serial.println("have");
        sm.CalibrationOfs(7);
        delay(10);
        while (sm.readWord(7, 16) != 400) {
            sm.unLockEprom(7);//打开EPROM保存功能
            delay(5);
            sm.writeWord(7, 16, 400); 
            delay(50);
            sm.LockEprom(7);//关闭EPROM保存功能
        }
    }
}

void GripperInfo()
{
    M5.Lcd.clear(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 20);
    M5.Lcd.print("Gripper Torque: ");
    M5.Lcd.setTextColor(RED);
    M5.Lcd.setTextSize(2);
    if (sm.Ping(7) == 7) {
        M5.Lcd.println(sm.readWord(7, 16));
    } else {
        M5.Lcd.println("can't found gripper");
    }
    delay(2000);
    info();
}

void WaitInfo()
{
    M5.Lcd.clear(BLACK);
    delay(50);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.println("parameter setting");
}
