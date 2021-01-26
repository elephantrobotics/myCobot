#include <MycobotBasic.h>
#include <ParameterList.h>

MycobotBasic myCobot;

Encoders encoders;

void setup() {
  // 打开Atom链接
  myCobot.setup();
  myCobot.powerOn();
  Serial.begin(9600);
}
void loop() {
  Serial.println("check to pos1...");
  for(auto &val : encoders)
    val = 2048;
  myCobot.setEncoders(encoders, 50);
  delay(5000);
  
  Serial.println("check to pos2...");
  for(auto &val : encoders)
    val = 1048;
  myCobot.setEncoders(encoders, 50);
  delay(5000);
}
