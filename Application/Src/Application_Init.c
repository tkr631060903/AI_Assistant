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
 * @brief 应用初始化
 * 
 */
void Application_Init(void)
{
    // 初始化串口中断输入
    uint8_t Uart1_ReceiveBuff = 0;
    HAL_UART_Receive_IT(&huart1, &Uart1_ReceiveBuff, sizeof(Uart1_ReceiveBuff));
    SDIO_CARD_Init();
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
    if (SDIO_SDCard_Check() == APP_OK) {
        printf("SDCard Check Success\r\n");
    }
    else {
        printf("SDCard Check Failed\r\n");
        Error_Handler();
    }
    // SDIO_SDCard_Test();
    printf("Init Success\r\n");
}
