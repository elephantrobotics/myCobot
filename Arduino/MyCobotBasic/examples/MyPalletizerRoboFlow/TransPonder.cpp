#include "transponder.h"

// MyPalletizerBasic myCobot;

// #define 
typedef  unsigned char u8;

void Transponder::init() {
  // myCobot.setup();
  // myCobot.powerOn();
  pinMode(15, OUTPUT); // 1 
  pinMode(5, OUTPUT); // 2
  pinMode(35, INPUT); // 2
  pinMode(36, INPUT); // 2
  delay(100);
  digitalWrite(15, 1); // 1 
  digitalWrite(5, 1); // 2
  info();
}
  
void Transponder::run(MyPalletizerBasic &myCobot) {
  init();
  EXIT = false;
  while (!EXIT)
  {
    readData(myCobot);
  }
  
  
}

bool Transponder::checkHeader(MyPalletizerBasic &myCobot)
{
  u8 bDat;
  u8 bBuf[2] = { 0, 0 };
  u8 Cnt = 0;
  while (true)
  {
    if (!readSerial(myCobot, &bDat, 1))
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

int Transponder::readSerial(MyPalletizerBasic &myCobot, unsigned char* nDat, int nLen)
{

  int Size = 0;
  int rec_data;
  unsigned long t_begin = millis();
  unsigned long t_use;

  while (true)
  {
    M5.update();
    if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 200)) {
        connect_ATOM(myCobot);
    }
    if(M5.BtnC.wasReleased()) { EXIT = true; break;}

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

void Transponder::rFlushSerial()
{
  while (Serial.read() != -1)
    ;
}

int Transponder::readData(MyPalletizerBasic &myCobot)
{
  rFlushSerial();
  if (!Transponder::checkHeader(myCobot))
    return -1;
  
  u8 data_len[1];
  u8 r_data_4[4];
  u8 r_data_3[3];
  if (Transponder::readSerial(myCobot, data_len, 1) != 1)
    return -1;
  switch (static_cast<int>(data_len[0]))
  {
    case 4:
      Transponder::readSerial(myCobot, r_data_4, 4);
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
      Transponder::readSerial(myCobot, r_data_3, 3);
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

void Transponder::connect_ATOM(MyPalletizerBasic &myCobot){
  M5.Lcd.clear(BLACK);
  delay(50);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(55, 20);
  M5.Lcd.println("Connect test");
  M5.Lcd.drawFastHLine(0,70,320,GREY);
  M5.Lcd.setCursor(5, 120);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.print("Atom: ");  
  M5.Lcd.setTextColor(GREEN);
  int state = myCobot.isPoweredOn();
  if(state == 1){
    M5.Lcd.println("ok");
  }else{
    M5.Lcd.println("no");
  }
  M5.update();
  delay(1000);
  info();
}

void Transponder::info()
{
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.printf("myCobot");
  M5.Lcd.setCursor(0, 40);
  M5.Lcd.drawFastHLine(0,70,320,GREY);
  M5.Lcd.setTextSize(3);
  M5.Lcd.println("Basic Transponder");
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(0, 100);
  M5.Lcd.println("Press A - Atom ConnectTest");
  M5.Lcd.println();
  M5.Lcd.println("Press C - Exit");
  M5.Lcd.setCursor(40, 210);
  M5.update();
  delay(10);
}
