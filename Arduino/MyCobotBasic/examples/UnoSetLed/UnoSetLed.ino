#include <MyCobotBasic.h>

void setup()
{
    Serial.begin(1000000);

    MyCobotBasic myCobot(&Serial);
    delay(100);

    myCobot.powerOn();
    delay(100);

    //set led color
    myCobot.setLEDRGB(255,255,255);
    delay(600);
    myCobot.setLEDRGB(255,0,255);
    delay(600);
    myCobot.setLEDRGB(0,255,0);
    delay(600);
    
}

void loop()
{
  
}
