#include "I2C_EEPROM.h"

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;

HAL_StatusTypeDef I2C_EEPROM_WriteByte(uint16_t WriteAddr, uint8_t* pData)
{

  HAL_StatusTypeDef state = HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, WriteAddr, I2C_MEMADD_SIZE_8BIT, pData, 1, 1000);
  if (state != HAL_OK)
  {
    HAL_UART_Transmit(&huart1, (uint8_t*)"Error Write EEPROM\r\n", sizeof("Error Write EEPROM\r"), 1000);
    return state;
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
  return state;
}

HAL_StatusTypeDef I2C_EEPROM_BuffWrite(uint16_t WriteAddr, uint8_t* pData, uint16_t NumByteToWrite)
{
  HAL_StatusTypeDef state = HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, WriteAddr, I2C_MEMADD_SIZE_8BIT, pData, NumByteToWrite, 1000);
  if (state != HAL_OK)
  {
    HAL_UART_Transmit(&huart1, (uint8_t*)"Error Write EEPROM\r\n", sizeof("Error Write EEPROM\r"), 1000);
    return state;
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
  return state;
}

HAL_StatusTypeDef I2C_EEPROM_BuffRead(uint16_t ReadAddr, uint8_t* pData, uint16_t NumByteToRead)
{
  HAL_StatusTypeDef state = HAL_I2C_Mem_Read(&hi2c1, EEPROM_ADDR, ReadAddr, I2C_MEMADD_SIZE_8BIT, pData, NumByteToRead, 1000);
  if (state != HAL_OK)
  {
    HAL_UART_Transmit(&huart1, (uint8_t*)"Error Read EEPROM\r\n", sizeof("Error Read EEPROM\r"), 1000);
  }
  return state;
}

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
