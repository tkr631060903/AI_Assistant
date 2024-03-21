/**
 * @file I2C_EEPROM_AT24C02.h
 * @author TanKairong (tkr631060903@gmail.com)
 * @brief AT24C02驱动基于STM32F103 HAL库编写
 * @version 0.1
 * @date 2023-12-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __I2C_EEPROM_AT24C02_H__
#define __I2C_EEPROM_AT24C02_H__

#include "Application.h"
#include "Application_Constant.h"

#define AT24C02_Debug 0

#define EEPROM_ADDR 0xA0
#define EEPROM_PAGE_SIZE 8

void I2C_EEPROM_WriteByte(uint16_t WriteAddr, uint8_t *pData);
APP_StatusTypeDef I2C_EEPROM_BuffRead(uint16_t ReadAddr, uint8_t *pData, uint16_t NumByteToRead);
void I2C_EEPROM_BuffWrite(uint16_t WriteAddr, uint8_t* pData, uint16_t NumByteToWrite);
void I2C_EEPROM_PageWrite(uint16_t WriteAddr, uint8_t* pData, uint16_t NumByteToWrite);
void I2C_EEPROM_StringWrite(uint16_t WriteAddr, const char* pData, uint16_t NumByteToWrite);
APP_StatusTypeDef I2C_EEPROM_StringWrite_Check(uint16_t WriteAddr, const char* pData, uint16_t NumByteToWrite);
APP_StatusTypeDef I2C_EEPROM_BuffWrite_Check(uint16_t WriteAddr, uint8_t* pData, uint16_t NumByteToWrite);
APP_StatusTypeDef I2C_EEPROM_StringRead(uint16_t ReadAddr, const char* pData, uint16_t NumByteToRead);
APP_StatusTypeDef I2C_EEPROM_Check(void);

#if AT24C02_Debug
void I2C_EEPROM_WRTest(void);
#endif

#endif
