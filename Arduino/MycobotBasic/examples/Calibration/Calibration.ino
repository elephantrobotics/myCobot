#include <MycobotBasic.h>
#include <ParameterList.h>

MycobotBasic myCobot;
int calibrate_servo_no = 1;

void setup() {
  myCobot.setup();
  M5.Lcd.setTextSize(3);
  myCobot.powerOn();
  myCobot.setLEDRGB(255, 255, 255);

  info();
}

void loop() {
  // put your main code here, to run repeatedly:
    M5.update(); // need to call update()  
    M5.Lcd.setCursor(0,0);
   // M5.Lcd.clear(BLACK);
  
     if (M5.BtnA.wasPressed()) {
      myCobot.setLEDRGB(255, 0, 0);
      BtnAPressOnce();
      } 
    if (M5.BtnB.wasPressed()) {
        myCobot.setLEDRGB(0, 255, 0);
        BtnBPressOnce();
      }

   if (M5.BtnC.wasPressed()) {
      myCobot.setLEDRGB(0, 0, 255);
      BtnCPressOnce();
      }

   if(M5.BtnB.wasReleasefor(800)){  // force to test the servos
      calibrate_servo_no = 6;
      BtnBPressOnce();
     }
  

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
  
  myCobot.setServoCalibration(calibrate_servo_no);

  M5.Lcd.print("Calibrating\nServo\n\n");
  M5.Lcd.setTextSize(8);
  M5.Lcd.printf("%d",calibrate_servo_no);
  M5.Lcd.setTextSize(3);
  
  delay(100);

  myCobot.SetEncoder(calibrate_servo_no, 2047);
  delay(400);

  calibrate_servo_no ++;
}



void BtnBPressOnce()
{
  M5.Lcd.clear(BLACK);
  delay(50);
  // move all servos
  if (calibrate_servo_no > 6)
  {
     for (int i = 1; i < 7; i ++)
    {
      M5.Lcd.printf("Move servo %d \n",i);

      myCobot.SetEncoder(i, 1848);
      delay(2500);
      myCobot.SetEncoder(i, 2248);
      delay(3000);
      myCobot.SetEncoder(i, 2048);
      delay(2500);
    }
    info();
  }
  else{
    M5.Lcd.print("Only move after all servo calibrated");
    return;
  }
}

void BtnCPressOnce()
{
  M5.Lcd.clear(BLACK);
  delay(50);
  
  M5.Lcd.print("Restart to calibrate");
  calibrate_servo_no = 0;
  //关闭扭力输出
  myCobot.setFreeMove();
  delay(1000);
  info();
}
