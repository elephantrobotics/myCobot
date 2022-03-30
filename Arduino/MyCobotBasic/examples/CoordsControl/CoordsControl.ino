#include <MyCobotBasic.h>
#include <ParameterList.h>
MyCobotBasic myCobot;

bool Servo_state = 1;
int power_pin = 2;
int open_pin = 5;
int out_state = 1;

Coords pos_init_1 = {155.10, -55.10, 90.10, 179.10, 0.10, -90.10};   // 初始坐标
Coords pos_init_2 = {255.10, -55.10, 90.10, 179.10, 0.10, -90.10};   // 初始坐标
Coords pos_init_3 = {255.10,  55.10, 90.10, 179.10, 0.10, -90.10};   // 初始坐标
Coords pos_init_4 = {155.10,  55.10, 90.10, 179.10, 0.10, -90.10};   // 初始坐标
Coords pos_init_5 = {155.10, -55.10, 90.10, 179.10, 0.10, -90.10};   // 初始坐标
Coords pos_init_6 = {155.10, -55.10, 150.10, 179.10, 0.10, -90.10};   // 初始坐标
Coords pos_init_7 = {155.10,  55.10, 150.10, 179.10, 0.10, -90.10};   // 初始坐标
Coords pos_init_8 = {255.10,  55.10, 150.10, 179.10, 0.10, -90.10};   // 初始坐标
Coords pos_init_9 = {255.10, -55.10, 150.10, 179.10, 0.10, -90.10};   // 初始坐标
Coords pos_init_10 = {155.10, -55.10, 150.10, 179.10, 0.10, -90.10};   // 初始坐标
Coords data1;
Angles angles_0 = {0, 0, 0, 0, 0, 0};             //初始化角度

void move_coords(int dir = 0,
                 int num = 0);   // 声明可调用函数，无实际意义。

void setup()                //初始化函数
{
    myCobot.setup();
    myCobot.powerOn();

    pinMode(power_pin, OUTPUT);
    pinMode(open_pin, OUTPUT);

    set_pump(1);

    myCobot.setLEDRGB(0, 0, 255);
    delay(100);
    myCobot.writeAngles(angles_0, 30);
    delay(3000);
    Serial.printf("A键控制力矩开关         |");
    Serial.println("");
    Serial.printf("B键控制立方体移动       |");
    Serial.println("");
    Serial.printf("C键控制前后左右上下移动  |");
    Serial.println("");
}

void loop()                 //主函数
{
    // put your main code here, to run repeatedly:
    M5.update(); // need to call update()
    M5.Lcd.setCursor(0, 0);
    int j = 0;
    if (M5.BtnA.wasReleased()) {       //控制上下电
        reless();
    }
    if (M5.BtnB.wasReleased()) {        //移动到初始角度
        myCobot.writeCoords(pos_init_1, 50);
        delay(3000);
        myCobot.writeCoords(pos_init_2, 30);
        delay(2000);
        myCobot.writeCoords(pos_init_3, 30);
        delay(2000);
        myCobot.writeCoords(pos_init_4, 30);
        delay(2000);
        myCobot.writeCoords(pos_init_5, 30);
        delay(2000);
        myCobot.writeCoords(pos_init_6, 30);
        delay(2000);
        myCobot.writeCoords(pos_init_7, 30);
        delay(2000);
        myCobot.writeCoords(pos_init_8, 30);
        delay(2000);
        myCobot.writeCoords(pos_init_9, 30);
        delay(2000);
        myCobot.writeCoords(pos_init_10, 30);
        delay(2000);
    }
    if (M5.BtnC.wasReleased()) {        //前后左右上下移动
        myCobot.writeCoords(pos_init_1, 30);
        delay(3000);
        data1 = pos_init_1;
        delay(50);
        move_coords(0, 10);
        delay(2000);
        move_coords(0, -10);
        delay(2000);
        move_coords(1, 10);
        delay(2000);
        move_coords(1, -10);
        delay(2000);
        move_coords(2, 10);
        delay(2000);
        move_coords(2, -10);
        delay(2000);
        move_coords(3, -10);
        delay(2000);
        move_coords(3, 10);
        delay(2000);
        move_coords(4, -10);
        delay(2000);
        move_coords(4, 10);
        delay(2000);
        move_coords(5, -10);
        delay(2000);
        move_coords(5, 10);
        delay(2000);
    }
}

void reless()               //控制力矩开关
{
    for (int i = 1; i < 7; i++) {
        myCobot.setServoData(i, 40, !Servo_state);
        delay(30);
    }
    Servo_state = !Servo_state;
}

Angles read_Angles()        // 读取角度并输出
{
    Angles data2;
    data2 = myCobot.getAngles();
    delay(50);
    for (int i = 0; i < 6; i++) {
        Serial.print(data2[i]);
        Serial.print(", ");
    }
    Serial.println();
    return data2;
}

Coords read_pos()           //读取坐标并输出
{
    Coords data1;
    data1 = myCobot.getCoords();
    delay(50);
    for (int i = 0; i < 6; i++) {
        Serial.print(data1[i]);
        Serial.print(", ");
    }
    Serial.println();
    return data1;
}

void move_coords(int dir,
                 int num)    //控制移动方向和步数，一步等于10mm
{
    if (num > 0) {
        for (int i = 0; i < num; i++) {
            myCobot.writeCoords(data1, 30);
            for (int i = 0; i < 6; i++) {
                Serial.print(data1[i]);
                Serial.print(", ");
            }
            Serial.println("");
            data1[dir] += 10;
            delay(100);
        }
    } else {
        num = 0 - num;
        for (int i = 0; i < num; i++) {
            myCobot.writeCoords(data1, 30);
            for (int i = 0; i < 6; i++) {
                Serial.print(data1[i]);
                Serial.print(", ");
            }
            Serial.println("");
            data1[dir] -= 10;
            delay(100);
        }
    }
}

void set_pump(int out_state)          //吸泵开关
{
    digitalWrite(power_pin, out_state);
    digitalWrite(open_pin, out_state);
}
