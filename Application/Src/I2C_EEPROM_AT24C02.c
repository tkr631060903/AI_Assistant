/**
 * @file I2C_EEPROM_AT24C02.c
 * @author TanKairong (tkr631060903@gmail.com)
 * @brief AT24C02驱动基于STM32F103 HAL库编写
 * 用串口打印调试信息需要重定义printf函数
 * 需要引用Application_Constant.h，stm32f1xx_hal_i2c.h头文件
 * @version 0.1
 * @date 2023-12-27
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "I2C_EEPROM_AT24C02.h"

extern I2C_HandleTypeDef hi2c1;

/**
 * @brief 写入一个Byte数据到EEPROM
 *
 * @param WriteAddr 写入EEPROM起始地址
 * @param pData 数据缓冲区
 * @return HAL_Status
 */
APP_StatusTypeDef I2C_EEPROM_WriteByte(uint16_t WriteAddr, uint8_t* pData)
{

  HAL_StatusTypeDef state = HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, WriteAddr, I2C_MEMADD_SIZE_8BIT, pData, 1, 1000);
  if (state != HAL_OK)
  {
#if AT24C02_Debug
    printf("Error Write EEPROM");
#endif
    return APP_ERROR;
  }
  // 检查I2C是否准备好
  while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
  {
  }
  // 检查I2C是否准备好
  while (HAL_I2C_IsDeviceReady(&hi2c1, EEPROM_ADDR, 300, 100) == HAL_TIMEOUT)
  {
  }
  // 等待传输结束,检查I2C是否准备好
  while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
  {
  }
  return APP_OK;
}

/**
 * @brief 连续写数据到EEPROM
 *
 * @param WriteAddr 写入EEPROM起始地址
 * @param pData 数据缓冲区
 * @param NumByteToWrite 写入数据个数
 * @return HAL_Status
 */
APP_StatusTypeDef I2C_EEPROM_BuffWrite(uint16_t WriteAddr, uint8_t* pData, uint16_t NumByteToWrite)
{
  HAL_StatusTypeDef state = HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, WriteAddr, I2C_MEMADD_SIZE_8BIT, pData, NumByteToWrite, 1000);
  if (state != HAL_OK)
  {
#if AT24C02_Debug
    printf("Error Write EEPROM");
#endif
    return APP_ERROR;
  }
  // 检查I2C是否准备好
  while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
  {
  }
  // 检查I2C是否准备好
  while (HAL_I2C_IsDeviceReady(&hi2c1, EEPROM_ADDR, 300, 100) == HAL_TIMEOUT)
  {
  }
  // 等待传输结束,检查I2C是否准备好
  while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
  {
  }
  return APP_OK;
}

/**
 * @brief 连续读EEPROM数据
 *
 * @param ReadAddr 读取EEPROM起始地址
 * @param pData 数据缓冲区
 * @param NumByteToRead 写入数据个数
 * @return HAL_Status
 */
APP_StatusTypeDef I2C_EEPROM_BuffRead(uint16_t ReadAddr, uint8_t* pData, uint16_t NumByteToRead)
{
  HAL_StatusTypeDef state = HAL_I2C_Mem_Read(&hi2c1, EEPROM_ADDR, ReadAddr, I2C_MEMADD_SIZE_8BIT, pData, NumByteToRead, 1000);
  if (state != HAL_OK)
  {
#if AT24C02_Debug
    printf("Error Read EEPROM");
#endif
    return APP_ERROR;
  }
  return APP_OK;
}

/**
 * @brief 校验EEPROM外设
 *
 * @return APP_Status
 */
APP_StatusTypeDef I2C_EEPROM_Check(void)
{
  uint8_t data[1] = { 0x10 };
  I2C_EEPROM_BuffWrite(2047, data, 1);
  data[0] = 0;
  I2C_EEPROM_BuffRead(2047, data, 1);
  if (data[0] == 0x10)
  {
    return APP_OK;
  }
  return APP_ERROR;
}

#if AT24C02_Debug
/**
 * @brief EEPROM读写测试
 *
 */
void I2C_EEPROM_WRTest(void)
{
  uint8_t writeData[3] = { 0x01, 0x02, 0x03 };
  uint8_t readData[3] = { 0x00, 0x00, 0x00 };
  I2C_EEPROM_BuffWrite(0x01, writeData, 3);
  I2C_EEPROM_BuffRead(0x01, readData, 3);
  if (readData[0] == writeData[0] && readData[1] == writeData[1] && readData[2] == writeData[2])
  {
    HAL_UART_Transmit(&huart1, "DataCheckOK\n", sizeof("DataCheckOK\n"), 1000);
  }
}
#endif
