#ifndef __I2C_EEPROM_H__
#define __I2C_EEPROM_H__

#include "Application.h"

#define EEPROM_ADDR 0xA0

void I2C_EEPROM_WRTest(void);
HAL_StatusTypeDef I2C_EEPROM_WriteByte(uint8_t WriteAddr, uint8_t *pData);
HAL_StatusTypeDef I2C_EEPROM_BuffRead(uint8_t ReadAddr, uint8_t *pData, uint16_t NumByteToRead);
HAL_StatusTypeDef I2C_EEPROM_BuffWrite(uint8_t WriteAddr, uint8_t *pData, uint16_t NumByteToWrite);

#endif
