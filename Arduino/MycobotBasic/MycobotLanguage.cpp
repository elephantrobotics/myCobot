#include "MycobotLanguage.h"


MycobotLanguage::MycobotLanguage()
{
    

    M5.begin(true, false, true);
    M5.Power.begin();
    delay(100);

    M5.Lcd.setTextSize(1);
    M5.Lcd.setFreeFont(&mycobot_24px); 
    M5.Lcd.setTextDatum(TC_DATUM);

    
}

void MycobotLanguage::clearLanguage()
{
    EEPROM.write(Lan_Add, 0);
    EEPROM.commit();
    delay(100);
}


int MycobotLanguage::language()
{
    // begin
    //EEPROM.begin(EEPROM_SIZE);

    if(hasSeletecd())
    {
        return language_val;
    }
    else
    {
        return selectLanguage();
    }
}


bool MycobotLanguage::hasSeletecd()
{
    language_val = EEPROM.read(Lan_Add);

    //Serial.print("seletec language is : ");
    //Serial.println(language_val);

    if (language_val != 0)
    {
        return true;
    }
    else // = 0 
    {
        return false;
    }
}

int MycobotLanguage::selectLanguage()
{

    // display lcd text
    
    M5.Lcd.drawString("  语言选择", 20, 40, 1);
    M5.Lcd.drawString("  Language", 20, 70, 1);
    M5.Lcd.drawString("English", 60, 190, 1);
    M5.Lcd.drawString("中文", 260, 190, 1);
    M5.update();
    delay(100);    

    // begin to choose
    while(1)
    {
        // english
        if (M5.BtnA.wasPressed()) 
        {
            language_val = EN_NO;
            break;
        }
        // chinese
        if (M5.BtnC.wasPressed()) 
        {
            language_val = CN_NO;     
            break;  
        }
        M5.update();   
        delay(50);
    }

    //Serial.println(language_val);

    // save to eeprom
    setLanguage(language_val);
    
    delay(50);
    return language_val;

}

void MycobotLanguage::setLanguage(int lan_val)
{
    EEPROM.write(Lan_Add, lan_val);
    EEPROM.commit();
}