#include "Information.h"

void Connect::info()
{
    board->ClearScreen(Board_BLACK);//黑色填充屏幕
    board->SetTextColor(Board_BLACK);
    board->SetTextColor(Board_RED);
    board->SetTextSize(3);
    board->SetCursor(10, 10);
    board->Printf(TYPE);
    board->SetCursor(10, 40);
    board->DrawFastHLine(0, 70, 320, Board_GREY);
    board->SetTextSize(2);
    board->Println("Status Inspection");

    distep.Start();

}

void Connect::run(MyCobotBasic &myCobot)
{
    Serial.println("infomation----");
    board->SetRotation(3);
    distep.y_pos = pos_y;
    distep.rect_pos1 = rect1;
    distep.rect_pos2 = rect2;
    string menu[3] = {"Servos motor", "Firmwave", "Exit"};
    int num[3] = {0, 1, 2};
    distep.MenuInit(num, menu, 3);
    info();
    distep.MenuChoice();
    while (1) {
        // put your main code here, to run repeatedly:
        board->BtnUpdate(); // need to call update()
        board->SetCursor(0, 0);
        if (board->IsBtnClicked(0)) {
            distep.state += 1;
            //Connect::testServo(myCobot);
            distep.MenuChoice();
        }
        if (board->IsBtnClicked(1)) {
            distep.state -= 1;
            //Connect::testServo(myCobot);
            distep.MenuChoice();
        }
        if (board->IsBtnClicked(2)) {
            switch (distep.state) {
                case 0:
                    Connect::testServo(myCobot);
                    break;
                case 1:
                    Connect::ReadConfig(myCobot);
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
            break;
        }
        delay(200);
    }
}

void Connect::testServo(MyCobotBasic &myCobot)
{
    board->ClearScreen(Board_BLACK);//黑色填充屏幕;
    delay(50);
    board->SetTextSize(2);
    board->SetCursor(10, 10);
    board->SetTextColor(Board_RED);

    board->Println("connect test");
    board->SetTextSize(2);
    board->SetTextColor(Board_WHITE);
    board->DrawFastHLine(0, 50, 320, Board_GREY);
    board->SetCursor(10, 70);
    int m = 0;
    board->Print("atom - ");
    for (int c = 1; c < 4; c++) {
        int state = myCobot.isPoweredOn();
        delay(20);
        if (state == 1) {
            m = m + 1;
        } else {
            m = m;
        }
    }
    if (m >= 2) {
        board->SetTextColor(Board_GREEN);
        board->Println("ok");
    } else {
        board->SetTextColor(Board_RED);
        board->Println("no");
        delay(50);
    }
    board->SetTextSize(2);
    board->SetTextColor(Board_WHITE);
    int y = 70;
    for (int i = 1; i < 7; i++) {
        y += 20;
        board->SetTextColor(Board_WHITE);
        board->SetCursor(10, y);
        board->Print("servo ");
        board->Print(i);
        board->Print(" - ");
        Serial.print("state all = ");
        Serial.println(myCobot.isAllServoEnabled());

        int servo_state = myCobot.isServoEnabled(i);
        if (servo_state == 1) {
            board->SetTextColor(Board_GREEN);
            board->Println("ok");
        } else {
            board->SetTextColor(Board_RED);
            board->Println("no");
        }
        delay(50);
        Serial.print("state  = ");
        Serial.println(servo_state);
    }
    board->BtnUpdate();
    delay(3000);
    info();
}


void Connect::ReadConfig(MyCobotBasic &myCobot)
{
    char s[10];
    board->ClearScreen(Board_BLACK);//黑色填充屏幕
    delay(50);

    board->SetTextSize(2);
    board->SetCursor(10, 10);
    board->SetTextColor(Board_RED);
    board->Println("connect test");
    board->SetTextSize(2);
    board->SetTextColor(Board_WHITE);
    board->DrawFastHLine(0, 50, 320, Board_GREY);
    board->SetTextSize(2);
    board->SetCursor(10, 70);
    board->Printf("robot version :");
    int version = myCobot.getAtomVersion();
    sprintf(s, "V%.2f", version / 10.0);
    board->SetCursor(200, 70);
    board->SetTextColor(Board_RED);
    board->Println(s);

    board->SetTextColor(Board_WHITE);
    board->SetCursor(10, 100);
    board->Println("basic version :");

    board->SetCursor(200, 100);
    board->SetTextColor(Board_RED);
    board->Println("V1.0");
    board->BtnUpdate();
    delay(3000);
    info();
}
