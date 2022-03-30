#include "Calibration.h"

int calibrate_servo_no = 1;

void Calibration::run(MyCobotBasic &myCobot)
{
    tft.setTextSize(2);
    // EEPROM.begin(EEPROM_SIZE);//new
    tft.setRotation(3);
    myCobot.setLEDRGB(255, 255, 255);

    distep.y_pos = pos_y;
    distep.rect_pos1 = rect1;
    distep.rect_pos2 = rect2;
    int num[2] = {0, 1};
    if (lan == 2) {
        String menu[2] = {"设置舵机零位", "测试舵机"};
        distep.MenuInit(num, menu, 2);
    } else if (lan == 1) {
        String menu[2] = {"Calibrate Servo", "Test Servos"};
        distep.MenuInit(num, menu, 2);
    }

    Calibration::info();
    distep.MenuChoice();
    while (1) {
        //m5.update(); // need to call update()
        tft.setCursor(0, 0);
        if (digitalRead(WIO_5S_DOWN) == LOW) {
            //myCobot.setLEDRGB(255, 0, 0);
            //Calibration::init(myCobot);
            distep.state += 1;
            distep.MenuChoice();
        }
        if (digitalRead(WIO_5S_UP) == LOW) {
            distep.state += 1;
            distep.MenuChoice();
        }
        if (digitalRead(WIO_5S_RIGHT) == LOW) {
            switch (distep.state) {
                case 0: {
                    myCobot.setLEDRGB(255, 0, 0);
                    Calibration::init(myCobot);
                }
                break;
                case 1: {
                    myCobot.setLEDRGB(0, 255, 0);
                    Calibration::test(myCobot);
                }
                break;
                default:
                    break;
            }
        }
        if (digitalRead(WIO_5S_LEFT) == LOW) {
            myCobot.setLEDRGB(0, 0, 255);
            Calibration::reset(myCobot);
            break;
        }
        delay(200);
    }
}

void Calibration::DisplayHead(bool isClearAll)
{
    if (isClearAll) {
        tft.fillScreen(TFT_BLACK);//黑色填充屏幕
    }
    tft.setTextColor(TFT_BLACK);
    tft.setTextColor(TFT_RED);
    tft.setTextSize(3);
    tft.setCursor(10, 10);
    tft.printf(TYPE);
    tft.setCursor(10, 40);
    tft.drawFastHLine(0, 70, 320, GREY);
    tft.setTextSize(2);
    tft.println("Basic Calibration");
}

void Calibration::info()
{
    DisplayHead(true);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(0, 100);
    delay(50);

    distep.Start();
    //m5.update();
}

void Calibration::init(MyCobotBasic &myCobot)
{
    tft.fillScreen(TFT_BLACK);//黑色填充屏幕
    delay(50);

    if (calibrate_servo_no > 6) {
        if (lan == 2) {
            tft.drawString("已经设置好所有舵机", 20, 20, 1);
        }
        if (lan == 1) {
            DisplayHead(true);
            tft.setCursor(20, 100);
            tft.setTextColor(TFT_WHITE);
            tft.setTextSize(2);
            tft.print("Already Calibrate all!!\n");
        }
        delay(2000);
        Calibration::info();
        return;
    }

    myCobot.setServoCalibration(calibrate_servo_no);

    if (lan ==  2) {
        tft.drawString("已设置舵机", 20, 100, 1);
        tft.setTextSize(2);
        tft.setCursor(0, 150);
        tft.printf("%d", calibrate_servo_no);
        tft.setTextSize(2);
    }
    if (lan == 1) {
        tft.setTextSize(2);
        tft.setTextColor(TFT_RED);
        tft.setCursor(0, 20);
        tft.print("Calibrating Servo\n");
        tft.setCursor(0, 40);
        tft.drawFastHLine(0, 70, 320, GREY);
        tft.setTextSize(7);
        tft.setTextColor(TFT_WHITE);
        tft.setCursor(140, 125);
        tft.printf("%d", calibrate_servo_no);

        tft.setTextSize(2);
        tft.setCursor(235/*35*/, 210);
        tft.print("NEXT");
//    tft.setCursor(235, 210);
//    tft.print(" EXIT ");
    }

    delay(100);

    myCobot.setEncoder(calibrate_servo_no, 2047);
    delay(400);

    calibrate_servo_no ++;
}

void Calibration::test(MyCobotBasic &myCobot)
{
    tft.fillScreen(TFT_BLACK);//黑色填充屏幕
    delay(50);
    // move all servos
    if (calibrate_servo_no >= 6) {
        for (int i = 1; i < 7; i ++) {
            if (lan == 2) {
                tft.drawString("已设置舵机零位 ", 20, 20, 1);
            }
            if (lan == 1) {
                DisplayHead(false);
                tft.setTextSize(2);
                tft.setTextColor(TFT_WHITE);
                tft.setCursor(20, 80 + 20 * i);
                tft.print("Move servo -> ");
                tft.println(i);
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
        if (lan == 2) {
            tft.drawString("请先设定关节零位", 20, 20, 1);
        }
        if (lan == 1) {
            DisplayHead(true);
            tft.setCursor(0, 100);
            tft.setTextSize(2);
            tft.setTextColor(TFT_WHITE);
            tft.print("Only move after all servo calibrated");
        }
        delay(2000);
        Calibration::info();
        return;
    }
}

void Calibration::reset(MyCobotBasic &myCobot)
{
    tft.fillScreen(TFT_BLACK);//黑色填充屏幕
    delay(50);
    if (lan == 2) {
        tft.drawString("重新设置", 20, 20, 1);
    }
    if (lan == 1) {
        DisplayHead(true);
        tft.setCursor(0, 100);
        tft.setTextSize(2);
        tft.setTextColor(TFT_WHITE);
        tft.print("Restart to calibrate!!");
    }
    calibrate_servo_no = 0;
    //关闭扭力输出
    myCobot.setFreeMove();
    delay(1000);
    //Calibration::info();
}
