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
#ifndef __WIFI_ESP8266_H__
#define __WIFI_ESP8266_H__

#include "Application.h"

#define WIFI_ESP8266_Reply_Length 20

#define     WIFI_ESP8266_RST_HIGH_LEVEL()            HAL_GPIO_WritePin(WIFI_ESP8266_RST_GPIO_Port, WIFI_ESP8266_RST_Pin, GPIO_PIN_SET)
#define     WIFI_ESP8266_RST_LOW_LEVEL()             HAL_GPIO_WritePin(WIFI_ESP8266_RST_GPIO_Port, WIFI_ESP8266_RST_Pin, GPIO_PIN_RESET)
#define     WIFI_ESP8266_ENABLE()                    HAL_GPIO_WritePin(WIFI_ESP8266_EN_GPIO_Port, WIFI_ESP8266_EN_Pin, GPIO_PIN_SET)
#define     WIFI_ESP8266_DISABLE()                   HAL_GPIO_WritePin(WIFI_ESP8266_EN_GPIO_Port, WIFI_ESP8266_EN_Pin, GPIO_PIN_RESET)

APP_StatusTypeDef WIFI_ESP8266_Check(void);

#define WIFI_ESP8266_Debug 0

#ifdef WIFI_ESP8266_Debug
void WIFI_ESP8266_Test(void);
#endif

#endif
