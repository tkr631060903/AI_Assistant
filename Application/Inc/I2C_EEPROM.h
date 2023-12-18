#ifndef __I2C_EEPROM_H__
#define __I2C_EEPROM_H__

#include "Application.h"

#define EEPROM_ADDR 0xA0

void I2C_EEPROM_WRTest(void);
HAL_StatusTypeDef I2C_EEPROM_WriteByte(uint16_t WriteAddr, uint8_t *pData);
HAL_StatusTypeDef I2C_EEPROM_BuffRead(uint16_t ReadAddr, uint8_t *pData, uint16_t NumByteToRead);
HAL_StatusTypeDef I2C_EEPROM_BuffWrite(uint16_t WriteAddr, uint8_t* pData, uint16_t NumByteToWrite);
APP_StatusTypeDef I2C_EEPROM_Check(void);

#endif