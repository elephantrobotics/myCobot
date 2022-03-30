#include <MyPalletizerBasic.h>
#include <ParameterList.h>
#include <SCServo.h>
MyPalletizerBasic myCobot;
SMSBL sm;
MyPalletizerEncoders encoders;
MyPalletizerAngles angles;
void setup()
{
    // 打开Atom链接
    angles.at(0) = 0;
    angles.at(1) = -0;
    angles.at(2) = 90;
    angles.at(3) = 0;
    myCobot.setup();
    myCobot.powerOn();
    sm.pSerial = &Serial2;
    //myCobot.writeangles(angles, 30);
    delay(2000);
    myCobot.setGripperState(0, 30);
    delay(2000);
    myCobot.setGripperState(1, 30);
    delay(2000);
    //myCobot.setGripperIni();
    //Serial.begin(9600);
}
void loop()
{


    // angles.at(0) = -50;
    // angles.at(1) = 50;
    // angles.at(2) = 120;
    // angles.at(3) = 0;
    // myCobot.writeAngles(angles,50);
    // delay(20);
    // for(int i = 0; i < 20; i++) {
    //   myCobot.checkRunning();
    //   delay(250);
    // }
    // angles.at(0) = 50;
    // angles.at(1) = 50;
    // angles.at(2) = 120;
    // angles.at(3) = 0;
    // myCobot.writeAngles(angles,50);
    // delay(20);
    // for(int i = 0; i < 20; i++) {
    //   myCobot.checkRunning();
    //   delay(250);
    // }
    // angles.at(0) = 50;
    // angles.at(1) = 50;
    // angles.at(2) = 50;
    // angles.at(3) = 0;
    // myCobot.writeAngles(angles,50);
    // delay(20);
    // for(int i = 0; i < 20; i++) {
    //   myCobot.checkRunning();
    //   delay(250);
    // }
}
