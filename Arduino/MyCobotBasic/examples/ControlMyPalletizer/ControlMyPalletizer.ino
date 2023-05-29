#include <MyPalletizerBasic.h>

MyPalletizerBasic myPal;

/* 角度控制范围：J1~J4：+-160,0~90,0~60,无限
* 坐标控制范围：xy范围+-260 z范围0~227
* */
void setup()
{
    myPal.setup();
    delay(100);
    myPal.powerOn();//机械臂上电
    delay(100);
}

void loop()
{
    delay(1000);
    MoveAngleToZero();
    delay(500);
    ControlAngle();
    delay(500);
    MoveCoordToZero();
    delay(500);
    ControlCoord();
    delay(500);
    ControlGripper();
    delay(1000); 
}
/*
 * 获取关节角度，移动机械臂到零点
 */
void MoveAngleToZero()
{
    MyPalletizerAngles angles = myPal.getAngles();
    delay(100);
    Serial.print("angles = ");
    for (int i = 0; i < MyPalletizerJointsNum; i++) {
        Serial.print(angles[i]);
        Serial.print(" ");
    }
    Serial.println();
    myPal.writeAngles({0, 0, 0, 0}, 30);
    delay(5000);
}

/*
 * 单/多关节控制
 */
void ControlAngle()
{
    //单关节控制 每个关节移动到30 速度为30
    for (int i = 1; i < MyPalletizerJointsNum+1; i++) {
        myPal.writeAngle((MyPalletizerJoint)i, 30, 30); 
        delay(3000);
    }

    //多关节控制
    myPal.writeAngles({0, 0, 0, 0}, 50);
    delay(6000);
}

/*
 * 获取当前坐标，移动坐标到零点
 */
void MoveCoordToZero()
{
    MyPalletizerCoords coords = myPal.getCoords();
    delay(3000);
    Serial.print("coords = ");
    for (int i = 0; i < MyPalletizerJointsNum; i++) {
        Serial.print(coords[i]);
        Serial.print(" ");
    }
    Serial.println();
    myPal.writeAngles({0, -10, 20, 45}, 50);//關節動到此姿態，再進行坐標控制
    delay(6000);
}

/*
 * 单/多坐标控制
 */
void ControlCoord() 
{
    //单关节控制 x轴移动到30 速度为30
     myPal.writeCoord((MyPalletizerAxis)1, 30, 30);
     delay(3000);
    //多坐标控制
    myPal.writeCoords({194.700,-67.400,131.300,-177.260}, 30); 
    delay(6000);
}

/*
 * 夹爪控制：获取夹爪角度
 */
void ControlGripper()
{
    int state = myPal.getGripperValue();
    Serial.printf("gripper value %d\n", state);
    delay(500);
    myPal.setGripperValue(100, 50);
    delay(800);
    myPal.setGripperValue(0, 50);
    delay(800);
}