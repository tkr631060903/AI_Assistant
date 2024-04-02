#ifndef APP_WIFI_H
#define APP_WIFI_H

#include "WIFI_ESP8266.h"
#include "I2C_EEPROM_AT24C02.h"

#define WIFI_SSID_SAVEADDR 0x00 // WIFISSID保存在EEPROM的起始地址，占30个字节
#define WIFI_PASSWORD_SAVEADDR 0x30 // WIFIPASSWORD保存在EEPROM的起始地址，占30个字节

APP_StatusTypeDef Wire_Connect_WIFIConfig(const char* WIFI_SSID, const char* WIFI_PASSWORD);

#endif
