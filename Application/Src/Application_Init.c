/**
 * @file Application_Init.c
 * @author TanKairong (tkr631060903@gmail.com)
 * @brief 应用初始化
 * @version 0.1
 * @date 2023-12-27
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "Application_Init.h"
#include "Application_Constant.h"
#include "UART_Debug.h"
#include "I2C_EEPROM_AT24C02.h"
#include "SPI_FLASH_W25Q64.h"
#include "SDIO_SDCard.h"
#include "WIFI_ESP8266.h"
#include "App_WIFI.h"


uint8_t Uart1_ReceiveBuff = 0;  //串口1接收缓冲区
uint8_t Uart3_ReceiveBuff = 0;  //串口3接收缓冲区

/**
* @brief SD卡自定义初始化
*
*/
void SDIO_CARD_Init(void)
{
    /* 初始化完成SDIO卡后为了提高读写，开启4bits模式 */
    extern SD_HandleTypeDef hsd;
    hsd.Init.BusWide = SDIO_BUS_WIDE_1B;
    if (HAL_SD_Init(&hsd) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_SD_ConfigWideBusOperation(&hsd, SDIO_BUS_WIDE_4B) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
* @brief WIFI_ESP8266自定义初始化
*
*/
void WIFI_ESP8266_Init(void)
{
    WIFI_ESP8266_RST_HIGH_LEVEL();
    WIFI_ESP8266_ENABLE();
}

/**
 * @brief 应用初始化
 *
 */
void Application_Init(void)
{
    // 初始化串口中断输入
    HAL_UART_Receive_IT(&huart1, &Uart1_ReceiveBuff, 1);
    HAL_UART_Receive_IT(&huart3, &Uart3_ReceiveBuff, 1);
    SDIO_CARD_Init();
    WIFI_ESP8266_Init();
    // I2C_EEPROM_WRTest();
    if (I2C_EEPROM_Check() == APP_OK) {
        printf("EEPROM Check Success\r\n");
    }
    else {
        printf("EEPROM Check Failed\r\n");
        Error_Handler();
    }
    // SPI_FLASH_Test();
    if (SPI_FLASH_Check() == APP_OK) {
        printf("FLASH Check Success\r\n");
    }
    else {
        printf("FLASH Check Failed\r\n");
        Error_Handler();
    }
    // SDIO_SDCard_Test();
    if (SDIO_SDCard_Check() == APP_OK) {
        printf("SDCard Check Success\r\n");
    }
    else {
        printf("SDCard Check Failed\r\n");
        Error_Handler();
    }
    if (WIFI_ESP8266_Check() == APP_OK) {
        printf("WIFI_ESP8266 Check Success\r\n");
    }
    // WIFI_ESP8266_Test();
    Wire_Connect_WIFIConfig("iQOONeo5", "rong19980521");
    printf("Init Success\r\n");
}
