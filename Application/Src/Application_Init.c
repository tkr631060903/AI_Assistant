#include "Application_Init.h"

void Application_Init(void)
{
    uint8_t Uart1_ReceiveBuff = 0;
    I2C_EEPROM_WRTest();
    SPI_FLASH_ReadJEDECID();
    HAL_UART_Receive_IT(&huart1, &Uart1_ReceiveBuff, sizeof(Uart1_ReceiveBuff));
}
