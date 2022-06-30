#ifndef __M5LiteDebug_H__
#define __M5LiteDebug_H__

const String _sigInName[256] = {
  "SPICLK_IN_IDX",
  "SPIQ_IN_IDX",
  "SPID_IN_IDX",
  "SPIHD_IN_IDX",
  "SPIWP_IN_IDX",
  "SPICS0_IN_IDX",
  "SPICS1_IN_IDX",
  "SPICS2_IN_IDX",
  "HSPICLK_IN_IDX",
  "HSPIQ_IN_IDX",
  "HSPID_IN_IDX",
  "HSPICS0_IN_IDX",
  "HSPIHD_IN_IDX",
  "HSPIWP_IN_IDX",
  "U0RXD_IN_IDX",
  "U0CTS_IN_IDX",
  "U0DSR_IN_IDX",
  "U1RXD_IN_IDX",
  "U1CTS_IN_IDX",
  "I2CM_SCL_O_IDX",
  "I2CM_SDA_I_IDX",
  "EXT_I2C_SCL_O_IDX",
  "EXT_I2C_SDA_I_IDX",
  "I2S0O_BCK_IN_IDX",
  "I2S1O_BCK_IN_IDX",
  "I2S0O_WS_IN_IDX",
  "I2S1O_WS_IN_IDX",
  "I2S0I_BCK_IN_IDX",
  "I2S0I_WS_IN_IDX",
  "I2CEXT0_SCL_IN_IDX",
  "I2CEXT0_SDA_IN_IDX",
  "PWM0_SYNC0_IN_IDX",
  "PWM0_SYNC1_IN_IDX",
  "PWM0_SYNC2_IN_IDX",
  "PWM0_F0_IN_IDX",
  "PWM0_F1_IN_IDX",
  "PWM0_F2_IN_IDX",
  "GPIO_BT_ACTIVE_IDX",
  "GPIO_BT_PRIORITY_IDX",
  "PCNT_SIG_CH0_IN0_IDX",
  "PCNT_SIG_CH1_IN0_IDX",
  "PCNT_CTRL_CH0_IN0_IDX",
  "PCNT_CTRL_CH1_IN0_IDX",
  "PCNT_SIG_CH0_IN1_IDX",
  "PCNT_SIG_CH1_IN1_IDX",
  "PCNT_CTRL_CH0_IN1_IDX",
  "PCNT_CTRL_CH1_IN1_IDX",
  "PCNT_SIG_CH0_IN2_IDX",
  "PCNT_SIG_CH1_IN2_IDX",
  "PCNT_CTRL_CH0_IN2_IDX",
  "PCNT_CTRL_CH1_IN2_IDX",
  "PCNT_SIG_CH0_IN3_IDX",
  "PCNT_SIG_CH1_IN3_IDX",
  "PCNT_CTRL_CH0_IN3_IDX",
  "PCNT_CTRL_CH1_IN3_IDX",
  "PCNT_SIG_CH0_IN4_IDX",
  "PCNT_SIG_CH1_IN4_IDX",
  "PCNT_CTRL_CH0_IN4_IDX",
  "PCNT_CTRL_CH1_IN4_IDX",
  "BB_DIAG18_IDX",
  "BB_DIAG19_IDX",
  "HSPICS1_IN_IDX",
  "HSPICS2_IN_IDX",
  "VSPICLK_IN_IDX",
  "VSPIQ_IN_IDX",
  "VSPID_IN_IDX",
  "VSPIHD_IN_IDX",
  "VSPIWP_IN_IDX",
  "VSPICS0_IN_IDX",
  "VSPICS1_IN_IDX",
  "VSPICS2_IN_IDX",
  "PCNT_SIG_CH0_IN5_IDX",
  "PCNT_SIG_CH1_IN5_IDX",
  "PCNT_CTRL_CH0_IN5_IDX",
  "PCNT_CTRL_CH1_IN5_IDX",
  "PCNT_SIG_CH0_IN6_IDX",
  "PCNT_SIG_CH1_IN6_IDX",
  "PCNT_CTRL_CH0_IN6_IDX",
  "PCNT_CTRL_CH1_IN6_IDX",
  "PCNT_SIG_CH0_IN7_IDX",
  "PCNT_SIG_CH1_IN7_IDX",
  "PCNT_CTRL_CH0_IN7_IDX",
  "PCNT_CTRL_CH1_IN7_IDX",
  "RMT_SIG_IN0_IDX",
  "RMT_SIG_IN1_IDX",
  "RMT_SIG_IN2_IDX",
  "RMT_SIG_IN3_IDX",
  "RMT_SIG_IN4_IDX",
  "RMT_SIG_IN5_IDX",
  "RMT_SIG_IN6_IDX",
  "RMT_SIG_IN7_IDX",
  "RMT_SIG_OUT4_IDX",
  "RMT_SIG_OUT5_IDX",
  "EXT_ADC_START_IDX",
  "CAN_RX_IDX",
  "I2CEXT1_SCL_IN_IDX",
  "I2CEXT1_SDA_IN_IDX",
  "HOST_CCMD_OD_PULLUP_EN_N_IDX",
  "HOST_RST_N_1_IDX",
  "HOST_RST_N_2_IDX",
  "HOST_CARD_WRITE_PRT_2_IDX",
  "HOST_CARD_INT_N_1_IDX",
  "HOST_CARD_INT_N_2_IDX",
  "PWM1_SYNC0_IN_IDX",
  "PWM1_SYNC1_IN_IDX",
  "PWM1_SYNC2_IN_IDX",
  "PWM1_F0_IN_IDX",
  "PWM1_F1_IN_IDX",
  "PWM1_F2_IN_IDX",
  "PWM0_CAP0_IN_IDX",
  "PWM0_CAP1_IN_IDX",
  "PWM0_CAP2_IN_IDX",
  "PWM1_CAP0_IN_IDX",
  "PWM1_CAP1_IN_IDX",
  "PWM1_CAP2_IN_IDX",
  "PWM2_FLTA_IDX",
  "PWM2_FLTB_IDX",
  "PWM2_CAP1_IN_IDX",
  "PWM2_CAP2_IN_IDX",
  "PWM2_CAP3_IN_IDX",
  "PWM3_FLTA_IDX",
  "PWM3_FLTB_IDX",
  "PWM3_CAP1_IN_IDX",
  "PWM3_CAP2_IN_IDX",
  "PWM3_CAP3_IN_IDX",
  "CAN_CLKOUT_IDX",
  "126",
  "127",
  "SPID4_IN_IDX",
  "SPID5_IN_IDX",
  "SPID6_IN_IDX",
  "SPID7_IN_IDX",
  "HSPID4_IN_IDX",
  "HSPID5_IN_IDX",
  "HSPID6_IN_IDX",
  "HSPID7_IN_IDX",
  "VSPID4_IN_IDX",
  "VSPID5_IN_IDX",
  "VSPID6_IN_IDX",
  "VSPID7_IN_IDX",
  "I2S0I_DATA_IN0_IDX",
  "I2S0I_DATA_IN1_IDX",
  "I2S0I_DATA_IN2_IDX",
  "I2S0I_DATA_IN3_IDX",
  "I2S0I_DATA_IN4_IDX",
  "I2S0I_DATA_IN5_IDX",
  "I2S0I_DATA_IN6_IDX",
  "I2S0I_DATA_IN7_IDX",
  "I2S0I_DATA_IN8_IDX",
  "I2S0I_DATA_IN9_IDX",
  "I2S0I_DATA_IN10_IDX",
  "I2S0I_DATA_IN11_IDX",
  "I2S0I_DATA_IN12_IDX",
  "I2S0I_DATA_IN13_IDX",
  "I2S0I_DATA_IN14_IDX",
  "I2S0I_DATA_IN15_IDX",
  "I2S0O_DATA_OUT16_IDX",
  "I2S0O_DATA_OUT17_IDX",
  "I2S0O_DATA_OUT18_IDX",
  "I2S0O_DATA_OUT19_IDX",
  "I2S0O_DATA_OUT20_IDX",
  "I2S0O_DATA_OUT21_IDX",
  "I2S0O_DATA_OUT22_IDX",
  "I2S0O_DATA_OUT23_IDX",
  "I2S1I_BCK_IN_IDX",
  "I2S1I_WS_IN_IDX",
  "I2S1I_DATA_IN0_IDX",
  "I2S1I_DATA_IN1_IDX",
  "I2S1I_DATA_IN2_IDX",
  "I2S1I_DATA_IN3_IDX",
  "I2S1I_DATA_IN4_IDX",
  "I2S1I_DATA_IN5_IDX",
  "I2S1I_DATA_IN6_IDX",
  "I2S1I_DATA_IN7_IDX",
  "I2S1I_DATA_IN8_IDX",
  "I2S1I_DATA_IN9_IDX",
  "I2S1I_DATA_IN10_IDX",
  "I2S1I_DATA_IN11_IDX",
  "I2S1I_DATA_IN12_IDX",
  "I2S1I_DATA_IN13_IDX",
  "I2S1I_DATA_IN14_IDX",
  "I2S1I_DATA_IN15_IDX",
  "I2S1O_DATA_OUT16_IDX",
  "I2S1O_DATA_OUT17_IDX",
  "I2S1O_DATA_OUT18_IDX",
  "I2S1O_DATA_OUT19_IDX",
  "I2S1O_DATA_OUT20_IDX",
  "I2S1O_DATA_OUT21_IDX",
  "I2S1O_DATA_OUT22_IDX",
  "I2S1O_DATA_OUT23_IDX",
  "I2S0I_H_SYNC_IDX",
  "I2S0I_V_SYNC_IDX",
  "I2S0I_H_ENABLE_IDX",
  "I2S1I_H_SYNC_IDX",
  "I2S1I_V_SYNC_IDX",
  "I2S1I_H_ENABLE_IDX",
  "PWM3_OUT4H_IDX",
  "PWM3_OUT4L_IDX",
  "U2RXD_IN_IDX",
  "U2CTS_IN_IDX",
  "EMAC_MDC_I_IDX",
  "EMAC_MDI_I_IDX",
  "EMAC_CRS_I_IDX",
  "EMAC_COL_I_IDX",
  "PCMFSYNC_IN_IDX",
  "PCMCLK_IN_IDX",
  "PCMDIN_IDX",
  "BLE_AUDIO0_IRQ_IDX",
  "BLE_AUDIO1_IRQ_IDX",
  "BLE_AUDIO2_IRQ_IDX",
  "PCMFSYNC_OUT_IDX",
  "PCMCLK_OUT_IDX",
  "PCMDOUT_IDX",
  "BLE_AUDIO_SYNC0_P_IDX",
  "BLE_AUDIO_SYNC1_P_IDX",
  "BLE_AUDIO_SYNC2_P_IDX",
  "ANT_SEL0_IDX",
  "ANT_SEL1_IDX",
  "ANT_SEL2_IDX",
  "ANT_SEL3_IDX",
  "ANT_SEL4_IDX",
  "ANT_SEL5_IDX",
  "ANT_SEL6_IDX",
  "ANT_SEL7_IDX",
  "SIG_IN_FUNC224_IDX",
  "SIG_IN_FUNC225_IDX",
  "SIG_IN_FUNC226_IDX",
  "SIG_IN_FUNC227_IDX",
  "SIG_IN_FUNC228_IDX",
  "229",
  "230",
  "231",
  "232",
  "233",
  "234",
  "235",
  "236",
  "237",
  "238",
  "239",
  "240",
  "241",
  "242",
  "243",
  "244",
  "245",
  "246",
  "247",
  "248",
  "249",
  "250",
  "251",
  "252",
  "253",
  "254",
  "255",
};

