#include "SDIO_SDCard.h"

APP_StatusTypeDef SDIO_SDCard_Check(void)
{
    uint32_t timeout = 100000;
    extern SD_HandleTypeDef hsd;
    while (HAL_SD_InitCard(&hsd) != HAL_OK)
    {
        if (timeout-- == 0)
        {
            return APP_ERROR;
        }
    }
    timeout = 100000;
    while (HAL_SD_GetCardState(&hsd) != HAL_SD_CARD_TRANSFER)
    {
        if (timeout-- == 0)
        {
            return APP_ERROR;
        }
    }
    return APP_OK;
}
