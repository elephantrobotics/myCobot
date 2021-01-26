#include <MycobotBasic.h>
#include <ParameterList.h>

MycobotBasic myCobot;

String comdata = "TX:";//声明字符串变量

void setup() {
  // init lcd, serial, but don't init sd card
  M5.begin(true, false, true);
  M5.Power.begin();
  Serial.begin(115200);
  Serial2.begin(1000000);  
  info();
  
}

void loop() {
  M5.update();
  if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 200)) {
    connect_ATOM();
  } else {
  while (Serial.available() > 0) {      // If anything comes in Serial (USB)
      int sum = Serial.available();
      comdata += String(Serial.peek(),HEX);
      comdata += " ";
      Serial2.write(Serial.read());   // read it and send it out Serial2
      if (sum == 1)
    {
      M5.Lcd.fillRect(0, 60, 350, 100, BLACK);
      M5.Lcd.setCursor(5, 60);
      M5.Lcd.setTextColor(RED);
//      M5.Lcd.setTextWrap(true);
      M5.Lcd.println(comdata);
      comdata = "TX:";
    }
    } 
  while (Serial2.available() > 0) {     // If anything comes in Serial 
    Serial.write(Serial2.read());   // read it and send it out Serial (USB)
  }
  }
}


void connect_ATOM()
{
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
  M5.Lcd.setCursor(65, 5);
  M5.Lcd.println("Transponder");
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(5, 40);
  M5.Lcd.println("Serial Data Show");
  M5.Lcd.setCursor(40, 220);
  M5.Lcd.println("TEST");
}
