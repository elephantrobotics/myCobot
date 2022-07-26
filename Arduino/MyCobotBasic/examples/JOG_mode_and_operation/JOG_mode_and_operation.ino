#include <MyCobotBasic.h>
#include <ParameterList.h>

MyCobotBasic myCobot;

//定义一个Angles类型的变量angleEncoders，内容如下
Angles angleEncoders = { 2048, 2048, 2048, 2048, 2048, 2048 };

//定义一个Angles类型的变量servoSpeeds，内容如下
Angles servoSpeeds = { 1, 1, 1, 1, 1, 1 };

void setup() 
{
    Serial.begin(115200);
    
    //打开通讯串口
    myCobot.setup();

    //关节控制，使某个关节朝正/反方向运动直至Jogstop或是到达限位
    myCobot.jogAngle(1, 0, 20);
    
    delay(2000);
    
    //检测是否存在电机在运动
    Serial.print(myCobot.checkRunning());
    Serial.println(); 
   
    /*delay(5000);
    myCobot.jogCoord( Axis(2), 0, 50);*/
    
    delay(5000);

    //jog运动停止，等待6s后再进行其他控制
    myCobot.jogStop();
    
    delay(6000);

    myCobot.writeAngles({45, -10, -123, 45, 0, 20}, 50);
    
    delay(5000);

    //单关节电位值控制
    myCobot.setEncoder(1, 2048);
    
    delay(5000);

    //获取单关节电位值
    int encoder = myCobot.getEncoder(2);
    Serial.print(encoder);
    Serial.println(); 
    
    delay(5000);

    //多关节电位值控制
    myCobot.setEncoders( angleEncoders, 50);
    
    delay(5000);

    //获取所有关节电位值
    angleEncoders = myCobot.getEncoders();
    for(int i = 0; i < 6; i++)
    {
     Serial.print(angleEncoders[i]);
     Serial.print("  ");
    }
    Serial.println();
    
    delay(5000);

    //获取所有电机速度
    servoSpeeds = myCobot.getServoSpeeds();
    for(int i = 0; i < 6; i++)
    {
     Serial.print(servoSpeeds[i]);
     Serial.print("  ");
    }

    //参考输出
    /*
    M5Stack initializing...OK
    1
    2168
    2050.00  2054.00  2047.00  2047.00  2047.00  2044.00  
    0.00  0.00  0.00  0.00  0.00  0.00
    */
}

void loop() {
  // put your main code here, to run repeatedly:

}
