#include <MyCobotBasic.h>
#include <ParameterList.h>

MyCobotBasic myCobot;
int baundrate = 115200;
int PID[6][3] = {{10, 0, 1}, {10, 0, 1}, {10, 0, 1}, {32, 32, 0}, {10, 0, 1}, {10, 0, 1}};
int pid_hex[3] = {21, 22, 23};

void info();

void setup() {
    Serial.begin(115200);
    Serial2.begin(BAUD_RATE);
    delay(100);
    myCobot.setup();
    delay(100);
    myCobot.powerOn();
    delay(100);
    for (int i = 0; i + 1 < 7; i++) {
        for (int j = 0; j < 3; j++) {
                delay(100);
                myCobot.setServoData(i+1, pid_hex[j], PID[i][j]);
                delay(100);
        }
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
