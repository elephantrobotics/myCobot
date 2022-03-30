#include <MyPalletizerBasic.h>
#include <ParameterList.h>
#include <SCServo.h>
MyPalletizerBasic myCobot;
SMSBL sm;
MyPalletizerEncoders encoders;
MyPalletizerCoords coords;
void init_dump()
{
    pinMode(2, OUTPUT); //设定引脚G2为输出状态
    pinMode(5, OUTPUT); //设定引脚G5为输出状态
    delay(100);
    digitalWrite(2, 1); //将引脚2设为高电平，关闭电磁阀
    digitalWrite(5, 1); //将引脚5设为高电平，关闭泵机
}
void setup()
{
    // 打开Atom链接
    coords.at(0) = 150;
    coords.at(1) = 0;
    coords.at(2) = 280;
    coords.at(3) = 30;
    myCobot.setup();
    myCobot.powerOn();
    init_dump();
    sm.pSerial = &Serial2;
    //myCobot.writeCoords(coords, 30);
    //delay(2000);
    M5.Lcd.clear(BLACK);
    M5.Lcd.setTextSize(4);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(20, 90);
    M5.Lcd.print("MyPalletizer");
    //myCobot.setGripperIni();
    //Serial.begin(9600);
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

void loop()
{
/////////////////////////////////////////////////
    coords.at(0) = -150;
    coords.at(1) = 170;
    coords.at(2) = 150;
    coords.at(3) = 40;
    myCobot.writeCoords(coords, 50);
    // delay(3000);
    // coords.at(0) = 140;
    // coords.at(1) = 130;
    // coords.at(2) = 120;
    // coords.at(3) = 0;
    // myCobot.writeCoords(coords,50);
    delay(3000);
    coords.at(0) = -150;
    coords.at(1) = -170;
    coords.at(2) = 150;
    coords.at(3) = 40;
    myCobot.writeCoords(coords, 50);
    delay(3000);
    //myCobot.setGripperState(1, 50);
    // coords.at(0) = 140;
    // coords.at(1) = 130;
    // coords.at(2) = 280;
    // coords.at(3) = 0;
    // myCobot.writeCoords(coords,50);
    //delay(3000);
    // coords.at(0) = 140;
    // coords.at(1) = -130;
    // coords.at(2) = 280;
    // coords.at(3) = 0;
    // myCobot.writeCoords(coords,50);
    // delay(3000);
    // coords.at(0) = 140;
    // coords.at(1) = -130;
    // coords.at(2) = 120;
    // coords.at(3) = 0;
    // myCobot.writeCoords(coords,50);
    // delay(50);

    // delay(3000);
    // myCobot.setGripperState(0, 50);
    //   coords.at(0) = 140;
    // coords.at(1) = 0;
    // coords.at(2) = 280;
    // coords.at(3) = 0;
    // myCobot.writeCoords(coords,50);
    // delay(3000);
    // coords.at(0) = 140;
    // coords.at(1) = -130;
    // coords.at(2) = 280;
    // coords.at(3) = 0;
    // myCobot.writeCoords(coords,50);
    // delay(50);

    // delay(3000);

///////////////////////////////////////////////////



////////////////////////////
}
