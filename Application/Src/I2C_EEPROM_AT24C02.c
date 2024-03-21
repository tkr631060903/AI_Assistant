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
#include "string.h"

#if AT24C02_Debug
#include "UART_Debug.h"
#endif

extern I2C_HandleTypeDef hi2c1;

/**
 * @brief 写入一个Byte数据到EEPROM
 *
 * @param WriteAddr 写入EEPROM起始地址
 * @param pData 数据缓冲区
 */
void I2C_EEPROM_WriteByte(uint16_t WriteAddr, uint8_t* pData)
{

  HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, WriteAddr, I2C_MEMADD_SIZE_8BIT, pData, 1, 1000);
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
}

/**
 * @brief 页写入数据到EEPROM，每次写入不超过8字节数据
 *
 * @param WriteAddr 写入EEPROM起始地址
 * @param pData 数据缓冲区
 */
void I2C_EEPROM_PageWrite(uint16_t WriteAddr, uint8_t* pData, uint16_t NumByteToWrite)
{
  if (NumByteToWrite > EEPROM_PAGE_SIZE)
  {
    return;
  }
  HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, WriteAddr, I2C_MEMADD_SIZE_8BIT, pData, NumByteToWrite, 1000);
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
}

/**
 * @brief 连续写数据到EEPROM
 *
 * @param WriteAddr 写入EEPROM起始地址
 * @param pData 数据缓冲区
 * @param NumByteToWrite 写入数据个数
 */
void I2C_EEPROM_BuffWrite(uint16_t WriteAddr, uint8_t* pData, uint16_t NumByteToWrite)
{
  uint8_t pageCount = 0;  // 需要写入的页数
  uint8_t lastWrite = NumByteToWrite % EEPROM_PAGE_SIZE;  // 最后一次写入的字节数
  // 计算需要写入的页数
  if (lastWrite == 0)
  {
    pageCount = NumByteToWrite / EEPROM_PAGE_SIZE;
  }
  pageCount = (NumByteToWrite - lastWrite) / EEPROM_PAGE_SIZE;
  while (pageCount)
  {
    // 开始按页写入数据
    I2C_EEPROM_PageWrite(WriteAddr, pData, EEPROM_PAGE_SIZE);
    pageCount--;
    WriteAddr += EEPROM_PAGE_SIZE;
    pData += EEPROM_PAGE_SIZE;
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
    {
    }
  }
  if (lastWrite != 0)
  {
    // 写入最后一次不满8个字节的数据
    HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, WriteAddr, I2C_MEMADD_SIZE_8BIT, pData, lastWrite, 1000);
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
}

/**
 * @brief 将字符串写入到EEPROM
 *
 * @param WriteAddr 写入EEPROM起始地址
 * @param pData 数据缓冲区
 * @param NumByteToWrite 写入字符个数
 */
void I2C_EEPROM_StringWrite(uint16_t WriteAddr, const char* pData, uint16_t NumByteToWrite)
{
  uint8_t pageCount = 0;  // 需要写入的页数
  uint8_t lastWrite = NumByteToWrite % EEPROM_PAGE_SIZE;  // 最后一次写入的字节数
  // 计算需要写入的页数
  if (lastWrite == 0)
  {
    pageCount = NumByteToWrite / EEPROM_PAGE_SIZE;
  }
  pageCount = (NumByteToWrite - lastWrite) / EEPROM_PAGE_SIZE;
  while (pageCount)
  {
    // 开始按页写入数据
    I2C_EEPROM_PageWrite(WriteAddr, (uint8_t*)pData, EEPROM_PAGE_SIZE);
    pageCount--;
    WriteAddr += EEPROM_PAGE_SIZE;
    pData += EEPROM_PAGE_SIZE;
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
    {
    }
  }
  if (lastWrite != 0)
  {
    // 写入最后一次不满8个字节的数据
    HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, WriteAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)pData, lastWrite, 1000);
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
}

/**
 *@brief 将字符串写入到EEPROM，回读数据校验
 *
 * @param WriteAddr 写入EEPROM起始地址
 * @param pData 数据缓冲区
 * @param NumByteToWrite 写入字符个数
 * @return APP_StatusTypeDef
 */
