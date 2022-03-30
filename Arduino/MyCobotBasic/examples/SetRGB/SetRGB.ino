#include <MyCobotBasic.h>
#include <ParameterList.h>

MyCobotBasic myCobot;

void setup()
{
    myCobot.setup();
    myCobot.powerOn();
}

void loop()
{
    myCobot.setLEDRGB(0XFF, 0, 0);       // set RGB show red
    delay(2000);
    myCobot.setLEDRGB(0, 0XFF, 0);       // set RGB show blue
    delay(2000);
    myCobot.setLEDRGB(0, 0, 0XFF);       // set RGB show green
    delay(2000);
}
