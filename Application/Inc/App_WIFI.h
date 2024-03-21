#ifndef APP_WIFI_H
#define APP_WIFI_H

#include "WIFI_ESP8266.h"
#include "I2C_EEPROM_AT24C02.h"

APP_StatusTypeDef Wire_Connect_WIFIConfig(const char* WIFI_SSID, const char* WIFI_PASSWORD);

#endif
