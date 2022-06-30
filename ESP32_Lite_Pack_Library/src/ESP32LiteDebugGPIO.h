#ifndef __ESP32LiteDebugGPIO_H__
#define __ESP32LiteDebugGPIO_H__

#include "soc/rtc_periph.h"

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

typedef struct {
  bool enable: 1;
  bool pullup: 1;
  bool pulldown: 1;
  bool openDrain: 1;
  bool adc: 1;
  bool output: 1;
  bool level: 1;
} _gpio_info_t;

_gpio_info_t getPinMode(uint8_t pin)
{
  _gpio_info_t info = {};

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
    _gpio_info_t gpioInfo = getPinMode(i);
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

#endif
