#include <MyCobotBasic.h>
#include <ParameterList.h>

MyCobotBasic myCobot;

Encoders encoders;

void setup()
{
    // 打开Atom链接
    myCobot.setup();
    myCobot.powerOn();
    Serial.begin(9600);
}
void loop()
{
    encoders = myCobot.getEncoders();
    for (auto encoder : encoders) {
        Serial.print(encoder);
        Serial.print("   ");;
    }
    Serial.println();
}
