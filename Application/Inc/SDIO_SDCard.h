/**
 * @file SDIO_SDCard.c
 * @author TanKairong (tkr631060903@gmail.com)
 * @brief SD卡驱动基于STM32F103 HAL库编写
 * @version 0.1
 * @date 2023-12-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __SDIO_SDCard_H__
#define __SDIO_SDCard_H__

#include "Application.h"

#define SDCard_Debug 0

APP_StatusTypeDef SDIO_SDCard_Check(void);
APP_StatusTypeDef SDIO_SDCard_WriteBlocks_DMA(SD_HandleTypeDef* hsd, uint8_t* pData, uint32_t BlockAdd, uint32_t NumberOfBlocks);
APP_StatusTypeDef SDIO_SDCard_ReadBlocks_DMA(SD_HandleTypeDef* hsd, uint8_t* pData, uint32_t BlockAdd, uint32_t NumberOfBlocks);

void SDIO_SDCard_Test(void);

#endif