const String _sigOutName[256] = {
  "SPICLK_OUT_IDX",
  "SPIQ_OUT_IDX",
  "SPID_OUT_IDX",
  "SPIHD_OUT_IDX",
  "SPIWP_OUT_IDX",
  "SPICS0_OUT_IDX",
  "SPICS1_OUT_IDX",
  "SPICS2_OUT_IDX",
  "HSPICLK_OUT_IDX",
  "HSPIQ_OUT_IDX",
  "HSPID_OUT_IDX",
  "HSPICS0_OUT_IDX",
  "HSPIHD_OUT_IDX",
  "HSPIWP_OUT_IDX",
  "U0TXD_OUT_IDX",
  "U0RTS_OUT_IDX",
  "U0DTR_OUT_IDX",
  "U1TXD_OUT_IDX",
  "U1RTS_OUT_IDX",
  "I2CM_SCL_O_IDX",
  "I2CM_SDA_O_IDX",
  "EXT_I2C_SCL_O_IDX",
  "EXT_I2C_SDA_O_IDX",
  "I2S0O_BCK_OUT_IDX",
  "I2S1O_BCK_OUT_IDX",
  "I2S0O_WS_OUT_IDX",
  "I2S1O_WS_OUT_IDX",
  "I2S0I_BCK_OUT_IDX",
  "I2S0I_WS_OUT_IDX",
  "I2CEXT0_SCL_OUT_IDX",
  "I2CEXT0_SDA_OUT_IDX",
  "SDIO_TOHOST_INT_OUT_IDX",
  "PWM0_OUT0A_IDX",
  "PWM0_OUT0B_IDX",
  "PWM0_OUT1A_IDX",
  "PWM0_OUT1B_IDX",
  "PWM0_OUT2A_IDX",
  "GPIO_BT_ACTIVE_IDX",
  "PWM0_OUT2B_IDX",
  "GPIO_BT_PRIORITY_IDX",
  "GPIO_WLAN_ACTIVE_IDX",
  "BB_DIAG0_IDX",
  "BB_DIAG1_IDX",
  "BB_DIAG2_IDX",
  "BB_DIAG3_IDX",
  "BB_DIAG4_IDX",
  "BB_DIAG5_IDX",
  "BB_DIAG6_IDX",
  "BB_DIAG7_IDX",
  "BB_DIAG8_IDX",
  "BB_DIAG9_IDX",
  "BB_DIAG10_IDX",
  "BB_DIAG11_IDX",
  "BB_DIAG12_IDX",
  "BB_DIAG13_IDX",
  "BB_DIAG14_IDX",
  "BB_DIAG15_IDX",
  "BB_DIAG16_IDX",
  "BB_DIAG17_IDX",
  "BB_DIAG18_IDX",
  "BB_DIAG19_IDX",
  "HSPICS1_OUT_IDX",
  "HSPICS2_OUT_IDX",
  "VSPICLK_OUT_IDX",
  "VSPIQ_OUT_IDX",
  "VSPID_OUT_IDX",
  "VSPIHD_OUT_IDX",
  "VSPIWP_OUT_IDX",
  "VSPICS0_OUT_IDX",
  "VSPICS1_OUT_IDX",
  "VSPICS2_OUT_IDX",
  "LEDC_HS_SIG_OUT0_IDX",
  "LEDC_HS_SIG_OUT1_IDX",
  "LEDC_HS_SIG_OUT2_IDX",
  "LEDC_HS_SIG_OUT3_IDX",
  "LEDC_HS_SIG_OUT4_IDX",
  "LEDC_HS_SIG_OUT5_IDX",
  "LEDC_HS_SIG_OUT6_IDX",
  "LEDC_HS_SIG_OUT7_IDX",
  "LEDC_LS_SIG_OUT0_IDX",
  "LEDC_LS_SIG_OUT1_IDX",
  "LEDC_LS_SIG_OUT2_IDX",
  "LEDC_LS_SIG_OUT3_IDX",
  "LEDC_LS_SIG_OUT4_IDX",
  "LEDC_LS_SIG_OUT5_IDX",
  "LEDC_LS_SIG_OUT6_IDX",
  "LEDC_LS_SIG_OUT7_IDX",
  "RMT_SIG_OUT0_IDX",
  "RMT_SIG_OUT1_IDX",
  "RMT_SIG_OUT2_IDX",
  "RMT_SIG_OUT3_IDX",
  "RMT_SIG_OUT4_IDX",
  "RMT_SIG_OUT5_IDX",
  "RMT_SIG_OUT6_IDX",
  "RMT_SIG_OUT7_IDX",
  "I2CEXT1_SCL_OUT_IDX",
  "I2CEXT1_SDA_OUT_IDX",
  "HOST_CCMD_OD_PULLUP_EN_N_IDX",
  "HOST_RST_N_1_IDX",
  "HOST_RST_N_2_IDX",
  "GPIO_SD0_OUT_IDX",
  "GPIO_SD1_OUT_IDX",
  "GPIO_SD2_OUT_IDX",
  "GPIO_SD3_OUT_IDX",
  "GPIO_SD4_OUT_IDX",
  "GPIO_SD5_OUT_IDX",
  "GPIO_SD6_OUT_IDX",
  "GPIO_SD7_OUT_IDX",
  "PWM1_OUT0A_IDX",
  "PWM1_OUT0B_IDX",
  "PWM1_OUT1A_IDX",
  "PWM1_OUT1B_IDX",
  "PWM1_OUT2A_IDX",
  "PWM1_OUT2B_IDX",
  "PWM2_OUT1H_IDX",
  "PWM2_OUT1L_IDX",
  "PWM2_OUT2H_IDX",
  "PWM2_OUT2L_IDX",
  "PWM2_OUT3H_IDX",
  "PWM2_OUT3L_IDX",
  "PWM2_OUT4H_IDX",
  "PWM2_OUT4L_IDX",
  "PWM3_CAP1_IN_IDX",
  "CAN_TX_IDX",
  "CAN_BUS_OFF_ON_IDX",
  "CAN_CLKOUT_IDX",
  "126",
  "127",
  "SPID4_OUT_IDX",
  "SPID5_OUT_IDX",
  "SPID6_OUT_IDX",
  "SPID7_OUT_IDX",
  "HSPID4_OUT_IDX",
  "HSPID5_OUT_IDX",
  "HSPID6_OUT_IDX",
  "HSPID7_OUT_IDX",
  "VSPID4_OUT_IDX",
  "VSPID5_OUT_IDX",
  "VSPID6_OUT_IDX",
  "VSPID7_OUT_IDX",
  "I2S0O_DATA_OUT0_IDX",
  "I2S0O_DATA_OUT1_IDX",
  "I2S0O_DATA_OUT2_IDX",
  "I2S0O_DATA_OUT3_IDX",
  "I2S0O_DATA_OUT4_IDX",
  "I2S0O_DATA_OUT5_IDX",
  "I2S0O_DATA_OUT6_IDX",
  "I2S0O_DATA_OUT7_IDX",
  "I2S0O_DATA_OUT8_IDX",
  "I2S0O_DATA_OUT9_IDX",
  "I2S0O_DATA_OUT10_IDX",
  "I2S0O_DATA_OUT11_IDX",
  "I2S0O_DATA_OUT12_IDX",
  "I2S0O_DATA_OUT13_IDX",
  "I2S0O_DATA_OUT14_IDX",
  "I2S0O_DATA_OUT15_IDX",
  "I2S0O_DATA_OUT16_IDX",
  "I2S0O_DATA_OUT17_IDX",
  "I2S0O_DATA_OUT18_IDX",
  "I2S0O_DATA_OUT19_IDX",
  "I2S0O_DATA_OUT20_IDX",
  "I2S0O_DATA_OUT21_IDX",
  "I2S0O_DATA_OUT22_IDX",
  "I2S0O_DATA_OUT23_IDX",
  "I2S1I_BCK_OUT_IDX",
  "I2S1I_WS_OUT_IDX",
  "I2S1O_DATA_OUT0_IDX",
  "I2S1O_DATA_OUT1_IDX",
  "I2S1O_DATA_OUT2_IDX",
  "I2S1O_DATA_OUT3_IDX",
  "I2S1O_DATA_OUT4_IDX",
  "I2S1O_DATA_OUT5_IDX",
  "I2S1O_DATA_OUT6_IDX",
  "I2S1O_DATA_OUT7_IDX",
  "I2S1O_DATA_OUT8_IDX",
  "I2S1O_DATA_OUT9_IDX",
  "I2S1O_DATA_OUT10_IDX",
  "I2S1O_DATA_OUT11_IDX",
  "I2S1O_DATA_OUT12_IDX",
  "I2S1O_DATA_OUT13_IDX",
  "I2S1O_DATA_OUT14_IDX",
  "I2S1O_DATA_OUT15_IDX",
  "I2S1O_DATA_OUT16_IDX",
  "I2S1O_DATA_OUT17_IDX",
  "I2S1O_DATA_OUT18_IDX",
  "I2S1O_DATA_OUT19_IDX",
  "I2S1O_DATA_OUT20_IDX",
  "I2S1O_DATA_OUT21_IDX",
  "I2S1O_DATA_OUT22_IDX",
  "I2S1O_DATA_OUT23_IDX",
  "PWM3_OUT1H_IDX",
  "PWM3_OUT1L_IDX",
  "PWM3_OUT2H_IDX",
  "PWM3_OUT2L_IDX",
  "PWM3_OUT3H_IDX",
  "PWM3_OUT3L_IDX",
  "PWM3_OUT4H_IDX",
  "PWM3_OUT4L_IDX",
  "U2TXD_OUT_IDX",
  "U2RTS_OUT_IDX",
  "EMAC_MDC_O_IDX",
  "EMAC_MDO_O_IDX",
  "EMAC_CRS_O_IDX",
  "EMAC_COL_O_IDX",
  "BT_AUDIO0_IRQ_IDX",
  "BT_AUDIO1_IRQ_IDX",
  "BT_AUDIO2_IRQ_IDX",
  "BLE_AUDIO0_IRQ_IDX",
  "BLE_AUDIO1_IRQ_IDX",
  "BLE_AUDIO2_IRQ_IDX",
  "PCMFSYNC_OUT_IDX",
  "PCMCLK_OUT_IDX",
  "PCMDOUT_IDX",
  "BLE_AUDIO_SYNC0_P_IDX",
  "BLE_AUDIO_SYNC1_P_IDX",
  "BLE_AUDIO_SYNC2_P_IDX",
  "ANT_SEL0_IDX",
  "ANT_SEL1_IDX",
  "ANT_SEL2_IDX",
  "ANT_SEL3_IDX",
  "ANT_SEL4_IDX",
  "ANT_SEL5_IDX",
  "ANT_SEL6_IDX",
  "ANT_SEL7_IDX",
  "224",
  "225",
  "226",
  "227",
  "228",
  "229",
  "230",
  "231",
  "232",
  "233",
  "234",
  "235",
  "236",
  "237",
  "238",
  "239",
  "240",
  "241",
  "242",
  "243",
  "244",
  "245",
  "246",
  "247",
  "248",
  "249",
  "250",
  "251",
  "252",
  "253",
  "254",
  "255",
};

