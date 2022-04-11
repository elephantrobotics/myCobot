#include <MyCobotBasic.h>
#include <ParameterList.h>

MyCobotBasic myCobot;
int baundrate = 115200;

void setup() {
    Serial.begin(115200);
    Serial2.begin(BAUD_RATE);
    delay(100);
    myCobot.setup();
    delay(100);
    myCobot.powerOn();
    delay(100);
    while (myCobot.getServoData(4, 13) != 85) {
        delay(100);
        myCobot.setServoData(4, 13, 85);
        delay(100);
    }
    info();
}

void loop() {
}

void info()
{
    M5.Lcd.clear(BLACK);
    M5.Lcd.setTextColor(RED);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(10, 80);
    M5.Lcd.println("Firmware upgrade successful");
}
