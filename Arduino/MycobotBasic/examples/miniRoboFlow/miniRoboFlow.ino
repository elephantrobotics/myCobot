#include <MycobotBasic.h>
#include "transponder.h"
#include "MainControl.h"
#include "Calibration.h"
#include "Information.h"
#include "config.h"

MycobotBasic myCobot;
Transponder tp;
MainControl mc;
Calibration cb;
Connect ct;

int state = 0;
// bool EXIT = false;
int y_pos[] = {70, 95, 120, 145};


void setup(){
  myCobot.setup();                                      
  myCobot.powerOn();                                    //启动机械臂
  delay(50);
  EEPROM.begin(EEPROM_SIZE);                            //EEPROM_SIZE=64
  
  if (EEPROM.read(state_addr))
  {
    state = EEPROM.read(state_addr) - 1;                //写数据
    program_selection(myCobot, state);
  }else{
    EEPROM.write(state_addr, 0); //写数据
  }
  EEPROM.commit();                                      //保存更改的数据
  M5.Lcd.clear(BLACK);
  menu_choice();
  select();
}

void loop(){
  M5.update(); 
  if (M5.BtnA.wasPressed()) {
    state += 1;
    select();
    } 
  if (M5.BtnB.wasPressed()) {  
    state -= 1;
    select();
  }
  if (M5.BtnC.wasPressed()) {  
    EEPROM.begin(EEPROM_SIZE); //申请操作到地址4095,size=目标地址+1
    EEPROM.write(state_addr, state + 1); //写数据
    EEPROM.commit(); //保存更改的数据
    program_selection(myCobot, state);
    M5.Lcd.clear(BLACK);
    menu_choice();
    select();
  } 
}

void program_selection(MycobotBasic &myCobot, int state){
  switch (state)
  {
  case 0:
    mc.Control(myCobot);
    break;
  case 1:
    cb.bration(myCobot);
    break;
  case 2:
    tp.ponder(myCobot);
    break;
  case 3:
    ct.test(myCobot);
    break;
  default:
    break;
  }
  menu_choice();
}

void menu_choice(){
  
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.setCursor(20,10);
  M5.Lcd.print("miniRoboFlow"); 

  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(250,30);
  M5.Lcd.setTextColor(GREY); 
  M5.Lcd.print("v1.0");   

  M5.Lcd.drawFastHLine(0,45,320,GREY);
  M5.Lcd.drawFastHLine(0,195,320,GREY);

  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(30,y_pos[0]);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.print("MainControl"); 
  M5.Lcd.setCursor(30,y_pos[1]);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.print("Calibration"); 
  M5.Lcd.setCursor(30,y_pos[2]);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.print("Transponder"); 
  M5.Lcd.setCursor(30,y_pos[3]);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.print("Information"); 

  M5.Lcd.setCursor(35, 210);
  M5.Lcd.print("DOWN");
  M5.Lcd.setCursor(140, 210);
  M5.Lcd.print(" UP ");
  M5.Lcd.setCursor(235, 210);
  M5.Lcd.print(" OK ");

}

void select(){
  if (state < 0)
    {
      state = App_number;
  }if (state > App_number)
  {
    state = 0;
  }
  M5.Lcd.fillRect(0, 70, 26, 90, BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0,y_pos[state]);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.print(" >");
}
