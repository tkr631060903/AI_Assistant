#ifndef __SDIO_SDCard_H__
#define __SDIO_SDCard_H__

#include "Application.h"

APP_StatusTypeDef SDIO_SDCard_Check(void);
APP_StatusTypeDef SDIO_SDCard_WriteBlocks_DMA(SD_HandleTypeDef* hsd, uint8_t* pData, uint32_t BlockAdd, uint32_t NumberOfBlocks);
APP_StatusTypeDef SDIO_SDCard_ReadBlocks_DMA(SD_HandleTypeDef* hsd, uint8_t* pData, uint32_t BlockAdd, uint32_t NumberOfBlocks);

#endif
