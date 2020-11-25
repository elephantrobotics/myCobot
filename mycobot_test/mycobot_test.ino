#include <MycobotBasic.h>

MycobotBasic myCobot;

void setup() {
  myCobot.setup();
  for(int i = 1; i < 7; i++)         // init
    {
      myCobot.setServoEncoder(i, 2048, 3000);
      delay(500);
    }
}

void loop() {
  for(int i = 1; i < 7; i++)        //run
    {
      myCobot.setAngle(i, -50, 3000);
      delay(2000);
      myCobot.setAngle(i, 50, 3000);
      delay(2000);
      myCobot.setAngle(i, 0, 3000);
      delay(2000);
    }
}
