#include "transponder.h"

// MyCobotBasic myCobot;

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
  tft.fillScreen(TFT_BLACK);//黑色填充屏幕
  tft.setRotation(3);
  
  distep.y_pos = pos_y;
  distep.rect_pos1 = rect1;
  distep.rect_pos2 = rect2;
  String menu[1] = {"Atom ConnectTest"};
  int num[1] = {0};
  distep.MenuInit(num, menu, 1);
  
  info();
  distep.MenuChoice();
}
  
void Transponder::run(MyCobotBasic &myCobot) {
  init();
  EXIT = false;
  while (!EXIT)
  {
    readData(myCobot);
  }
  
  
}

bool Transponder::checkHeader(MyCobotBasic &myCobot)
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

int Transponder::readSerial(MyCobotBasic &myCobot, unsigned char* nDat, int nLen)
{

  int Size = 0;
  int rec_data;
  unsigned long t_begin = millis();
  unsigned long t_use;

  while (true)
  {
    //m5.update();
    if (digitalRead(WIO_5S_DOWN) == LOW) {
        distep.state += 1;
        //connect_ATOM(myCobot);
        distep.MenuChoice();
    }
    if (digitalRead(WIO_5S_UP) == LOW) {
        distep.state -= 1;
        //connect_ATOM(myCobot);
        distep.MenuChoice();
    }
    if (digitalRead(WIO_5S_RIGHT) == LOW) {
        switch(distep.state) {
          case 0:
            connect_ATOM(myCobot);
          break;
          default:
            break;  
        }
    }
    
    if(digitalRead(WIO_5S_LEFT) == LOW) { EXIT = true; break;}

    if(Serial.available()>0)
    {
      rec_data = Serial.read();   // readSerial
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
    }
    // read serial 1
    if (Serial1.available() > 0) {     // If anything comes in Serial 1
         Serial.write(Serial1.read());    // read it and send it out Serial (USB)
    } 
  }
  return Size;
}

void Transponder::rFlushSerial()
{
  while (Serial.read() != -1)
    ;
}

int Transponder::readData(MyCobotBasic &myCobot)
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
  
  while(Serial.available()>0) {Serial1.write(Serial.read()); }
  while(Serial1.available()>0) {Serial.write(Serial1.read());} 

}

void Transponder::connect_ATOM(MyCobotBasic &myCobot){
  tft.fillScreen(TFT_BLACK);//黑色填充屏幕
  delay(50);
  tft.setTextColor(TFT_RED);
  tft.setTextSize(2);
  tft.setCursor(55, 20);
  tft.println("Connect test");
  tft.drawFastHLine(0,70,320,GREY);
  
  tft.setCursor(10, 120);
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);
  tft.print("Atom: ");  
  tft.setTextColor(TFT_GREEN);
  int state = myCobot.isPoweredOn();
  if(state == 1){
    tft.println("ok");
  }else{
    tft.println("no");
  }
  //m5.update();
  delay(1000);
  info();
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
  tft.drawFastHLine(0,70,320,GREY);
  tft.setTextSize(2);
  tft.println("Basic Transponder");

  distep.Start();
  //m5.update();
  delay(10);
}