class M5LiteDebug {
  public:
    TFT_eSPI *_Lcd;
    M5LiteAXP192 *_Axp;
    M5LiteButton *_BtnA;
    M5LiteButton *_BtnB;
    M5LiteButton *_BtnC;
    M5LiteRTC *_Rtc;
    M5LiteIMU *_Imu;
    M5LiteMPU6886 *_Mpu6886;
    M5LiteSH200Q *_Sh200Q;
    M5LiteCommUtil *_I2C;
    M5LitePower *_Power;
    M5LiteSpeaker *_Beep;
    M5LiteLED *_dis;
    M5LiteTouch *_Touch;
    Preferences *_preferences;

    void dispHelp(void) {
      Serial.println("===============================================================");
      Serial.println("M5Lite Debug Command List");
      Serial.println("===============================================================");
      Serial.println(" ?                                 : This print");
      Serial.println(" INFO                              : Print Info");
      Serial.println(" AXP192                            : AXP192 Info");
      Serial.println(" IMU                               : IMU Info");
      Serial.println(" RTC                               : RTC Info");
      Serial.println(" MEM                               : Memory Info");
      Serial.println(" GPIO                              : GPIO Info");
      Serial.println(" I2C                               : I2C Scan");
#ifdef WiFi_h
      Serial.println(" WIFI [SSID] [KEY]                 : Connect Wi-Fi(default Last SSID & Key)");
      Serial.println(" NTP [SERVER]                      : Sync NTP Server(default pool.ntp.org)");
#endif
      Serial.println(" SD [DIR]                          : SD Storage");
      Serial.println(" SPIFFS [DIR]                      : SPIFFS Storage");
      Serial.println(" FORMAT [NVS|SPIFFS]               : Format Flash");
      Serial.println(" SCREENSHOT [SD|SPIFFS] [FILENAME] : Screenshot 16bitBMP(default SD)");
      Serial.println(" RESET                             : Reset ESP32");
    }

