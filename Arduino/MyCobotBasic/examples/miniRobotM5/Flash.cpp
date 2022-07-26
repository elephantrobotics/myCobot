#include "Flash.h"

/*
 * Function: infomation main interface display
 */
void Flash::info()
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
    M5.Lcd.println("Flash");
    M5.Lcd.setCursor(0, 100);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.println("Press A - Flash");
    M5.Lcd.println();
    M5.Lcd.println("Press C - Exit");
}

void Flash::run(MyCobotBasic &myCobot)
{
    esp_sleep_enable_timer_wakeup(20000000);
    info();
    while (1) {
        // put your main code here, to run repeatedly:
        M5.update(); // need to call update()
        M5.Lcd.setCursor(0, 0);
        // M5.Lcd.clear(BLACK);

        if (M5.BtnA.wasReleased()) {
            Flash::SetIo();
            SetInfo();
        }
        if (M5.BtnC.wasReleased()) {
            break;
        }
    }
}

/*
 * Function: when flash set io
 */
void Flash::SetIo()
{
    esp_deep_sleep_start();
}

void Flash::SetInfo()
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
    M5.Lcd.println("Flash");
    M5.Lcd.setCursor(0, 100);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.println("Ready to flash");
}
