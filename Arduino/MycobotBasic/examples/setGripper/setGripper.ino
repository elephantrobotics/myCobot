#include <MycobotBasic.h>
#include <ParameterList.h>

MycobotBasic myCobot;   
 
void setup() {
  myCobot.setup();
  myCobot.powerOn();
}

void loop() {
    myCobot.setGripper(1);       // set RGB show red
    delay(2000);
    myCobot.setGripper(0);       // set RGB show red
    delay(2000);

}
