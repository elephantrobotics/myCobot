#include <MyPalletizerBasic.h>
#include <ParameterList.h>
#include <SCServo.h>
MyPalletizerBasic myCobot;
SMSBL sm;
MyPalletizerEncoders encoders;
MyPalletizerCoords begin_coords;
MyPalletizerCoords end_coords;
MyPalletizerAngles angles;

void init_dump()
{
    pinMode(2, OUTPUT); //设定引脚G2为输出状态
    pinMode(5, OUTPUT); //设定引脚G5为输出状态
    delay(50);
    digitalWrite(2, 1); //将引脚2设为高电平，关闭电磁阀
    digitalWrite(5, 1); //将引脚5设为高电平，关闭泵机
}


void open_dump()
{
    digitalWrite(5, 0); //将引脚5设为低电平，打开泵机
    delay(200);//延时200ms
    digitalWrite(2, 0); //将引脚2设为低电平，打开电磁阀
    delay(200);
}
void close_dump()
{
    digitalWrite(2, 1); //将引脚2设为高电平，关闭电磁阀
    delay(200);//延时200ms
    digitalWrite(5, 1); //将引脚5设为高电平，关闭泵机
    delay(200);//延时200ms
}
//延时2000ms,松开吸住的物体

void setup()
{
    // 打开Atom链接
    myCobot.setup();
    myCobot.powerOn();
    init_dump();
    sm.pSerial = &Serial2;

    delay(500);
    //myCobot.setGripperIni();
    //Serial.begin(9600);
}
void loop()
{
    begin_coords.at(0) = 200;
    begin_coords.at(1) = 50;
    begin_coords.at(2) = 150;
    begin_coords.at(3) = 30;
    myCobot.moveLCoords(begin_coords, 30);
    delay(5000);
    end_coords.at(0) = 200;
    end_coords.at(1) = -50;
    end_coords.at(2) = 150;
    end_coords.at(3) = 30;
    myCobot.moveLCoords(end_coords, 50);
    delay(5000);
    begin_coords.at(0) = 200;
    begin_coords.at(1) = 0;
    begin_coords.at(2) = 150;
    begin_coords.at(3) = 30;
    myCobot.moveLCoords(begin_coords, 50);
    delay(5000);
    end_coords.at(0) = 240;
    end_coords.at(1) = 0;
    end_coords.at(2) = 150;
    end_coords.at(3) = 30;
    myCobot.moveLCoords(end_coords, 50);
    delay(5000);
    end_coords.at(0) = 150;
    end_coords.at(1) = 0;
    end_coords.at(2) = 150;
    end_coords.at(3) = 30;
    myCobot.moveLCoords(end_coords, 50);
    delay(5000);
    end_coords.at(0) = 200;
    end_coords.at(1) = 0;
    end_coords.at(2) = 150;
    end_coords.at(3) = 30;
    myCobot.moveLCoords(end_coords, 50);
    delay(5000);
    end_coords.at(0) = 200;
    end_coords.at(1) = 0;
    end_coords.at(2) = 200;
    end_coords.at(3) = 30;
    myCobot.moveLCoords(end_coords, 50);
    delay(5000);
    end_coords.at(0) = 200;
    end_coords.at(1) = 0;
    end_coords.at(2) = 50;
    end_coords.at(3) = 30;
    myCobot.moveLCoords(end_coords, 50);
    delay(5000);
    end_coords.at(0) = 150;
    end_coords.at(1) = 0;
    end_coords.at(2) = 150;
    end_coords.at(3) = 30;
    myCobot.moveLCoords(end_coords, 50);
    delay(5000);
    end_coords.at(0) = 200;
    end_coords.at(1) = 0;
    end_coords.at(2) = 150;
    end_coords.at(3) = 30;
    myCobot.moveCCoords(end_coords, 0, 50);
    delay(20000);
}
