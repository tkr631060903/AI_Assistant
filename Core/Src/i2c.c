/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    i2c.c
 * @brief   This file provides code for the configuration
 *          of the I2C instances.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

/* USER CODE BEGIN 0 */
extern UART_HandleTypeDef huart1;
/* USER CODE END 0 */

I2C_HandleTypeDef hi2c1;

/* I2C1 init function */
void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspInit 0 */

  /* USER CODE END I2C1_MspInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* I2C1 clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
  /* USER CODE BEGIN I2C1_MspInit 1 */

  /* USER CODE END I2C1_MspInit 1 */
  }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{

  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspDeInit 0 */

  /* USER CODE END I2C1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();

    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);

  /* USER CODE BEGIN I2C1_MspDeInit 1 */

  /* USER CODE END I2C1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
HAL_StatusTypeDef I2C_EEPROM_WriteByte(uint8_t WriteAddr, uint8_t *pData)
{

  HAL_StatusTypeDef state = HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, WriteAddr, I2C_MEMADD_SIZE_8BIT, pData, 1, 1000);
  if (state != HAL_OK)
  {
    HAL_UART_Transmit(&huart1, (uint8_t *)"Error Write EEPROM\r\n", sizeof("Error Write EEPROM\r"), 1000);
    return state;
  }
  // �?查I2C总线是否准备�?
  while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
  {
  }
  // �?查I2C总线是否准备�?
  while (HAL_I2C_IsDeviceReady(&hi2c1, EEPROM_ADDR, 300, 100) == HAL_TIMEOUT)
  {
  }
  // 等待传输结束,�?查I2C总线是否准备�?
  while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
  {
  }
  return state;
}

HAL_StatusTypeDef I2C_EEPROM_BuffWrite(uint8_t WriteAddr, uint8_t *pData, uint16_t NumByteToWrite)
{
  HAL_StatusTypeDef state = HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, WriteAddr, I2C_MEMADD_SIZE_8BIT, pData, NumByteToWrite, 1000);
  if (state != HAL_OK)
  {
    HAL_UART_Transmit(&huart1, (uint8_t *)"Error Write EEPROM\r\n", sizeof("Error Write EEPROM\r"), 1000);
    return state;
  }
  // �?查I2C总线是否准备�?
  while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
  {
  }
  // �?查I2C总线是否准备�?
  while (HAL_I2C_IsDeviceReady(&hi2c1, EEPROM_ADDR, 300, 100) == HAL_TIMEOUT)
  {
  }
  // 等待传输结束,�?查I2C总线是否准备�?
  while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
  {
  }
  return state;
}

HAL_StatusTypeDef I2C_EEPROM_BuffRead(uint8_t ReadAddr, uint8_t *pData, uint16_t NumByteToRead)
{
  HAL_StatusTypeDef state = HAL_I2C_Mem_Read(&hi2c1, EEPROM_ADDR, ReadAddr, I2C_MEMADD_SIZE_8BIT, pData, NumByteToRead, 1000);
  if (state != HAL_OK)
  {
    HAL_UART_Transmit(&huart1, (uint8_t *)"Error Read EEPROM\r\n", sizeof("Error Read EEPROM\r"), 1000);
  }
  return state;
}

void I2C_EEPROM_WRTest(void)
{
  uint8_t writeData[3] = {0x01, 0x02, 0x03};
  uint8_t readData[3] = {0x00, 0x00, 0x00};
  I2C_EEPROM_BuffWrite(0x01, writeData, 3);
  I2C_EEPROM_BuffRead(0x01, readData, 3);
  if (readData[0] == writeData[0] && readData[1] == writeData[1] && readData[2] == writeData[2])
  {
    HAL_UART_Transmit(&huart1, "DataCheckOK\n", sizeof("DataCheckOK\n"), 1000);
  }
}
/* USER CODE END 1 */
