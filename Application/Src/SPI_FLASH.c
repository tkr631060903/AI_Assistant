#include "SPI_FLASH.h"

extern SPI_HandleTypeDef hspi1;

uint8_t SPI_FLASH_SendByte(uint8_t byte)
{
  uint8_t data = 0;
  HAL_StatusTypeDef status;
  status = HAL_SPI_TransmitReceive(&hspi1, &byte, &data, 1, 1000);
  while (status != HAL_OK)
  {
  }
  //  status = HAL_SPI_Transmit(&hspi1, &byte, 1, 1000);
  // // status = HAL_SPI_Transmit_DMA(&hspi1, &byte, sizeof(&byte));
  // while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_TX_RX || status != HAL_OK)
  // {
  // }
  // status = HAL_SPI_Receive(&hspi1, &data, 1, 1000);
  // // status = HAL_SPI_Receive_DMA(&hspi1, &data, sizeof(&data));
  // while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_TX_RX || status != HAL_OK)
  // {
  // }
  return data;
}

APP_StatusTypeDef SPI_FLASH_ReadJEDECID(void)
{
  uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

  SPI_FLASH_CS_LOW;

  SPI_FLASH_SendByte(W25X_JedecDeviceID);
  Temp0 = SPI_FLASH_SendByte(W25X_Dummy_Byte);
  Temp1 = SPI_FLASH_SendByte(W25X_Dummy_Byte);
  Temp2 = SPI_FLASH_SendByte(W25X_Dummy_Byte);

  SPI_FLASH_CS_HIGH;
  Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;
  printf("0x%x\r\n", Temp);
  if (Temp == 0xEF4017)
  {
    return APP_OK;
  }
  return APP_ERROR;
}
