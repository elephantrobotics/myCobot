#include "Information.h"

void Connect::info()
{
    tft.fillScreen(TFT_BLACK);//黑色填充屏幕
    tft.setTextColor(TFT_BLACK);
    tft.setTextColor(TFT_RED);
    tft.setTextSize(3);
    tft.setCursor(10, 10);
    tft.printf(TYPE);
    tft.setCursor(10, 40);
    tft.drawFastHLine(0, 70, 320, GREY);
    tft.setTextSize(2);
    tft.println("Status Inspection");

    distep.Start();

}

void Connect::run(MyCobotBasic &myCobot)
{
    Serial.println("infomation----");
    tft.setRotation(3);

    distep.y_pos = pos_y;
    distep.rect_pos1 = rect1;
    distep.rect_pos2 = rect2;
    String menu[2] = {"Servos motor", "Firmwave"};
    int num[2] = {0, 1};
    distep.MenuInit(num, menu, 2);
    info();
    distep.MenuChoice();
    while (1) {
        // put your main code here, to run repeatedly:
        //m5.update(); // need to call update()
        tft.setCursor(0, 0);
        if (digitalRead(WIO_5S_DOWN) == LOW) {
            distep.state += 1;
            //Connect::testServo(myCobot);
            distep.MenuChoice();
        }
        if (digitalRead(WIO_5S_UP) == LOW) {
            distep.state -= 1;
            //Connect::testServo(myCobot);
            distep.MenuChoice();
        }
        if (digitalRead(WIO_5S_RIGHT) == LOW) {
            switch (distep.state) {
                case 0:
                    Connect::testServo(myCobot);
                    break;
                case 1:
                    Connect::ReadConfig(myCobot);
                    break;
                default:
                    break;
            }
        }
        if (digitalRead(WIO_5S_LEFT) == LOW) {
            break;
        }
        delay(200);
    }
}

void Connect::testServo(MyCobotBasic &myCobot)
{
    tft.fillScreen(TFT_BLACK);//黑色填充屏幕;
    delay(50);
    tft.setTextSize(2);
    tft.setCursor(10, 10);
    tft.setTextColor(TFT_RED);

    tft.println("connect test");
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    tft.drawFastHLine(0, 50, 320, GREY);
    tft.setCursor(10, 70);
    int m = 0;
    tft.print("atom - ");
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
        tft.setTextColor(TFT_GREEN);
        tft.println("ok");
    } else {
        tft.setTextColor(TFT_RED);
        tft.println("no");
        delay(50);
    }
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    int y = 70;
    for (int i = 1; i < 7; i++) {
        y += 20;
        tft.setTextColor(TFT_WHITE);
        tft.setCursor(10, y);
        tft.print("servo ");
        tft.print(i);
        tft.print(" - ");
        Serial.print("state all = ");
        Serial.println(myCobot.isAllServoEnabled());

        int servo_state = myCobot.isServoEnabled(i);
        if (servo_state == 1) {
            tft.setTextColor(TFT_GREEN);
            tft.println("ok");
        } else {
            tft.setTextColor(TFT_RED);
            tft.println("no");
        }
        delay(50);
        Serial.print("state  = ");
        Serial.println(servo_state);
    }
    //m5.update();
    delay(3000);
    info();
}


void Connect::ReadConfig(MyCobotBasic &myCobot)
{
    char s[10];
    tft.fillScreen(TFT_BLACK);//黑色填充屏幕
    delay(50);

    tft.setTextSize(2);
    tft.setCursor(10, 10);
    tft.setTextColor(TFT_RED);
    tft.println("connect test");
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    tft.drawFastHLine(0, 50, 320, GREY);
    tft.setTextSize(2);
    tft.setCursor(10, 70);
    tft.printf("robot version :");
    int version = myCobot.getAtomVersion();
    sprintf(s, "V%.2f", version / 10.0);
    tft.setCursor(200, 70);
    tft.setTextColor(TFT_RED);
    tft.println(s);

    tft.setTextColor(TFT_WHITE);
    tft.setCursor(10, 100);
    tft.println("basic version :");

    tft.setCursor(200, 100);
    tft.setTextColor(TFT_RED);
    tft.println("V1.0");
    //m5.update();
    delay(3000);
    info();
}
