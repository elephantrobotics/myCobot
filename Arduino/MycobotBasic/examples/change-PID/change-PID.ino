// Plase Faist Read README.txt
// ElephantRobotics

#include <MycobotBasic.h>
#include <ParameterList.h>

MycobotBasic myCobot;
int baundrate = 1000000;
#define GREY 0x5AEB

void setup() {
  myCobot.setup();
  myCobot.powerOn();
  Serial.begin(9600);
  delay(200);
  info();
}
void info(){
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.printf("myCobot");
  M5.Lcd.setCursor(0, 40);
  M5.Lcd.drawFastHLine(0,70,320,GREY);
  M5.Lcd.setTextSize(3);
  M5.Lcd.println("Basic set PID");
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(0, 100);
  M5.Lcd.println("Press A - Mode 1");
  M5.Lcd.println();
  M5.Lcd.println("Press B - Mode 2");
  M5.Lcd.println();
  M5.Lcd.println("Press C - READ PID");
}
void loop() {
  M5.update();
  if (M5.BtnA.wasReleased()) {
    change_mode1();
    delay(3000);
    info();
  }else if (M5.BtnB.wasReleased()) {
    change_mode2();
    delay(3000);
    info();
   }
   else if (M5.BtnC.wasReleased()) {
    read_pid();
    delay(3000);
    info();
}
}

void read_pid(){
  M5.Lcd.clear(BLACK);
  M5.Lcd.setCursor(0,10);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("Servo CHANGE PID is");
  for(int i =1; i <7; i++)
  { 
     M5.Lcd.print("servo: ");
     M5.Lcd.print(i);
     M5.Lcd.print(" P: ");
     M5.Lcd.print(myCobot.getServoData(i, 21));//P
     delay(50);
     M5.Lcd.print(" D: ");
     M5.Lcd.print(myCobot.getServoData(i, 22));//D
     delay(50);
     M5.Lcd.print(" I: ");
     M5.Lcd.print(myCobot .getServoData(i, 23));//I
     delay(50);
     M5.Lcd.println();
     M5.Lcd.println();
  }
}

void change_mode2(){
  M5.Lcd.clear(BLACK);
  M5.Lcd.setCursor(0,10);
  M5.Lcd.setTextSize(2);
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
  } 
  M5.Lcd.println("CHANGE PID to Mode 2");
  M5.Lcd.println();
  M5.Lcd.println("Serco 1-6 :");
  M5.Lcd.println();
  M5.Lcd.println("P = 10, I = 1, D = 0");
}
void change_mode1(){
  M5.Lcd.clear(BLACK);
  M5.Lcd.setCursor(0,10);
  M5.Lcd.setTextSize(2);
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
   
 }
  M5.Lcd.println("Servo CHANGE PID to Mode 1");
  M5.Lcd.println();
  M5.Lcd.println("Serco 1-3 :");
  M5.Lcd.println();
  M5.Lcd.println("P = 5, I = 0, D = 15");
  M5.Lcd.println();
  M5.Lcd.println("Serco 4-6 :");
  M5.Lcd.println();
  M5.Lcd.println("P = 8, I = 0, D = 24");
}
