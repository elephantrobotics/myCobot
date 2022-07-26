#include <MyCobotBasic.h>
#include <ParameterList.h>

MyCobotBasic myCobot;

void setup()
{
    Serial.begin(115200);
    
    delay(5000);
    
    //打开通讯串口
    myCobot.setup();
    
    //连接atom
    myCobot.powerOn();
    //myCobot.powerOff();//机械臂掉电

    delay(5000);
    
    //ATOM状态查询，检测是否上电
    bool is_poweron = myCobot.isPoweredOn();
    Serial.print(is_poweron);
    Serial.println();
    
    //检查Atom版本
    int atomversion = myCobot.getAtomVersion();
    Serial.print(atomversion);
    Serial.println();

    //参考输出
    /*
    M5Stack initializing...OK
    1
    42
    */
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
