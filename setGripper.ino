#include <MycobotBasic.h>
#include <ParameterList.h>

MycobotBasic myCobot;   
 
void setup() {
  myCobot.setup();
  myCobot.powerOn();
//  myCobot.setGripperIni(); //init Gripper, must open Gripper
  delay(2000);
  Serial.begin(9600);
}

void loop() {
    myCobot.setGripperState(1, 100);       // set Gripper 
    delay(2000);
    myCobot.setGripperState(0, 100);       // set Gripper
    delay(2000);
}