    void dispAxp192(void) {
      // AXP192
      if (_Axp->enable) {
        Serial.printf("===============================================================\n");
        Serial.printf("AXP192\n");
        Serial.printf("===============================================================\n");
        Serial.printf("Battery\n");
        Serial.printf(" Temp :%6.1f C\n", _Axp->GetTempInAXP192());    // AXP192 Internal temperature
        Serial.printf(" V    :%6.3f V\n", _Axp->GetBatVoltage());    // Battery Voltage(3.0V-4.2V)
        Serial.printf(" I    :%6.1f mA\n", _Axp->GetBatCurrent());   // Battery Current(+:charge, -:decharge)

        Serial.printf("ASP(ESP32)\n");
        Serial.printf(" V    :%6.3f V\n", _Axp->GetAPSVoltage());    // ESP32 Voltage

        Serial.printf("VBus(USB)\n");
        Serial.printf(" V    :%6.3f V\n", _Axp->GetVBusVoltage());   // USB Voltage
        Serial.printf(" I    :%6.1f mA\n", _Axp->GetVBusCurrent());  // USB Current

        Serial.printf("VIN(5V-In)\n");
        Serial.printf(" V    :%6.3f V\n", _Axp->GetVinVoltage());    // 5V IN Voltage
        Serial.printf(" I    :%6.1f mA\n", _Axp->GetVinCurrent());   // 5V IN Current
      } else {
        Serial.printf("AXP192      : (NONE)\n");
      }
    }

    void dispImu(void) {
      Serial.printf("===============================================================\n");
      Serial.printf("IMU\n");
      Serial.printf("===============================================================\n");
      if (_Imu->imuType == M5LiteIMU::IMU_UNKNOWN) {
        Serial.println("(NONE)");
      } else if (_Imu->imuType == M5LiteIMU::IMU_SH200Q) {
        Serial.println("SH200Q(6-AXIS)");
        float ax, ay, az, gx, gy, gz , t;
        _Imu->getAccelData(&ax, &ay, &az);
        _Imu->getGyroData(&gx, &gy, &gz);
        _Imu->getTempData(&t);
        Serial.printf(" ACCEL\n");
        Serial.printf("  X    :%11.6f\n", ax);
        Serial.printf("  Y    :%11.6f\n", ay);
        Serial.printf("  Z    :%11.6f\n", az);
        Serial.printf(" GYRO\n");
        Serial.printf("  X    :%11.6f\n", gx);
        Serial.printf("  Y    :%11.6f\n", gy);
        Serial.printf("  Z    :%11.6f\n", gz);
        Serial.printf(" TEMP\n");
        Serial.printf("  T    :%11.6f C\n", t);
      } else if (_Imu->imuType == M5LiteIMU::IMU_MPU6886) {
        Serial.println("MPU6886(6-AXIS)");
        float ax, ay, az, gx, gy, gz , t;
        _Imu->getAccelData(&ax, &ay, &az);
        _Imu->getGyroData(&gx, &gy, &gz);
        _Imu->getTempData(&t);
        Serial.printf(" ACCEL\n");
        Serial.printf("  X    :%11.6f\n", ax);
        Serial.printf("  Y    :%11.6f\n", ay);
        Serial.printf("  Z    :%11.6f\n", az);
        Serial.printf(" GYRO\n");
        Serial.printf("  X    :%11.6f\n", gx);
        Serial.printf("  Y    :%11.6f\n", gy);
        Serial.printf("  Z    :%11.6f\n", gz);
        Serial.printf(" TEMP\n");
        Serial.printf("  T    :%11.6f C\n", t);
      } else if (_Imu->imuType == M5LiteIMU::IMU_BMA423) {
        Serial.println("BMA423(3-AXIS:ACCEL)");
        float ax, ay, az;
        _Imu->getAccelData(&ax, &ay, &az);
        Serial.printf(" ACCEL\n");
        Serial.printf("  X    :%11.6f\n", ax);
        Serial.printf("  Y    :%11.6f\n", ay);
        Serial.printf("  Z    :%11.6f\n", az);
      }
    }

