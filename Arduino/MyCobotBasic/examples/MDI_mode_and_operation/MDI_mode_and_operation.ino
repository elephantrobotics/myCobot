#include <MyCobotBasic.h>
#include <ParameterList.h>

MyCobotBasic myCobot;

//定义一个Angles类型的变量angles，内容如下
Angles angles = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

//定义一个Coords类型的变量coords，内容如下
Coords coords = { 194.700,-67.400,131.300,-177.260,-3.760,-110.880 };

void setup() 
{
    Serial.begin(115200);
    
    //打开通讯串口
    myCobot.setup();

    //获取所有关节角度
    angles = myCobot.getAngles();
    for(int i = 0; i < 6; i++)
    {
     Serial.print(angles[i]);
     Serial.print("  ");
    }
    Serial.println();

    delay(5000);

    //发送单独角度
    myCobot.writeAngle( 1, 45, 50); 
    myCobot.writeAngle( 2, 45, 50);
    myCobot.writeAngle( 3, 45, 50);
    myCobot.writeAngle( 4, 45, 50);
    myCobot.writeAngle( 5, 45, 50);
    myCobot.writeAngle( 6, 45, 50);
    
    delay(5000);

    //发送全部角度
    myCobot.writeAngles( angles, 50); 

    delay(5000);
    
    //读取所有坐标
    coords = myCobot.getCoords();
    for(int i = 0; i < 6; i++)
    {
     Serial.print(coords[i]);
     Serial.print("  ");
    }
    Serial.println();
    
    delay(5000);
    
    /*myCobot.writeAngles({0, -10, -123, 45, 0, 20}, 50);
    delay(5000);
    myCobot.writeAngles({0, 0, 0, 0, 0, 0}, 50);
    delay(5000);
    myCobot.writeCoords({194.700,-67.400,131.300,-177.260,-3.760,-110.880}, 30);
    delay(5000);*/

    //发送单独坐标
    myCobot.writeCoord( (Axis)4, 100, 50);

    delay(5000);

    //发送所有坐标
    myCobot.writeCoords( coords, 50);

    delay(5000);

    //发送三次坐标，按顺序移动
    Coords begin_coord = { 235.1, 17.5, 52.7, -157.74, -9.78, 121.94 };
    Coords middle_coord = { 228.9, 89.8, 42.9, -167.26, -7.17, 140.16 };
    Coords end_coord = { 239.9, 1.6, 206.0, 162.6, 20.39, 118.4 };
    myCobot.moveCCoords( begin_coord, middle_coord, end_coord);

    //参考输出
    /*
    M5Stack initializing...OK
    -0.08  -0.08  -0.08  -0.17  0.08  0.26  
    48.30  -62.60  412.20  -90.52  0.53  -89.03 
    */
}

void loop() {
  // put your main code here, to run repeatedly:

}
