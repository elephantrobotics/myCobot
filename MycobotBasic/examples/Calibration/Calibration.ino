#include <MycobotBasic.h>

MycobotBasic myCobot;
int calibrate_servo_no = 1;

void setup() {
  myCobot.setup();
  M5.Lcd.setTextSize(3);

  info();
}

void loop() {
  // put your main code here, to run repeatedly:
    M5.update(); // need to call update()  
    M5.Lcd.setCursor(0,0);
   // M5.Lcd.clear(BLACK);
  
     if (M5.BtnA.wasPressed()) {
      BtnAPressOnce();
      } 
    if (M5.BtnB.wasPressed()) {
        BtnBPressOnce();
      }

   if (M5.BtnC.wasPressed()) {
      BtnCPressOnce();
      }

   if(M5.BtnB.wasReleasefor(800)){  // force to test the servos
      calibrate_servo_no = 7;
      BtnBPressOnce();
     }
  

}

void BtnAPressOnce()
{
  M5.Lcd.clear(BLACK);
  delay(50);
  
  if (calibrate_servo_no>6) 
  {
    M5.Lcd.print("Already Calibrate all \n");
    delay(500);
    info();
    return;
  }
  
  myCobot.calibrateServo(calibrate_servo_no);

  M5.Lcd.print("Calibrating\nServo\n\n");
  M5.Lcd.setTextSize(8);
  M5.Lcd.printf("%d",calibrate_servo_no);
  M5.Lcd.setTextSize(3);
  
  delay(100);

  myCobot.setServoEncoder(calibrate_servo_no,2048,1000);
  delay(400);

  calibrate_servo_no ++;
}



void BtnBPressOnce()
{
  M5.Lcd.clear(BLACK);
  delay(50);
  
  if (calibrate_servo_no > 6)
  {
     for (int i = 1; i < 7; i ++)
    {
      M5.Lcd.printf("Move servo %d \n",i);
      
      // relase all servos
      myCobot.setServoEncoder(i, 2148 , 1000);
      delay(500);
      myCobot.setServoEncoder(i, 1948 , 1000);
      delay(500);
      myCobot.setServoEncoder(i, 2048 , 1000);
      delay(500);
      
    }
    
    delay(1000);
    info();
  }
  else
  {
    M5.Lcd.print("Only move after all servo calibrated");
    return;
  }
}

void BtnCPressOnce()
{
  M5.Lcd.clear(BLACK);
  delay(50);
  
  M5.Lcd.print("Restart to calibrate");
  calibrate_servo_no = 1;
  myCobot.releaseAllServos();
  delay(1000);
  info();
}

void info()
{
  M5.Lcd.clear(BLACK);
  delay(50);
  M5.Lcd.setCursor(0,0);
  delay(50);
  
  M5.Lcd.print("Press A - Cablibrate Servo 1~6 \n\n");
  M5.Lcd.print("Press B - Test Servos (long press to force testing)\n\n");
  M5.Lcd.print("Press C - Restart Calibaration");
}
