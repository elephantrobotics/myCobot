#include <MyCobotBasic.h>
#include <ParameterList.h>

MyCobotBasic myCobot;

//定义一个Angles类型的变量angles，内容如下
Angles angles = { -0.0, -0.0, -0.0, -0.0, -0.0, -0.0 };


void setup()
{

    //打开通讯串口
    myCobot.setup();

    //链接atom
    myCobot.powerOn();

    //赋值angles为{ 0, 0, 0, 0, 0, 0 };
    for (auto &val : angles)
        val = 0.0;

    //关节回到原点
    /*myCobot.writeAngles(angles, 50);*/
    delay(5000);
    angles = myCobot.getPid();
    for (int i = 0; i < 6; i++) {
        Serial.print(angles[i]);
        Serial.print("  ");
    }
    Serial.println();
    delay(100);
    myCobot.setPid({10, 10, 10, 10, 10, 10});
    delay(100);
    angles = myCobot.getPid();
    for (int i = 0; i < 6; i++) {
        Serial.print(angles[i]);
        Serial.print("  ");
    }
    Serial.println();
    delay(100);
    angles = myCobot.getServoStatus();
    for (int i = 0; i < 6; i++) {
        Serial.print(angles[i]);
        Serial.print("  ");
    }
    Serial.println();
    delay(100);
    angles = myCobot.getServoTemps();
    for (int i = 0; i < 6; i++) {
        Serial.print(angles[i]);
        Serial.print("  ");
    }
    Serial.println();
    delay(100);
    angles = myCobot.getServoVoltages();
    for (int i = 0; i < 6; i++) {
        Serial.print(angles[i]);
        Serial.print("  ");
    }
    Serial.println();
    delay(100);
    angles = myCobot.getAngles();
    for (int i = 0; i < 6; i++) {
        Serial.print(angles[i]);
        Serial.print("  ");
    }
    Serial.println();
}

void loop()
{
    /*for (int i = 1; i < 7; i++) {     //依次设定关节正反转90°
        //myCobot.writeAngle(i,angle,0-100);
        myCobot.writeAngle(i, -90, 100);   // set joint angle -90 degree
        delay(4000);
        myCobot.writeAngle(i, 90, 100);    // set joint angle 90 degree
        delay(4000);
        myCobot.writeAngle(i, 0, 100);     // set joint angle 0 degree
        delay(4000);
    }*/
}