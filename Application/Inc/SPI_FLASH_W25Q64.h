/**
 * @file SPI_FLASH_W25Q64.h
 * @author TanKairong (tkr631060903@gmail.com)
 * @brief W25Q64驱动基于STM32F103 HAL库编写
 * @version 0.1
 * @date 2023-12-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __SPI_FLASH_W25Q64_H__
#define __SPI_FLASH_W25Q64_H__

#include "Application.h"

#define W25Q64_Debug 0
#define SPI_FLASH_PageSize 256 // W25Q64页大小，256byte
#define W25Q64_FLASH_ID 0xEF4017 // W25Q64

// FLASH命令定义
#define W25X_WriteEnable 0x06
#define W25X_WriteDisable 0x04
#define W25X_ReadStatusReg 0x05
#define W25X_WriteStatusReg 0x01
#define W25X_ReadData 0x03
#define W25X_FastReadData 0x0B
#define W25X_FastReadDual 0x3B
#define W25X_PageProgram 0x02
#define W25X_BlockErase 0xD8
#define W25X_SectorErase 0x20
#define W25X_ChipErase 0xC7
#define W25X_PowerDown 0xB9
#define W25X_ReleasePowerDown 0xAB
#define W25X_DeviceID 0xAB
#define W25X_ManufactDeviceID 0x90
#define W25X_JedecDeviceID 0x9F
#define W25X_Dummy_Byte 0x00

#define SPI_FLASH_CS_GPIO_Port GPIOC
#define SPI_FLASH_CS_Pin GPIO_PIN_0
#define SPI_FLASH_CS_LOW HAL_GPIO_WritePin(SPI_FLASH_CS_GPIO_Port, SPI_FLASH_CS_Pin, GPIO_PIN_RESET)
#define SPI_FLASH_CS_HIGH HAL_GPIO_WritePin(SPI_FLASH_CS_GPIO_Port, SPI_FLASH_CS_Pin, GPIO_PIN_SET)

APP_StatusTypeDef SPI_FLASH_BufferReadJEDECID(void);
APP_StatusTypeDef SPI_FLASH_Check(void);
void SPI_FLASH_ChipSector(void);
void SPI_FLASH_WaitForWriteEnd(void);
void SPI_FLASH_WriteEnable(void);
void SPI_FLASH_WriteDisable(void);
void SPI_FLASH_SectorSector(uint32_t SectorAddr);
void SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);

#if W25Q64_Debug
void SPI_FLASH_Test(void);
#endif

#endif
