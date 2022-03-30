#include "MyCobotLanguage.h"


MyCobotLanguage::MyCobotLanguage()
{

#if defined Mycobot_M5
    M5.begin(true, false, true);
    M5.Power.begin();
    delay(100);

    M5.Lcd.setTextSize(1);
    M5.Lcd.setFreeFont(&mycobot_24px);
    M5.Lcd.setTextDatum(TC_DATUM);
#endif

}

void MyCobotLanguage::clearLanguage()
{
#if defined Mycobot_M5
    EEPROM.write(Lan_Add, 0);
    EEPROM.commit();
    delay(100);
#endif
}


int MyCobotLanguage::language()
{
    // begin
    //EEPROM.begin(EEPROM_SIZE);

    if (hasSeletecd()) {
        return language_val;
    } else {
        return selectLanguage();
    }
}


bool MyCobotLanguage::hasSeletecd()
{
#if defined Mycobot_M5
    language_val = EEPROM.read(Lan_Add);

    //Serial.print("seletec language is : ");
    //Serial.println(language_val);
#endif
    if (language_val != 0) {
        return true;
    } else { // = 0
        return false;
    }
}

int MyCobotLanguage::selectLanguage()
{

    // display lcd text
#if defined Mycobot_M5
    M5.Lcd.drawString("  语言选择", 20, 40, 1);
    M5.Lcd.drawString("  Language", 20, 70, 1);
    M5.Lcd.drawString("English", 60, 190, 1);
    M5.Lcd.drawString("中文", 260, 190, 1);
    M5.update();
#endif
    delay(100);
    // begin to choose
    while (1) {
        // english
#if defined Mycobot_M5
        if (M5.BtnA.wasPressed())
#elif defined Mycobot_Seeed
        if (digitalRead(WIO_5S_DOWN) == LOW)
#endif
        {
            language_val = EN_NO;
            break;
        }
        // chinese
#if defined Mycobot_M5
        if (M5.BtnC.wasPressed())
#elif defined Mycobot_Seeed
        if (digitalRead(WIO_5S_RIGHT) == LOW)
#endif
        {
            language_val = CN_NO;
            break;
        }
#if defined Mycobot_M5
        M5.update();
#endif
        delay(50);
    }

    //Serial.println(language_val);

    // save to eeprom
    setLanguage(language_val);

    delay(50);
    return language_val;

}

void MyCobotLanguage::setLanguage(int lan_val)
{
#if defined Mycobot_M5
    EEPROM.write(Lan_Add, lan_val);
    EEPROM.commit();
#endif
}