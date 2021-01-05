#include <MycobotBasic.h>
#include <ParameterList.h>

MycobotBasic myCobot;

void setup() {
  // 打开Atom链接
  myCobot.setup();
  myCobot.powerOn();
  Serial.begin(9600);
}
void loop() {
  Serial.println("check setEncoder()...");
  myCobot.SetEncoder(Joint::J1, 2048);
  delay(5000);

  Serial.println("check getEncoder()...");
  Serial.print("current J1 encoder is: ");
  Serial.println(myCobot.GetEncoder(Joint::J1));
  delay(5000);

  Serial.println("check setEncoders()...");
  Angles encoders;
  for(auto &val : encoders)
    val = 2048;
  myCobot.SetEncoders(encoders, 50);
  delay(5000);
}
