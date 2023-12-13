#ifndef __SPI_FLASH_H__
#define __SPI_FLASH_H__

#include "Application.h"
#include "usart.h"

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

APP_StatusTypeDef SPI_FLASH_ReadJEDECID(void);
APP_StatusTypeDef SPI_FLASH_Check(void);

#endif