APP_StatusTypeDef I2C_EEPROM_StringWrite_Check(uint16_t WriteAddr, const char* pData, uint16_t NumByteToWrite)
{
  uint8_t pageCount = 0;  // 需要写入的页数
  uint8_t lastWrite = NumByteToWrite % EEPROM_PAGE_SIZE;  // 最后一次写入的字节数
  uint16_t nitialAddress = WriteAddr; // 写入数据的初始地址
  const char* nitialData = pData; // 写入数据的初始数(指针)
  // 计算需要写入的页数
  if (lastWrite == 0)
  {
    pageCount = NumByteToWrite / EEPROM_PAGE_SIZE;
  }
  pageCount = (NumByteToWrite - lastWrite) / EEPROM_PAGE_SIZE;
  while (pageCount)
  {
    // 开始按页写入数据
    I2C_EEPROM_PageWrite(WriteAddr, (uint8_t*)pData, EEPROM_PAGE_SIZE);
    pageCount--;
    WriteAddr += EEPROM_PAGE_SIZE;
    pData += EEPROM_PAGE_SIZE;
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
    {
    }
  }
  if (lastWrite != 0)
  {
    // 写入最后一次不满8个字节的数据
    HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, WriteAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)pData, lastWrite, 1000);
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
  // 回读EEPROM数据并校验
  const char pDataCheck[NumByteToWrite];
  I2C_EEPROM_StringRead(nitialAddress, pDataCheck, NumByteToWrite);
  if (strcmp(nitialData, pDataCheck) != 0)
  {
    return APP_ERROR;
  }
  return APP_OK;
}

/**
 * @brief 连续写数据到EEPROM，回读数据校验
 *
 * @param WriteAddr 写入EEPROM起始地址
 * @param pData 数据缓冲区
 * @param NumByteToWrite 写入数据个数
 * @return APP_StatusTypeDef
 */
APP_StatusTypeDef I2C_EEPROM_BuffWrite_Check(uint16_t WriteAddr, uint8_t* pData, uint16_t NumByteToWrite)
{
  uint8_t pageCount = 0;  // 需要写入的页数
  uint8_t lastWrite = NumByteToWrite % EEPROM_PAGE_SIZE;  // 最后一次写入的字节数
  uint16_t nitialAddress = WriteAddr; // 写入数据的初始地址
  uint8_t* nitialData = pData; // 写入数据的初始数(指针)
  // 计算需要写入的页数
  if (lastWrite == 0)
  {
    pageCount = NumByteToWrite / EEPROM_PAGE_SIZE;
  }
  pageCount = (NumByteToWrite - lastWrite) / EEPROM_PAGE_SIZE;
  while (pageCount)
  {
    // 开始按页写入数据
    I2C_EEPROM_PageWrite(WriteAddr, pData, EEPROM_PAGE_SIZE);
    pageCount--;
    WriteAddr += EEPROM_PAGE_SIZE;
    pData += EEPROM_PAGE_SIZE;
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
    {
    }
  }
  if (lastWrite != 0)
  {
    // 写入最后一次不满8个字节的数据
    HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, WriteAddr, I2C_MEMADD_SIZE_8BIT, pData, lastWrite, 1000);
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
  // 回读EEPROM数据并校验
  uint8_t pDataCheck[NumByteToWrite];
  I2C_EEPROM_BuffRead(nitialAddress, pDataCheck, NumByteToWrite);
  for (int i = 0; i < NumByteToWrite; i++)
  {
    if (pDataCheck[i] != nitialData[i])
    {
      return APP_ERROR;
    }
  }
  return APP_OK;
}

/**
 * @brief 连续读EEPROM数据
 *
 * @param ReadAddr 读取EEPROM起始地址
 * @param pData 数据缓冲区
 * @param NumByteToRead 读取数据个数
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
 * @brief 以字符串形式读取EEPROM数据
 *
 * @param ReadAddr 读取EEPROM起始地址
 * @param pData 数据缓冲区
 * @param NumByteToRead 读取字符个数
 * @return HAL_Status
 */
APP_StatusTypeDef I2C_EEPROM_StringRead(uint16_t ReadAddr, const char* pData, uint16_t NumByteToRead)
{
  HAL_StatusTypeDef state = HAL_I2C_Mem_Read(&hi2c1, EEPROM_ADDR, ReadAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*)pData, NumByteToRead, 1000);
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
