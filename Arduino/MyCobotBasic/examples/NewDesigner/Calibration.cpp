#include "Calibration.h"

int calibrate_servo_no = 1;

void Calibration::run(MyCobotBasic &myCobot)
{
    board->SetTextSize(2);
    // EEPROM.begin(EEPROM_SIZE);//new
    board->SetRotation(3);
    myCobot.setLEDRGB(255, 255, 255);

    distep.y_pos = pos_y;
    distep.rect_pos1 = rect1;
    distep.rect_pos2 = rect2;
    int num[3] = {0, 1, 2};
    if (lan == 2) {
        string menu[2] = {"设置舵机零位", "测试舵机"};
        distep.MenuInit(num, menu, 2);
    } else if (lan == 1) {
        string menu[3] = {"Calibrate Servo", "Test Servos", "Exit"};
        distep.MenuInit(num, menu, 3);
    }

    Calibration::info();
    distep.MenuChoice();
    while (1) {
        board->BtnUpdate(); // need to call update()
        board->SetCursor(0, 0);
        if (board->IsBtnClicked(0)) {
            //myCobot.setLEDRGB(255, 0, 0);
            //Calibration::init(myCobot);
            distep.state += 1;
            distep.MenuChoice();
        }
        if (board->IsBtnClicked(1)) {
            distep.state += 1;
            distep.MenuChoice();
        }
        if (board->IsBtnClicked(2)) {
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
                case 2: {
                    Exit = true;
                }
                break;
                default:
                    break;
            }
        }
        if (board->IsBtnClicked(3) || Exit) {
            Exit = false;
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
        board->ClearScreen(Board_BLACK);//黑色填充屏幕
    }
    board->SetTextColor(Board_BLACK);
    board->SetTextColor(Board_RED);
    board->SetTextSize(3);
    board->SetCursor(10, 10);
    board->Printf(TYPE);
    board->SetCursor(10, 40);
    board->DrawFastHLine(0, 70, 320, Board_GREY);
    board->SetTextSize(2);
    board->Println("Basic Calibration");
}

void Calibration::info()
{
    DisplayHead(true);
    board->SetTextSize(2);
    board->SetTextColor(Board_WHITE);
    board->SetCursor(0, 100);
    delay(50);

    distep.Start();
    board->BtnUpdate();
}

void Calibration::init(MyCobotBasic &myCobot)
{
    board->ClearScreen(Board_BLACK);//黑色填充屏幕
    delay(50);

    if (calibrate_servo_no > 6) {
        if (lan == 2) {
            board->DrawString("已经设置好所有舵机", 20, 20, 1);
        }
        if (lan == 1) {
            DisplayHead(true);
            board->SetCursor(20, 100);
            board->SetTextColor(Board_WHITE);
            board->SetTextSize(2);
            board->Printf("Already Calibrate all!!\n");
        }
        delay(2000);
        Calibration::info();
        return;
    }

    myCobot.setServoCalibration(calibrate_servo_no);

    if (lan ==  2) {
        board->DrawString("已设置舵机", 20, 100, 1);
        board->SetTextSize(2);
        board->SetCursor(0, 150);
        board->Printf("%d", calibrate_servo_no);
        board->SetTextSize(2);
    }
    if (lan == 1) {
        board->SetTextSize(2);
        board->SetTextColor(Board_RED);
        board->SetCursor(0, 20);
        board->Printf("Calibrating Servo\n");
        board->SetCursor(0, 40);
        board->DrawFastHLine(0, 70, 320, Board_GREY);
        board->SetTextSize(7);
        board->SetTextColor(Board_WHITE);
        board->SetCursor(140, 125);
        //board->Printf("%d",calibrate_servo_no);
        board->Println(calibrate_servo_no);

        board->SetTextSize(2);
        board->SetCursor(235/*35*/, 210);
        board->Printf("NEXT");
//    board->SetCursor(235, 210);
//    board->Printf(" EXIT ");
    }

    delay(100);

    myCobot.setEncoder(calibrate_servo_no, 2047);
    delay(400);

    calibrate_servo_no ++;
}

void Calibration::test(MyCobotBasic &myCobot)
{
    board->ClearScreen(Board_BLACK);//黑色填充屏幕
    delay(50);
    // move all servos
    if (calibrate_servo_no >= 6) {
        for (int i = 1; i < 7; i ++) {
            if (lan == 2) {
                board->DrawString("已设置舵机零位 ", 20, 20, 1);
            }
            if (lan == 1) {
                DisplayHead(false);
                board->SetTextSize(2);
                board->SetTextColor(Board_WHITE);
                board->SetCursor(20, 80 + 20 * i);
                board->Printf("Move servo -> ");
                board->Println(i);
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
            board->DrawString("请先设定关节零位", 20, 20, 1);
        }
        if (lan == 1) {
            DisplayHead(true);
            board->SetCursor(0, 100);
            board->SetTextSize(2);
            board->SetTextColor(Board_WHITE);
            board->Printf("Only move after all servo calibrated");
        }
        delay(2000);
        Calibration::info();
        return;
    }
}

void Calibration::reset(MyCobotBasic &myCobot)
{
    board->ClearScreen(Board_BLACK);//黑色填充屏幕
    delay(50);
    if (lan == 2) {
        board->DrawString("重新设置", 20, 20, 1);
    }
    if (lan == 1) {
        DisplayHead(true);
        board->SetCursor(0, 100);
        board->SetTextSize(2);
        board->SetTextColor(Board_WHITE);
        board->Printf("Restart to calibrate!!");
    }
    calibrate_servo_no = 0;
    //关闭扭力输出
    myCobot.setFreeMove();
    delay(1000);
    //Calibration::info();
}
