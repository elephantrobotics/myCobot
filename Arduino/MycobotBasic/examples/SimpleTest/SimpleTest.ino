#include <MycobotBasic.h>
#include <ParameterList.h>

MycobotBasic myCobot;

//设定容器数量
Angles angles = { -0.0, -0.0, -0.0, -0.0, -0.0, -0.0 };           


void setup() {
  myCobot.setup();
  //打开扭矩输出
  myCobot.powerOn();
  //赋值容器内部元素
  for(auto &val : angles)       
    val = 0.0;
  //舵机回到原点
  myCobot.WriteAngles(angles, 50);
}

void loop() {
  for(int i = 1; i < 7; i++)        //run
    {
      myCobot.setLEDRGB(0XFF, 0, 0);       // set RGB show red
      delay(50);
      //myCobot.WriteAngle(i,angle,0-100);
      myCobot.WriteAngle(i, -90, 100);   // set joint angle -90 degree
      delay(4000);
      myCobot.setLEDRGB(0, 0XFF, 0);       // set RGB show blue
      delay(50);
      myCobot.WriteAngle(i, 90, 100);    // set joint angle 90 degree
      delay(4000);
      myCobot.setLEDRGB(0, 0, 0XFF);       // set RGB show green
      delay(50);
      myCobot.WriteAngle(i, 0, 100);     // set joint angle 0 degree
      delay(4000);
    }
}
