///适用于控制末端的io输出pwm控制，烧录设备为basic

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
    myCobot.writeAngles(angles, 50);
    delay(5000);

    //设定末端23号引脚频率为1800Hz,占空比为50%(0-254)
    myCobot.setPWMOutput(23, 1800, 128);
    delay(100);
}

void loop()
{

    delay(4000);
    myCobot.setPWMOutput(23, 1800, 0); //设置占空比为0%(0-254)

    delay(4000);
    myCobot.setPWMOutput(23, 1800, 128); //设置占空比为50%(0-254)

}
