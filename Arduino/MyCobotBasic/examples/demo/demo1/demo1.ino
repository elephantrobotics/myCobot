#include <MyPartnerBasic.h>
#include <ParameterList.h>
#include <SCServo.h>
MyPartnerBasic myCobot;
SMSBL sm;
MyPartnerEncoders encoders;
MyPartnerCoords coords;
void setup()
{
    // 打开Atom链接
    // coords.at(0) = 150;
    // coords.at(1) = 0;
    // coords.at(2) = 280;
    // coords.at(3) = 30;
    myCobot.setup();
    myCobot.powerOn();
    sm.pSerial = &Serial2;
    // myCobot.writeCoords(coords, 30);
    // delay(2000);
    myCobot.setGripperState(0, 30);
    //myCobot.setGripperIni();
    //Serial.begin(9600);
}
void loop()
{

    // coords.at(0) = 140;
    // coords.at(1) = 130;
    // coords.at(2) = 250;
    // coords.at(3) = 45;
    // myCobot.writeCoords(coords,50);
    // delay(2000);
    // coords.at(0) = 140;
    // coords.at(1) = 130;
    // coords.at(2) = 150;
    // coords.at(3) = 45;
    // myCobot.writeCoords(coords,30);
    // delay(50);
    // myCobot.setGripperState(1, 30);
    // delay(2000);
    // coords.at(0) = 140;
    // coords.at(1) = 130;
    // coords.at(2) = 250;
    // coords.at(3) = 45;
    // myCobot.writeCoords(coords,30);
    // delay(2000);
    // coords.at(0) = 140;
    // coords.at(1) = -130;
    // coords.at(2) = 250;
    // coords.at(3) = 45;
    // myCobot.writeCoords(coords,30);
    // delay(2000);
    // coords.at(0) = 140;
    // coords.at(1) = -130;
    // coords.at(2) = 150;
    // coords.at(3) = 45;
    // myCobot.writeCoords(coords,30);
    // delay(50);
    // myCobot.setGripperState(0, 30);
    // delay(2000);
    // coords.at(0) = 140;
    // coords.at(1) = -130;
    // coords.at(2) = 250;
    // coords.at(3) = 45;
    // myCobot.writeCoords(coords,30);
    // delay(2000);
    // coords.at(0) = 150;
    // coords.at(1) = 0;
    // coords.at(2) = 280;
    // coords.at(3) = 30;
    // myCobot.writeCoords(coords,30);
    // delay(5000);
// MyPartnerAngles angles;
// angles.at(0) = -150;
// angles.at(1) = 0;
// angles.at(2) = 0;
// angles.at(3) = 0;

// myCobot.writeAngles(angles,30);

    sm.WritePosEx(1, 200, 1000, 20);
    sm.WritePosEx(2, 1024, 1000, 20);
    sm.WritePosEx(3, 3096, 1000, 20);
    sm.WritePosEx(4, 2048, 1000, 20);

    delay(5000);

// angles.at(0) = 150;
// angles.at(1) = 0;
// angles.at(2) = 0;
// angles.at(3) = 0;
// sm.WritePosEx(1, 3800, 1000, 20);
// sm.WritePosEx(2, 1024, 1000, 20);
// sm.WritePosEx(3, 3096, 1000, 20);
// sm.WritePosEx(4, 2048, 1000, 20);

// // myCobot.writeAngles(angles,30);
// delay(5000);
}
