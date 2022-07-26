#include "Calibration.h"

int calibrate_servo_no = 1;

void Calibration::run(MyCobotBasic &myCobot)
{
    M5.Lcd.setTextSize(2);
    // EEPROM.begin(EEPROM_SIZE);//new
    myCobot.setLEDRGB(255, 255, 255);
    Calibration::info();
    while (1) {
        // need to call update
        M5.update(); 
        M5.Lcd.setCursor(0, 0);
        if (M5.BtnA.wasReleased()) {
            myCobot.setLEDRGB(255, 0, 0);
            Calibration::init(myCobot);
        }
        if (M5.BtnB.wasReleased()) {
            myCobot.setLEDRGB(0, 255, 0);
            Calibration::test(myCobot);
        }
        if (M5.BtnC.wasReleased()) {
            myCobot.setLEDRGB(0, 0, 255);
            Calibration::reset(myCobot);
            break;
        }
    }
}

void Calibration::DisplayHead(bool isClearAll)
{
    if (isClearAll) {
        M5.Lcd.clear(BLACK);
    }
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setTextColor(RED);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(0, 10);
    M5.Lcd.printf("myCobot");
    M5.Lcd.setCursor(0, 40);
    M5.Lcd.drawFastHLine(0, 70, 320, GREY);
    M5.Lcd.setTextSize(3);
    M5.Lcd.println("Basic Calibration");
}

void Calibration::info()
{
    DisplayHead(true);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(0, 100);
    delay(50);
    if (language == Chinese) {
        M5.Lcd.drawString("按A键 - 设置舵机零位", 20, 40, 1);
        M5.Lcd.drawString("按B键 - 测试舵机", 20, 80, 1);
        M5.Lcd.drawString("按C键 - 退出此程序", 20, 120, 1);
    }
    if (language == English) {
        M5.Lcd.println("Press A - Calibrate Servo ");
        M5.Lcd.println();
        // M5.Lcd.print("PressB - Test Servos (long press to force testing)\n\n");
        M5.Lcd.println("Press B - Test Servos ");
        M5.Lcd.println();
        M5.Lcd.println("Press C - Exit");
//    M5.Lcd.setCursor(0, 170);
//    M5.Lcd.print("(long press to return language selection)\n");
    }
    M5.update();
}

/*
 * Function: Set joint zero position
 */
void Calibration::init(MyCobotBasic &myCobot)
{
    M5.Lcd.clear(BLACK);
    delay(50);

    /*if (calibrate_servo_no > 1 && calibrate_servo_no < 8) {
        myCobot.focusServo(calibrate_servo_no - 1);
        delay(100);
    }*/
    //由于第一次校准未成功，结束前再进行一次校准
    if (calibrate_servo_no == 7) {
        for (int i = 1; i< 7; i++) {
          myCobot.setServoCalibration(i);
          delay(100);
          myCobot.focusServo(i);
          delay(100);
        }
    }
    
    if (calibrate_servo_no >= 7) {
        if (language == Chinese) {
            M5.Lcd.drawString("已经设置好所有舵机", 20, 20, 1);
        }
        if (language == English) {
            DisplayHead(true);
            M5.Lcd.setCursor(20, 100);
            M5.Lcd.setTextColor(WHITE);
            M5.Lcd.setTextSize(2);
            M5.Lcd.print("Already Calibrate all!!\n");
        }
        delay(2000);
        Calibration::info();
        return;
    }

//    myCobot.releaseServo(calibrate_servo_no);
//    delay(100);

    myCobot.setServoCalibration(calibrate_servo_no);
    delay(100);

    if (language == Chinese) {
        M5.Lcd.drawString("已设置舵机", 20, 100, 1);
        M5.Lcd.setTextSize(2);
        M5.Lcd.setCursor(0, 150);
        M5.Lcd.printf("%d", calibrate_servo_no);
        M5.Lcd.setTextSize(2);
    }
    if (language == English) {
        M5.Lcd.setTextSize(3);
        M5.Lcd.setTextColor(RED);
        M5.Lcd.setCursor(0, 20);
        M5.Lcd.print("Calibrating Servo\n");
        M5.Lcd.setCursor(0, 40);
        M5.Lcd.drawFastHLine(0, 70, 320, GREY);
        M5.Lcd.setTextSize(7);
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.setCursor(140, 125);
        M5.Lcd.printf("%d", calibrate_servo_no);

        M5.Lcd.setTextSize(2);
        M5.Lcd.setCursor(35, 210);
        M5.Lcd.print("NEXT");
        M5.Lcd.setCursor(235, 210);
        M5.Lcd.print(" EXIT ");
    }

    delay(100);

    calibrate_servo_no ++;
}

/*
 * Function: Test the servos and move 6 servos respectively
 */
void Calibration::test(MyCobotBasic &myCobot)
{
    M5.Lcd.clear(BLACK);
    delay(50);
    // move all servos
    if (calibrate_servo_no >= 7) {
        for (int i = 1; i < 7; i ++) {
            if (language == Chinese) {
                M5.Lcd.drawString("已设置舵机零位 ", 20, 20, 1);
            }
            if (language == English) {
                DisplayHead(false);
                M5.Lcd.setTextSize(2);
                M5.Lcd.setTextColor(WHITE);
                M5.Lcd.setCursor(20, 80 + 20 * i);
                M5.Lcd.print("Move servo -> ");
                M5.Lcd.println(i);
            }

            myCobot.setEncoder(i, 1848);
            delay(2500);
            myCobot.setEncoder(i, 2248);
            delay(3000);
            myCobot.setEncoder(i, 2048);
            delay(2500);
        }
        Calibration::info();
        delay(2000);
    } else {
        if (language == Chinese) {
            M5.Lcd.drawString("请先设定关节零位", 20, 20, 1);
        }
        if (language == English) {
            DisplayHead(true);
            M5.Lcd.setCursor(0, 100);
            M5.Lcd.setTextSize(2);
            M5.Lcd.setTextColor(WHITE);
            M5.Lcd.print("Only move after all servo calibrated");
        }
        delay(2000);
        Calibration::info();
        return;
    }
}

/*
 * Function: reset joint zero position
 */
void Calibration::reset(MyCobotBasic &myCobot)
{
    M5.Lcd.clear(BLACK);
    delay(50);
    if (language == Chinese) {
        M5.Lcd.drawString("重新设置", 20, 20, 1);
    }
    if (language == English) {
        DisplayHead(true);
        M5.Lcd.setCursor(0, 100);
        M5.Lcd.setTextSize(2);
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.print("Restart to calibrate!!");
    }
    calibrate_servo_no = 1;
    //Turn off torque output
#if (!defined MyCobot_Pro_350)
    myCobot.setFreeMove();
    delay(100);
#endif
    delay(1000);
    //Calibration::info();
}
