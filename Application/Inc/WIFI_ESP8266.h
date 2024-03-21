/**
 *@file WIFI_ESP8266.h
 * @author TanKairong (tkr631060903@gmail.com)
 * @brief ESP8266驱动基于STM32F103 HAL库编写
 * @version 0.1
 * @date 2024-01-04
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef WIFI_ESP8266_H
#define WIFI_ESP8266_H

#include "Application_Constant.h"

typedef enum
{
    STA = 0,
    AP,
    STA_AP
}WIFI_ESP8266_ModeTypeDef;

#define WIFI_ESP8266_Reply_Length 100

#define     WIFI_ESP8266_RST_HIGH_LEVEL()            HAL_GPIO_WritePin(WIFI_ESP8266_RST_GPIO_Port, WIFI_ESP8266_RST_Pin, GPIO_PIN_SET)
#define     WIFI_ESP8266_RST_LOW_LEVEL()             HAL_GPIO_WritePin(WIFI_ESP8266_RST_GPIO_Port, WIFI_ESP8266_RST_Pin, GPIO_PIN_RESET)
#define     WIFI_ESP8266_ENABLE()                    HAL_GPIO_WritePin(WIFI_ESP8266_EN_GPIO_Port, WIFI_ESP8266_EN_Pin, GPIO_PIN_SET)
#define     WIFI_ESP8266_DISABLE()                   HAL_GPIO_WritePin(WIFI_ESP8266_EN_GPIO_Port, WIFI_ESP8266_EN_Pin, GPIO_PIN_RESET)
// #define WIFI_SSID "iQOONeo5"
// #define WIFI_PASSWORD "rong19980521"

APP_StatusTypeDef WIFI_ESP8266_Check(void);
APP_StatusTypeDef WIFI_ESP8266_Connect(const char *WIFI_SSID, const char *WIFI_PASSWORD);
APP_StatusTypeDef WIFI_ESP8266_JoinAP(const char* SSID, const char* PASSWORD);
APP_StatusTypeDef WIFI_ESP8266_SetMode(WIFI_ESP8266_ModeTypeDef mode);

#define WIFI_ESP8266_Debug 0

#ifdef WIFI_ESP8266_Debug
void WIFI_ESP8266_Test(void);
#endif

#endif
