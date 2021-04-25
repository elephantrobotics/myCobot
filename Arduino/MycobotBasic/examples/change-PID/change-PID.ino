// Plase Faist Read README.txt
// ElephantRobotics

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
    int P,I,D;
   for(int i = 1; i <7 ; i++)
   {
    if(i < 4){
       P = 5;
       I = 0;
       D = 15;
    }else{
         P = 8;
         I = 0;
         D = 24;
    }
     myCobot.setServoData(i, 21, P);//P
     delay(50);
     myCobot.setServoData(i, 22, D);//D
     delay(50);
     myCobot.setServoData(i, 23, I);//I
     delay(50);
     Serial.print("servo:");
     Serial.print(i);
     Serial.println(" CHANGE PID to Mode 1");
   }
  }else if (M5.BtnB.wasReleased()) {
    int P,I,D;
    P = 10;
    I = 1;
    D = 0;
    for(int i = 1; i <7 ; i++){
      myCobot.setServoData(i, 21, P);//P
      delay(50);
      myCobot.setServoData(i, 22, D);//D
      delay(50);
      myCobot.setServoData(i, 23, I);//I
      delay(50);
     Serial.print("servo:");
     Serial.print(i);
     Serial.println("CHANGE PID to Mode 2");
    }  
   }
   else if (M5.BtnC.wasReleased()) {
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
