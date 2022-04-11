#include <MyCobotBasic.h>

MyCobotBasic myCobot;

void setup()
{
#if (!defined MyCobot_Uno)
    Serial.begin(115200);
#endif

    myCobot.setup();
    delay(100);
    myCobot.powerOn();//机械臂上电
    delay(100);
    
#if defined MyCobot_Uno || defined MyCobot_Mega
    pinMode(LED_BUILTIN, OUTPUT);//LED io设为输出
#endif

    delay(100);
}

void loop()
{
    delay(1000);
    SetLedBlink();
    delay(100);
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
    Angles angles = myCobot.getAngles();
    delay(100);
#if (!defined MyCobot_Uno)
    Serial.print("angles = ");
    for (int i = 0; i < 6; i++) {
        Serial.print(angles[i]);
        Serial.print(" ");
    }
    Serial.println();
#endif
    myCobot.writeAngles({0, 0, 0, 0, 0, 0}, 30);
    delay(5000);
}

/*
 * 单/多关节控制
 */
void ControlAngle()
{
    //单关节控制 每个关节移动到30 速度为30
    for (int i = 1; i < 7; i++) {
        myCobot.writeAngle((Joint)i, 30, 30);
        delay(3000);
    }

    //多关节控制
    myCobot.writeAngles({0, 0, 0, 0, 0, 0}, 50);
    delay(6000);
}

/*
 * 获取当前坐标，移动坐标到零点
 */
void MoveCoordToZero()
{
    Coords coords = myCobot.getCoords();
    delay(3000);
#if (!defined MyCobot_Uno)
    Serial.print("coords = ");
    for (int i = 0; i < 6; i++) {
        Serial.print(coords[i]);
        Serial.print(" ");
    }
    Serial.println();
#endif
    myCobot.writeAngles({0, -10, -123, 45, 0, 20}, 50);//關節動到此姿態，再進行坐標控制
    delay(6000);
}

/*
 * 单/多坐标控制
 */
void ControlCoord() 
{
    //单关节控制 x轴移动到30 速度为30
     myCobot.writeCoord((Axis)1, 30, 30);
     delay(3000);
    //多坐标控制
    myCobot.writeCoords({194.700,-67.400,131.300,-177.260,-3.760,-110.880}, 30);
    delay(6000);
}

/*
 * 夹爪控制：获取夹爪角度
 */
void ControlGripper()
{
    int state = myCobot.getGripperValue();
#if (!defined MyCobot_Uno)
    Serial.print("gripper value == ");
    Serial.println(state);
#endif
    delay(500);
    myCobot.setGripperValue(100, 50);
    delay(800);
    myCobot.setGripperValue(0, 50);
    delay(800);
}

/*
 * 控制LED灯闪烁
 */
void SetLedBlink()
{
#if defined Uno || defined Mega
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);                       // wait for a second
#endif
}
