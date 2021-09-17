#include <MyCobotBasic.h>
#include <ParameterList.h>

MyCobotBasic myCobot;

void setup() {
  myCobot.setup();
  delay(500);
  myCobot.powerOn();
  delay(500);
  M5.Lcd.clear(BLACK);
  delay(50);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(120, 5);
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.println("myCobot");
  M5.Lcd.setCursor(55, 25);
  M5.Lcd.println("SimpleTransponder");
  M5.Lcd.setCursor(5, 60);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.print("Power: ");
  int state = myCobot.isPoweredOn();
  if (state == 1) {
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.println(" ON");
  } else {
    M5.Lcd.setTextColor(RED);
    M5.Lcd.println(" OFF");
  }
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setBrightness(8);
  
  Serial.begin(115200);    // Connection to USB
  Serial2.begin(1000000);  // Connection to the Atom
}

void loop() {
  if (Serial.available() > 0) {    // If anything comes in Serial (USB),
    Serial2.write(Serial.read());  // read it and send it out Serial2.
  }
  if (Serial2.available() > 0) {   // If anything comes in Serial 2,
    Serial.write(Serial2.read());  // read it and send it out Serial (USB).
  }
}
