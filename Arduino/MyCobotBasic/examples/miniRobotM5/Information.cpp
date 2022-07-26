#include "Information.h"

/*
 * Function: infomation main interface display
 */
void Connect::info()
{
    M5.Lcd.clear(BLACK);
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setTextColor(RED);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(0, 10);
    M5.Lcd.printf("myCobot");
    M5.Lcd.setCursor(0, 40);
    M5.Lcd.drawFastHLine(0, 70, 320, GREY);
    M5.Lcd.setTextSize(3);
    M5.Lcd.println("Status Inspection");
    M5.Lcd.setCursor(0, 100);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.println("Press A - Servos motor");
    M5.Lcd.println();
    M5.Lcd.println("Press B - Firmware");
    M5.Lcd.println();
    M5.Lcd.println("Press C - Exit");
}

void Connect::run(MyCobotBasic &myCobot)
{
    info();
    while (1) {
        // put your main code here, to run repeatedly:
        M5.update(); // need to call update()
        M5.Lcd.setCursor(0, 0);
        // M5.Lcd.clear(BLACK);

        if (M5.BtnA.wasReleased()) {
            Connect::testServo(myCobot);
        }
        if (M5.BtnB.wasReleased()) {
            Connect::ReadConfig(myCobot);
        }
        if (M5.BtnC.wasReleased()) {
            break;
        }
    }
}

/*
 * Function: Get and display the connection status of atom and 6 motors
 */
void Connect::testServo(MyCobotBasic &myCobot)
{
    M5.Lcd.clear(BLACK);
    delay(50);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(40, 10);
    M5.Lcd.setTextColor(RED);

    M5.Lcd.println("connect test");
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.drawFastHLine(0, 50, 320, GREY);
    M5.Lcd.setCursor(0, 70);
    int m = 0;
    M5.Lcd.print("atom - ");
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
        M5.Lcd.setTextColor(GREEN);
        M5.Lcd.println("ok");
    } else {
        M5.Lcd.setTextColor(RED);
        M5.Lcd.println("no");
        delay(50);
    }
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(WHITE);
    for (int i = 1; i < 7; i++) {
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.print("servo ");
        M5.Lcd.print(i);
        M5.Lcd.print(" - ");
        int servo_state = myCobot.isServoEnabled(i);
        if (servo_state == 1) {
            M5.Lcd.setTextColor(GREEN);
            M5.Lcd.println("ok");
        } else {
            M5.Lcd.setTextColor(RED);
            M5.Lcd.println("no");
        }
        delay(50);
    }
    M5.update();
    delay(3000);
    info();
}

/*
 * Function: Get and display the current basic firmware and the Atom version information that has been burned
 */

void Connect::ReadConfig(MyCobotBasic &myCobot)
{
    char s[10];
    M5.Lcd.clear(BLACK);
    delay(50);

    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(0, 10);
    M5.Lcd.setTextColor(RED);
    M5.Lcd.println("connect test");
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.drawFastHLine(0, 50, 320, GREY);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(0, 70);
    M5.Lcd.printf("robot version :");
    int version = myCobot.getAtomVersion();
    sprintf(s, "V%.2f", version / 10.0);
    M5.Lcd.setCursor(200, 70);
    M5.Lcd.setTextColor(RED);
    M5.Lcd.println(s);

    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(0, 100);
    M5.Lcd.println("basic version :");

    M5.Lcd.setCursor(200, 100);
    M5.Lcd.setTextColor(RED);
    sprintf(s, "V%.2f", SYSTEM_VERSION / 10.0);
    M5.Lcd.println(s);
    M5.update();
    delay(3000);
    info();
}
