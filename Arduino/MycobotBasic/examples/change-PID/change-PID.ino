#include <MycobotBasic.h>
#include <ParameterList.h>

MycobotBasic myCobot;
int baundrate = 1000000;

void setup() {
  myCobot.setup();
  myCobot.powerOn();
  Serial.begin(9600);
  delay(200);
}

void loop() {

  M5.update();
  if (M5.BtnA.wasReleased()) {

   for(int i = 1; i <7 ; i++)
   {
     myCobot.setServoData(i, 21, 10);//P
     delay(30);
     myCobot.setServoData(i, 22, 0);//D
     delay(30);
     myCobot.setServoData(i, 23, 2);//I
     delay(30);
     Serial.print("servo");
     Serial.print(i);
     Serial.println("CHACK PID OK");
   }
   

  } else if (M5.BtnB.wasReleased()) {
    for(int i =1; i <7; i++)
    { 
       Serial.print("servo: ");
       Serial.print(i);
       Serial.print(" P: ");
       Serial.print(myCobot.getServoData(i, 21));//P
       delay(50);
       Serial.print(" D: ");
       Serial.print(myCobot.getServoData(i, 22));//D
       delay(50);
       Serial.print(" I: ");
       Serial.print(myCobot .getServoData(i, 23));//I
       delay(50);
       Serial.println();
  }
}
}
