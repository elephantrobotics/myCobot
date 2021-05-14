/// 此文件用于mycobot设备控制末端夹爪运动，对应烧录设备为Basic
/// 烧录前请将夹爪张开至最大角度


#include <MycobotBasic.h>
#include <ParameterList.h>

MycobotBasic myCobot;   
 
void setup() {
  myCobot.setup();
  delay(10);
  myCobot.powerOn();
  delay(10);
  myCobot.setGripperIni();                          //设定夹爪当前位置电位值为2048
  delay(20);
  Serial.begin(9600);
}

void loop() {
    myCobot.setEncoder(7,2048);                     //设定末端夹爪打开至2048电位值
    delay(2000);
    Serial.println(myCobot.getGripperValue());      //读取末端夹爪电位值
    delay(50);
    myCobot.setEncoder(7,1700);                     //设定末端夹爪打开至1700电位值
    delay(2000);
    Serial.println(myCobot.getGripperValue());      //读取末端夹爪电位值
    delay(50);
}
