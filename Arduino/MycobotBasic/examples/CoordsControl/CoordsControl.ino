#include <MycobotBasic.h>
#include <ParameterList.h>


MycobotBasic myCobot;


bool Servo_state = 1;

int power_pin = 2;
int open_pin = 5;
int out_state = 1;
                    
Coords pos_init_1 = {155.10, -55.10, 90.10, -179.10, 0.10, -90.10};
Coords data1;

Angles angles_0 = {0, 0, 0, 0, 0, 0};
Angles angles_1 = {-90.01, -45, -90.30, 45.09, 90.70, 90.63};
Angles angles_2 = {-0, -45, -90.30, 45.09, 90.70, 90.63};    
Angles angles_3 = {-0, -45, -90.30, 45.09, 90.70, 90.63};                 
void move_coords(int dir = 0, int num = 0);

void setup() {
  myCobot.setup();
  myCobot.powerOn();
  
  pinMode(power_pin, OUTPUT);
  pinMode(open_pin, OUTPUT);
  
  set_pump(1);
  
  myCobot.setLEDRGB(0, 0, 255);
  delay(100);
  myCobot.writeAngles(angles_0,30);
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
    M5.update(); // need to call update()  
    M5.Lcd.setCursor(0,0);
    int j = 0;
     if (M5.BtnA.wasReleased()) {
      reless();
      } 
    if (M5.BtnB.wasReleased()) {   
      myCobot.writeCoords(pos_init_1,30);
    }
    if (M5.BtnC.wasReleased()) {
      data1 = pos_init_1;
      delay(50);
      move_coords(0, 10);
      delay(2000);
      move_coords(0, -10);
      delay(2000);
      move_coords(1, 10);
      delay(2000);
      move_coords(1, -10);
      delay(2000);
      move_coords(2, 10);
      delay(2000);
      move_coords(2, -10);
      delay(2000);
}
}

void reless()
{
  for(int i = 1; i<7; i++){
    myCobot.setServoData(i, 40, !Servo_state);
    delay(30);
  }
  Servo_state = !Servo_state;
}

Angles read_Angles()
{
  Angles data2;
  data2 = myCobot.getAngles();
  delay(50);
  for(int i = 0; i<6; i++){
    Serial.print(data2[i]);
    Serial.print(", ");
  }
  Serial.println();
  return data2;
}

Coords read_pos()
{
  Coords data1;
  data1 = myCobot.getCoords();
  delay(50);
  for(int i = 0; i<6; i++){
    Serial.print(data1[i]);
    Serial.print(", ");
  }
  Serial.println();
  return data1;
}

void move_coords(int dir, int num)
{
  if (num > 0){
    for(int i = 0; i<num; i++){
    myCobot.writeCoords(data1,15);
    for(int i=0; i<6; i++){
      Serial.print(data1[i]);
      Serial.print(", ");
    }
    Serial.println("");
    data1[dir] += 10;
    delay(50);
  }
  }else{
    num = 0-num;
    for(int i = 0; i<num; i++){
    myCobot.writeCoords(data1,15);
    for(int i=0; i<6; i++){
      Serial.print(data1[i]);
      Serial.print(", ");
    }
    Serial.println("");
    data1[dir] -= 10;
    delay(50);
  }
  } 
}


void set_pump(int out_state){
    digitalWrite(power_pin, out_state);
    digitalWrite(open_pin, out_state);
}