    void dispRtc(void) {
      Serial.printf("===============================================================\n");
      Serial.printf("RTC\n");
      Serial.printf("===============================================================\n");
      if (_Rtc->enable) {
        RTC_TimeTypeDef RTC_TimeStruct;
        RTC_DateTypeDef RTC_DateStruct;
        _Rtc->GetTime(&RTC_TimeStruct);
        _Rtc->GetData(&RTC_DateStruct);
        Serial.printf("%04d-%02d-%02d ", RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date);
        Serial.printf("%02d:%02d:%02d\n", RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);
      } else {
        Serial.println("(NONE)");
      }
    }

    void dispMemory() {
      Serial.printf("===============================================================\n");
      Serial.printf("Memory Info\n");
      Serial.printf("===============================================================\n");

      Serial.printf("esp_get_free_heap_size()                              : %6d\n", esp_get_free_heap_size() );
      Serial.printf("esp_get_minimum_free_heap_size()                      : %6d\n", esp_get_minimum_free_heap_size() );

      //xPortGetFreeHeapSize()（データメモリ）ヒープの空きバイト数を返すFreeRTOS関数です。これはを呼び出すのと同じheap_caps_get_free_size(MALLOC_CAP_8BIT)です。
      Serial.printf("xPortGetFreeHeapSize()                                : %6d\n", xPortGetFreeHeapSize() );

      //xPortGetMinimumEverFreeHeapSize()また、関連heap_caps_get_minimum_free_size()するものを使用して、ブート以降のヒープの「最低水準点」を追跡できます。
      Serial.printf("xPortGetMinimumEverFreeHeapSize()                     : %6d\n", xPortGetMinimumEverFreeHeapSize() );

      //heap_caps_get_free_size() さまざまなメモリ機能の現在の空きメモリを返すためにも使用できます。
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_EXEC)              : %6d\n", heap_caps_get_free_size(MALLOC_CAP_EXEC) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_32BIT)             : %6d\n", heap_caps_get_free_size(MALLOC_CAP_32BIT) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_8BIT)              : %6d\n", heap_caps_get_free_size(MALLOC_CAP_8BIT) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_DMA)               : %6d\n", heap_caps_get_free_size(MALLOC_CAP_DMA) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_PID2)              : %6d\n", heap_caps_get_free_size(MALLOC_CAP_PID2) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_PID3)              : %6d\n", heap_caps_get_free_size(MALLOC_CAP_PID3) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_PID3)              : %6d\n", heap_caps_get_free_size(MALLOC_CAP_PID4) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_PID4)              : %6d\n", heap_caps_get_free_size(MALLOC_CAP_PID5) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_PID5)              : %6d\n", heap_caps_get_free_size(MALLOC_CAP_PID6) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_PID6)              : %6d\n", heap_caps_get_free_size(MALLOC_CAP_PID7) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_PID7)              : %6d\n", heap_caps_get_free_size(MALLOC_CAP_PID3) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_SPIRAM)            : %6d\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_INTERNAL)          : %6d\n", heap_caps_get_free_size(MALLOC_CAP_INTERNAL) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_DEFAULT)           : %6d\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_INVALID)           : %6d\n", heap_caps_get_free_size(MALLOC_CAP_INVALID) );

      //heap_caps_get_largest_free_block()ヒープ内の最大の空きブロックを返すために使用できます。これは、現在可能な最大の単一割り当てです。この値を追跡し、合計空きヒープと比較すると、ヒープの断片化を検出できます。
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_EXEC)     : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_EXEC) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_32BIT)    : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_32BIT) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_8BIT)     : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_DMA)      : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_DMA) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_PID2)     : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_PID2) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_PID3)     : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_PID3) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_PID3)     : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_PID4) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_PID4)     : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_PID5) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_PID5)     : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_PID6) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_PID6)     : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_PID7) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_PID7)     : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_PID3) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM)   : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL) : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_DEFAULT)  : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_DEFAULT) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_INVALID)  : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_INVALID) );

      //heap_caps_get_minimum_free_size()指定された機能を持つすべての領域の合計最小空きメモリを取得します。
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_EXEC)      : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_EXEC) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_32BIT)     : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_32BIT) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_8BIT)      : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_8BIT) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_DMA)       : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_DMA) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_PID2)      : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_PID2) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_PID3)      : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_PID3) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_PID3)      : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_PID4) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_PID4)      : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_PID5) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_PID5)      : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_PID6) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_PID6)      : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_PID7) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_PID7)      : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_PID3) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_SPIRAM)    : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_SPIRAM) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_INTERNAL)  : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_INTERNAL) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_DEFAULT)   : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_DEFAULT) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_INVALID)   : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_INVALID) );
    }

    void dispInfo(void) {
      Serial.printf("===============================================================\n");
      Serial.printf("M5Lite Info\n");
      Serial.printf("===============================================================\n");

      // Mac Address
      uint8_t mac[6];
      esp_read_mac(mac, ESP_MAC_WIFI_STA);
      Serial.printf("Mac Address : %02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

#ifdef WiFi_h
      // IP Address
      Serial.printf("IP Address  : ");
      Serial.println(WiFi.localIP());
#endif

      // Board
      Serial.printf("Board       : ");
      if (_Imu->board == lgfx::board_M5Stack) {
        // M5Stack
        Serial.println("M5Stack");
      } else if (_Imu->board == lgfx::board_M5StackCore2) {
        // M5Stack Core2
        Serial.println("M5Stack Core2");
      } else if (_Imu->board == lgfx::board_M5StickC) {
        // M5StickC
        Serial.println("M5StickC");
      } else if (_Imu->board == lgfx::board_M5StickCPlus) {
        // M5StickC Plus
        Serial.println("M5StickC Plus");
      } else if (_Imu->board == lgfx::board_TTGO_TWatch) {
        // TTGO T-Watch
        Serial.println("LILYGO TTGO T-Watch");
      } else if (_Imu->board == lgfx::board_unknown) {
        // ATOM
        Serial.println("M5Stack ATOM");
      }

      // LCD
      int width = _Lcd->width();
      int height = _Lcd->height();
      if (0 < width) {
        Serial.printf("LCD         : Width:%d, Height:%d\n", width, height);
      } else {
        Serial.printf("LCD         : (NONE)\n");
      }

      // RTC
      dispRtc();
    }

#ifdef WiFi_h
    void connectWiFi(String ssid, String key) {
      Serial.printf("===============================================================\n");
      Serial.printf("Wi-Fi Connect\n");
      Serial.printf("===============================================================\n");
      if (ssid == "" && key == "") {
        WiFi.begin();
      } else {
        WiFi.begin(ssid.c_str(), key.c_str());
      }
      int i;
      for (i = 0; i < 50 ; i++) {
        if (WiFi.status() == WL_CONNECTED) {
          Serial.println("Connect");
          Serial.printf(" IP Address  : ");
          Serial.println(WiFi.localIP());
          break;
        } else {
          Serial.print(".");
        }

        delay(200);
      }

      if (i == 50) {
        Serial.println("TimeOut");
      }
    }

    void syncNTP(String server) {
      Serial.printf("===============================================================\n");
      Serial.printf("NTP Sync\n");
      Serial.printf("===============================================================\n");
      if (WiFi.status() == WL_CONNECTED) {
        String ntpServer;
        // Set ntp time to local
        if (server != "") {
          configTime(9 * 3600, 0, server.c_str());
          ntpServer = server;
        } else {
          configTime(9 * 3600, 0, "pool.ntp.org");
          ntpServer = "pool.ntp.org";
        }

        Serial.print("NTP         : ");
        Serial.println(ntpServer);

        // Get local time
        struct tm timeInfo;
        if (getLocalTime(&timeInfo)) {
          // Set RTC time
          RTC_TimeTypeDef TimeStruct;
          TimeStruct.Hours   = timeInfo.tm_hour;
          TimeStruct.Minutes = timeInfo.tm_min;
          TimeStruct.Seconds = timeInfo.tm_sec;
          _Rtc->SetTime(&TimeStruct);

          RTC_DateTypeDef DateStruct;
          DateStruct.WeekDay = timeInfo.tm_wday;
          DateStruct.Month = timeInfo.tm_mon + 1;
          DateStruct.Date = timeInfo.tm_mday;
          DateStruct.Year = timeInfo.tm_year + 1900;
          _Rtc->SetData(&DateStruct);

          Serial.print("Local Time  : ");
          Serial.printf("%04d-%02d-%02d ", DateStruct.Year, DateStruct.Month, DateStruct.Date);
          Serial.printf("%02d:%02d:%02d\n", TimeStruct.Hours, TimeStruct.Minutes, TimeStruct.Seconds);

          if (_Rtc->enable) {
            dispRtc();
          }
        }
      } else {
        Serial.println("Not Wi-Fi Connection");
      }
    }
#endif

    typedef struct {
      bool enable: 1;
      bool pullup: 1;
      bool pulldown: 1;
      bool openDrain: 1;
      bool adc: 1;
      bool output: 1;
      bool level: 1;
    } gpio_info_t;

    gpio_info_t getPinMode(uint8_t pin) {
      gpio_info_t info = {};

      if (!digitalPinIsValid(pin)) {
        return info;
      }

      info.enable = true;

      uint32_t rtc_reg = rtc_gpio_desc[pin].reg;
      if (rtc_reg) {
        uint32_t reg_val = ESP_REG(rtc_reg);

        if (reg_val & rtc_gpio_desc[pin].mux) {
          info.adc = true;
        }

        if (reg_val & rtc_gpio_desc[pin].pullup) {
          info.pullup = true;
        }

        if (reg_val & rtc_gpio_desc[pin].pulldown) {
          info.pulldown = true;
        }
      }

      if (pin > 33) {
      } else if (pin < 32) {
        if (ESP_REG(GPIO_ENABLE_REG) & ((uint32_t)1 << pin)) {
          info.output = true;
        }
      } else {
        if (ESP_REG(GPIO_ENABLE1_REG) & ((uint32_t)1 << (pin - 32))) {
          info.output = true;
        }
      }

      if (ESP_REG(DR_REG_IO_MUX_BASE + esp32_gpioMux[pin].reg) & FUN_PU) {
        info.pullup = true;
      }

      if (ESP_REG(DR_REG_IO_MUX_BASE + esp32_gpioMux[pin].reg) & FUN_PD) {
        info.pulldown = true;
      }

      if (GPIO.pin[pin].val & (1 << GPIO_PIN0_PAD_DRIVER_S)) {
        info.openDrain = true;
      }

      if (pin < 32) {
        if (ESP_REG(GPIO_IN_REG) & ((uint32_t)1 << pin)) {
          info.level = true;
        } else {
          info.level = false;
        }
      } else {
        if (ESP_REG(GPIO_IN1_REG) & ((uint32_t)1 << (pin - 32))) {
          info.level = true;
        } else {
          info.level = false;
        }
      }

      if (34 <= pin) {
        // INPUT Only
        info.pullup = false;
        info.pulldown = false;
        info.openDrain = false;
      }

      return info;
    }

    void getPinMux(String *gpioMap) {
      // INPUT
      for (int i = 0; i < 256; i++) {
        uint32_t reg = GPIO_FUNC0_IN_SEL_CFG_REG + 0x04 * i;
        uint32_t reg_val = ESP_REG(reg);
        if (reg_val & (1 << 7)) {
          int gpio = reg_val & 0b00111111;
          gpioMap[gpio] = "[I]" + _sigInName[i];
        }
      }

      // OUTPUT
      for (int i = 0; i < 40; i++) {
        uint32_t reg = GPIO_FUNC0_OUT_SEL_CFG_REG + 0x04 * i;
        uint32_t reg_val = ESP_REG(reg);
        int func = reg_val & 0b111111111;
        if (func < 256) {
          gpioMap[i] = String("[O]") + _sigOutName[func];
        }
      }
    }

    void dispGpio() {
      String pinMap[40];
      getPinMux(pinMap);

      Serial.println("GPIO LEVEL MODE   ADC PULLUP PULLDOWN OPEN_DRAIN I/O NOTE ");
      Serial.println("-----------------------------------------------------------------------------");
      for (int i = 0; i < 40; i++) {
        gpio_info_t gpioInfo = getPinMode(i);
        if (!gpioInfo.enable) {
          continue;
        }

        Serial.printf("%4d ", i);

        if (gpioInfo.level) {
          Serial.print("HIGH  ");
        } else {
          Serial.print("LOW   ");
        }

        if (gpioInfo.output) {
          Serial.print("OUTPUT ");
        } else {
          Serial.print("INPUT  ");
        }

        if (gpioInfo.adc) {
          Serial.print("ADC ");
        } else {
          Serial.print("    ");
        }

        if (gpioInfo.pullup) {
          Serial.print("PULLUP ");
        } else {
          Serial.print("       ");
        }

        if (gpioInfo.pulldown) {
          Serial.print("PULLDOWN ");
        } else {
          Serial.print("         ");
        }

        if (gpioInfo.openDrain) {
          Serial.print("OPEN_DRAIN ");
        } else {
          Serial.print("           ");
        }

        if (i < 34) {
          Serial.print("I/O ");
        } else {
          Serial.print("I   ");
        }

        Serial.print(pinMap[i]);

        Serial.println();
      }
    }

    void dispI2c() {
      Serial.printf("===============================================================\n");
      Serial.printf("I2C Scan\n");
      Serial.printf("===============================================================\n");

      // Disp I2C
      int i2c0SDA = -1;
      int i2c0SCL = -1;
      int i2c1SDA = -1;
      int i2c1SCL = -1;
      for (int i = 0; i < 40; i++) {
        uint32_t reg = GPIO_FUNC0_OUT_SEL_CFG_REG + 0x04 * i;
        uint32_t reg_val = ESP_REG(reg);
        int func = reg_val & 0b111111111;
        if (func == I2CEXT0_SDA_IN_IDX) {
          i2c0SDA = i;
        } else if (func == I2CEXT0_SCL_IN_IDX) {
          i2c0SCL = i;
        } else if (func == I2CEXT1_SDA_IN_IDX) {
          i2c1SDA = i;
        } else if (func == I2CEXT1_SCL_IN_IDX) {
          i2c1SCL = i;
        }
      }

      if (i2c0SDA != -1 && i2c0SCL != -1) {
        // Wire
        Serial.printf("Wire(I2C0) SDA:%2d SCL:%2d\n", i2c0SDA, i2c0SCL);
        for (byte address = 0; address <= 127; address++) {
          Wire.beginTransmission(address);
          byte error = Wire.endTransmission();
          if (error == 0) {
            Serial.printf("%02X ", address);
          } else {
            Serial.print(".. ");
            if (address % 16 == 15) {
              Serial.println();
            }
          }
          delay(1);
        }
        Serial.println();
      }
      if (i2c1SDA != -1 && i2c1SCL != -1) {
        // Wire1
        Serial.printf("Wire1(I2C1) SDA:%2d SCL:%2d\n", i2c1SDA, i2c1SCL);
        for (byte address = 0; address <= 127; address++) {
          Wire1.beginTransmission(address);
          byte error = Wire1.endTransmission();
          if (error == 0) {
            Serial.printf("%02X ", address);
          } else {
            Serial.print(".. ");
            if (address % 16 == 15) {
              Serial.println();
            }
          }
          delay(1);
        }
        Serial.println();
      }
    }

    void formatStorage(String flash) {
      Serial.printf("===============================================================\n");
      Serial.println("Format Storage");
      Serial.printf("===============================================================\n");
      if (flash == "NVS") {
        Serial.println("Start NVS Format");
        if (nvs_flash_erase() == ESP_OK) {
          Serial.println("NVS clear");
        } else {
          Serial.println("NVS not clear");
        }
        Serial.println("Finish NVS Format");
      } else if (flash == "SPIFFS") {
        Serial.println("Start SPIFFS Format");
        SPIFFS.format();
        Serial.println("Finish SPIFFS Format");
      } else {
        Serial.println("Unknown Storage");
      }
    }

    String fileSizeString(uint32_t val) {
      if (1024 * 1024 * 1024 < val) {
        // GB
        return String(val / 1024.0 / 1024.0 / 1024.0, 2) + String(" GB");
      } else if (1024 * 1024 < val) {
        // MB
        return String(val / 1024.0 / 1024.0, 2) + String(" MB");
      } else if (1024 < val) {
        // KB
        return String(val / 1024.0, 2) + String(" KB");
      } else {
        // B
        return String(val) + String("  B");
      }
    }

    void dispSPIFFS(String command, String path1, String path2) {
      Serial.printf("===============================================================\n");
      Serial.printf("SPIFFS\n");
      Serial.printf("===============================================================\n");
      uint32_t totalBytes = SPIFFS.totalBytes();
      uint32_t usedBytes = SPIFFS.usedBytes();

      String sizeString = fileSizeString(totalBytes);
      Serial.printf("Total Bytes : %10s\n", sizeString.c_str());
      sizeString = fileSizeString(usedBytes);
      Serial.printf("Used Bytes  : %10s\n", sizeString.c_str());

      if (command == "DIR") {
        if (path1 == "") {
          path1 = "/";
        }
        Serial.println();
        Serial.println("[DIR " + path1 + "]");

        File root = SPIFFS.open(path1);
        if (root) {
          File file = root.openNextFile();
          while (file) {
            time_t t = file.getLastWrite();
            struct tm *tm_t = localtime(&t);
            Serial.printf("%04d-%02d-%02d %02d:%02d:%02d ", tm_t->tm_year + 1900, tm_t->tm_mon + 1, tm_t->tm_mday, tm_t->tm_hour, tm_t->tm_min, tm_t->tm_sec);
            if (file.isDirectory()) {
              Serial.print("<DIR>");
              Serial.print("           ");
              Serial.println(file.name());
            } else {
              // ファイル名とファイルサイズを出力
              Serial.print("     ");
              String sizeString = fileSizeString(file.size());
              Serial.printf("%10s ", sizeString.c_str());
              Serial.println(file.name());
            }
            file = root.openNextFile();
          }
        }
      }

      Serial.println("");
      Serial.println("[USAGE]");
      Serial.println(" SPIFFS            : SPIFFS Info");
      Serial.println(" SPIFFS DIR [PATH] : Dir Info(default /)");
    }

    void dispSD(String command, String path1, String path2) {
      Serial.printf("===============================================================\n");
      Serial.println("SD");
      Serial.printf("===============================================================\n");
      sdcard_type_t cardType = SD.cardType();
      String cardTypeName = "";
      if (cardType == CARD_NONE) {
        cardTypeName = "(NONE)";
      } else if (cardType == CARD_MMC) {
        cardTypeName = "MMC";
      } else if (cardType == CARD_SD) {
        cardTypeName = "SD";
      } else if (cardType == CARD_SDHC) {
        cardTypeName = "SDHC";
      } else if (cardType == CARD_UNKNOWN) {
        cardTypeName = "(UNKNOWN)";
      }
      uint32_t cardSize = SD.cardSize();
      uint32_t totalBytes = SD.totalBytes();
      uint32_t usedBytes = SD.usedBytes();

      Serial.printf("Card Type   : %s\n", cardTypeName.c_str());
      String sizeString = fileSizeString(cardSize);
      Serial.printf("Card Size   : %10s\n", sizeString.c_str());
      sizeString = fileSizeString(totalBytes);
      Serial.printf("Total Bytes : %10s\n", sizeString.c_str());
      sizeString = fileSizeString(usedBytes);
      Serial.printf("Used Bytes  : %10s\n", sizeString.c_str());

      if (SD.cardSize() == 0) {
        // No SD
        return;
      }

      if (command == "DIR") {
        if (path1 == "") {
          path1 = "/";
        }
        Serial.println();
        Serial.println("[DIR " + path1 + "]");

        File root = SD.open(path1);
        if (root) {
          File file = root.openNextFile();
          while (file) {
            time_t t = file.getLastWrite();
            struct tm *tm_t = localtime(&t);
            Serial.printf("%04d-%02d-%02d %02d:%02d:%02d ", tm_t->tm_year + 1900, tm_t->tm_mon + 1, tm_t->tm_mday, tm_t->tm_hour, tm_t->tm_min, tm_t->tm_sec);
            if (file.isDirectory()) {
              Serial.print("<DIR>");
              Serial.print("           ");
              Serial.println(file.name());
            } else {
              // ファイル名とファイルサイズを出力
              Serial.print("     ");
              String sizeString = fileSizeString(file.size());
              Serial.printf("%10s ", sizeString.c_str());
              Serial.println(file.name());
            }
            file = root.openNextFile();
          }
        }
      }

      Serial.println("");
      Serial.println("[USAGE]");
      Serial.println(" SD            : SD Info");
      Serial.println(" SD DIR [PATH] : Dir Info(default /)");
    }

    void screenshot(fs::FS &fs, String filename) {
      Serial.printf("===============================================================\n");
      Serial.printf("SCREENSHOT\n");
      Serial.printf("===============================================================\n");

      if (&fs == &SD) {
        Serial.printf("Storage  : SD\n");
      }
      if (&fs == &SPIFFS) {
        Serial.printf("Storage  : SPIFFS\n");
      }

      Serial.printf("filename : %s\n", filename.c_str());

      File file = fs.open(filename, FILE_WRITE);
      if (!file) {
        Serial.printf("file not open!\n");
      }

      uint8_t headSize = 66;
      uint16_t width = _Lcd->width();
      uint16_t height = _Lcd->height();
      uint16_t dataSize = width * height * 2;
      uint16_t fileSize = headSize + dataSize;
      uint16_t rMask = 0b1111100000000000;
      uint16_t gMask = 0b0000011111100000;
      uint16_t bMask = 0b0000000000011111;

      // BMP Header
      file.write('B');
      file.write('M');

      // fileSize
      file.write((uint8_t)(fileSize & 0xff));
      file.write((uint8_t)(fileSize >> 8));
      file.write(0x00);
      file.write(0x00);

      // Reserve
      file.write(0x00);
      file.write(0x00);
      file.write(0x00);
      file.write(0x00);

      // headSize
      file.write(headSize);
      file.write(0x00);
      file.write(0x00);
      file.write(0x00);

      // infoSize
      file.write(0x28);
      file.write(0x00);
      file.write(0x00);
      file.write(0x00);

      // width
      file.write((uint8_t)(width & 0xff));
      file.write((uint8_t)(width >> 8));
      file.write(0x00);
      file.write(0x00);

      // height
      file.write((uint8_t)(height & 0xff));
      file.write((uint8_t)(height >> 8));
      file.write(0x00);
      file.write(0x00);

      // plane
      file.write(0x01);
      file.write(0x00);

      // bit/pixel
      file.write(16);
      file.write(0x00);

      // compression
      file.write(0x03);
      file.write(0x00);
      file.write(0x00);
      file.write(0x00);

      // dataSize
      file.write((uint8_t)(dataSize & 0xff));
      file.write((uint8_t)(dataSize >> 8));
      file.write(0x00);
      file.write(0x00);

      // Horizontal resolution
      file.write(0x00);
      file.write(0x00);
      file.write(0x00);
      file.write(0x00);

      // Vertical resolution
      file.write(0x00);
      file.write(0x00);
      file.write(0x00);
      file.write(0x00);

      // Color Size
      file.write(0x00);
      file.write(0x00);
      file.write(0x00);
      file.write(0x00);

      // Number of important colors
      file.write(0x00);
      file.write(0x00);
      file.write(0x00);
      file.write(0x00);

      // R MASK
      file.write((uint8_t)(rMask & 0xff));
      file.write((uint8_t)(rMask >> 8));
      file.write(0x00);
      file.write(0x00);

      // G MASK
      file.write((uint8_t)(gMask & 0xff));
      file.write((uint8_t)(gMask >> 8));
      file.write(0x00);
      file.write(0x00);

      // B MASK
      file.write((uint8_t)(bMask & 0xff));
      file.write((uint8_t)(bMask >> 8));
      file.write(0x00);
      file.write(0x00);

      // DATA
      bool swap = _Lcd->getSwapBytes();
      _Lcd->setSwapBytes(true);
      for (int y = 0; y < height; y++) {
        uint16_t pl[width];
        _Lcd->readRect(0, height - y - 1, width, 1, pl);
        file.write((uint8_t *)pl, width * 2);
      }
      _Lcd->setSwapBytes(swap);

      file.close();

      Serial.println("Finish!");
    }

    void update() {
      while (Serial.available()) {
        char input[256];
        String command = Serial.readStringUntil('\n');
        command.trim();
        strncpy(input, command.c_str(), sizeof(input) - 1);
        char* command0 = strtok(input, " ");
        command = command0;
        command0 = strtok(NULL, " ");
        String command2 = command0;
        command0 = strtok(NULL, " ");
        String command3 = command0;
        command0 = strtok(NULL, " ");
        String command4 = command0;

        if (command == "") {
          // Skip
        } else if (command == "?") {
          dispHelp();
        } else if (command == "RESET") {
          ESP.restart();
        } else if (command == "INFO") {
          dispInfo();
        } else if (command == "AXP192") {
          dispAxp192();
        } else if (command == "IMU") {
          dispImu();
        } else if (command == "RTC") {
          dispRtc();
        } else if (command == "MEM") {
          dispMemory();
        } else if (command == "GPIO") {
          dispGpio();
        } else if (command == "I2C") {
          dispI2c();
        } else if (command == "FORMAT") {
          formatStorage(command2);
        } else if (command == "SPIFFS") {
          dispSPIFFS(command2, command3, command4);
        } else if (command == "SD") {
          dispSD(command2, command3, command4);
        } else if (command == "SCREENSHOT") {
          String filename;
          if (command3 != "") {
            filename = command3;
          } else {
            char name[40];
            time_t t = time(NULL);
            struct tm *t_st;
            t_st = localtime(&t);
            snprintf(name, 40, "/screenshot_%04d-%02d-%02d_%02d-%02d-%02d.bmp",
                     t_st->tm_year + 1900, t_st->tm_mon + 1, t_st->tm_mday,
                     t_st->tm_hour, t_st->tm_min, t_st->tm_sec);
            filename = name;
          }
          if (command2 == "SPIFFS") {
            screenshot(SPIFFS, filename);
          } else {
            screenshot(SD, filename);
          }
#ifdef WiFi_h
        } else if (command == "WIFI") {
          connectWiFi(command2, command3);
        } else if (command == "NTP") {
          syncNTP(command2);
#endif
        } else {
          dispHelp();
        }

        Serial.println(">");
      }
    }
};

#endif
