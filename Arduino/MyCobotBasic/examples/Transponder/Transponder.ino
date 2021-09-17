#include <MyCobotBasic.h>
#include <ParameterList.h>

typedef  unsigned char u8;

MyCobotBasic myCobot;

byte IO_TIME_OUT = 25;
int IO_REC_WRONG = -1;
byte HEADER = 0xfe;
byte FOOTER = 0xfa;

void setup() {
  Serial.begin(115200);
  delay(100);

  myCobot.setup();
  delay(500);
  
  myCobot.powerOn();
  delay(500);


  pinMode(15, OUTPUT); // 1 
  pinMode(5, OUTPUT); // 2
  pinMode(2, OUTPUT); // 2
  
  info();
}
  
void loop() { 
  readData();
}



bool checkHeader()
{
  u8 bDat;
  u8 bBuf[2] = { 0.0 };
  u8 Cnt = 0;

  while (true)
  {
    if (!readSerial(&bDat, 1))
      return 0;
    bBuf[1] = bBuf[0];
    bBuf[0] = bDat;

    if (bBuf[0] == HEADER && bBuf[1] == HEADER)
      break;
    ++Cnt;
    if (Cnt > 10)
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
    if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 200)) {
        connect_ATOM();
    }
    if(Serial.available()>0)
    {
        rec_data = Serial.read();   // readSerial
        Serial2.write(rec_data);
        if (rec_data != IO_REC_WRONG)
        {
          if (nDat)
            nDat[Size] = rec_data;
          ++Size;
          t_begin = millis();
        }
        if (Size >= nLen)
          break;
        t_use = millis() - t_begin;
        if (t_use > IO_TIME_OUT)
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


int readData()
{
  rFlushSerial();
  if (!checkHeader())
    return -1;

  u8 data_len[1];
  u8 r_data_4[4];
  if (readSerial(data_len, 1) != 1)
    return -1;
    
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
            bool pin_data = r_data_4[2];

            digitalWrite(pin_no,pin_data);

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

void connect_ATOM(){
  M5.Lcd.clear(BLACK);
  delay(50);
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(55, 5);
  M5.Lcd.println("Connect test");
  M5.Lcd.setCursor(5, 40);
  int state = myCobot.isPoweredOn();
  if(state == 1){
    M5.Lcd.println("Atom: ok");
  }else{
    M5.Lcd.println("Atom: no");
  }
  delay(2000);
  info();
}

void info()
{
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(10, 20);
  M5.Lcd.printf("myCobot");
  M5.Lcd.setCursor(10, 70);
  M5.Lcd.printf("Basic Transponder");
  M5.Lcd.setCursor(40, 220);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.println("TEST");
}
