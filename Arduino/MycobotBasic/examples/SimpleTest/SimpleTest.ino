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
      myCobot.setRGB(0XFF, 0, 0);       // set RGB show red
      delay(50);
      myCobot.setAngle(i, -50, 3000);   // set joint angle - 50 degree
      delay(2000);
      myCobot.setRGB(0, 0XFF, 0);       // set RGB show blue
      delay(50);
      myCobot.setAngle(i, 50, 3000);    // set joint angle 50 degree
      delay(2000);
      myCobot.setRGB(0, 0, 0XFF);       // set RGB show green
      delay(50);
      myCobot.setAngle(i, 0, 3000);     // set joint angle 0 degree
      delay(2000);
    }
}
