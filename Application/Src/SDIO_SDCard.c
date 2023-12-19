#include "SDIO_SDCard.h"

extern SD_HandleTypeDef hsd;

/**
 *@brief 校验SD卡外设
 *
 * @return APP_Status
 */
APP_StatusTypeDef SDIO_SDCard_Check(void)
{
    uint32_t timeout = 100000;
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

/**
 *@brief 使用MDAM方式将数据写入SD卡
 *
 * @param hsd 指向SD句柄的指针
 * @param pData 指向包含要传输的数据的缓冲区的指针
 * @param BlockAdd：将写入数据的块地址
 * @param NumberOfBlocks：要写入的块数
 * @return APP_Status
 */
APP_StatusTypeDef SDIO_SDCard_WriteBlocks_DMA(SD_HandleTypeDef* hsd, uint8_t* pData, uint32_t BlockAdd, uint32_t NumberOfBlocks)
{
    while (HAL_SD_GetCardState(hsd) != HAL_SD_CARD_TRANSFER)
    {
    }
    extern DMA_HandleTypeDef hdma_sdio;
    HAL_DMA_DeInit(&hdma_sdio);
    hdma_sdio.Instance = DMA2_Channel4;
    hdma_sdio.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_sdio.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_sdio.Init.MemInc = DMA_MINC_ENABLE;
    hdma_sdio.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_sdio.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_sdio.Init.Mode = DMA_NORMAL;
    hdma_sdio.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    if (HAL_DMA_Init(&hdma_sdio) != HAL_OK)
    {
        Error_Handler();
    }
    __HAL_LINKDMA(hsd, hdmatx, hdma_sdio);
    if (HAL_SD_WriteBlocks_DMA(hsd, pData, BlockAdd, NumberOfBlocks) != HAL_OK)
    {
        return APP_OK;
    }
    else
    {
        return APP_ERROR;
    }
}

/**
 *@brief 使用MDAM方式从SD卡读取数据
 *
 * @param hsd 指向SD句柄的指针
 * @param pData 指向包含要传输的数据的缓冲区的指针
 * @param BlockAdd：将读取数据的块地址
 * @param NumberOfBlocks：要读取的块数
 * @return APP_Status
 */
APP_StatusTypeDef SDIO_SDCard_ReadBlocks_DMA(SD_HandleTypeDef* hsd, uint8_t* pData, uint32_t BlockAdd, uint32_t NumberOfBlocks)
{
    while (HAL_SD_GetCardState(hsd) != HAL_SD_CARD_TRANSFER)
    {
    }
    extern DMA_HandleTypeDef hdma_sdio;
    HAL_DMA_DeInit(&hdma_sdio);
    hdma_sdio.Instance = DMA2_Channel4;
    hdma_sdio.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_sdio.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_sdio.Init.MemInc = DMA_MINC_ENABLE;
    hdma_sdio.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_sdio.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_sdio.Init.Mode = DMA_NORMAL;
    hdma_sdio.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    if (HAL_DMA_Init(&hdma_sdio) != HAL_OK)
    {
        Error_Handler();
    }
    __HAL_LINKDMA(hsd, hdmarx, hdma_sdio);
    if (HAL_SD_ReadBlocks_DMA(hsd, pData, BlockAdd, NumberOfBlocks) != HAL_OK)
    {
        return APP_OK;
    }
    else
    {
        return APP_ERROR;
    }
}

#if 0
void Fill_Buffer(uint8_t* pBuffer, uint32_t BufferLength, uint32_t Offset);
void Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength);
uint8_t Buffer_Block_Tx[512 * 5];
uint8_t Buffer_Block_Rx[512 * 5];
void SDIO_SDCard_Test(void)
{
    printf("SDIO_SDCard_Test\r\n");
    HAL_SD_CardInfoTypeDef cardInfo;
    HAL_SD_GetCardInfo(&hsd, &cardInfo);
    printf("Card BlockNbr: %d\r\n", cardInfo.BlockNbr);
    HAL_StatusTypeDef status = HAL_SD_Erase(&hsd, 2, 5);
    while (HAL_SD_GetCardState(&hsd) != HAL_SD_CARD_TRANSFER)
    {
    }
    Fill_Buffer(Buffer_Block_Tx, sizeof(Buffer_Block_Tx), 0x0);
    printf("write\r\n");
    SDIO_SDCard_WriteBlocks_DMA(&hsd, Buffer_Block_Tx, 2, 5);
    // status = HAL_SD_WriteBlocks(&hsd, Buffer_Block_Tx, 2, 5, 1000);
    while (HAL_SD_GetCardState(&hsd) != HAL_SD_CARD_TRANSFER)
    {
    }
    printf("read\r\n");
    SDIO_SDCard_ReadBlocks_DMA(&hsd, Buffer_Block_Rx, 2, 5);
    // status = HAL_SD_ReadBlocks(&hsd, Buffer_Block_Rx, 2, 5, 1000);
    while (HAL_SD_GetCardState(&hsd) != HAL_SD_CARD_TRANSFER)
    {
    }
    Buffercmp(Buffer_Block_Tx, Buffer_Block_Rx, 512 * 5);
}
void Fill_Buffer(uint8_t* pBuffer, uint32_t BufferLength, uint32_t Offset)
{
    uint16_t index = 0;
    /* Put in global buffer same values */
    for (index = 0; index < BufferLength; index++) {
        pBuffer[index] = index + Offset;
        // pBuffer[index] = 0xff;
        // printf("%02x ", pBuffer[index]);
    }
}
void Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength)
{
    printf("cmpstart\r\n");
    while (BufferLength--) {
        if (*pBuffer1 != *pBuffer2) {
            // printf("%02x != %02x\r\n", *pBuffer1, *pBuffer2);
            printf("Buffercmp_Error\r\n");
            return;
        }
        pBuffer1++;
        pBuffer2++;
    }
    printf("Buffercmp_OK\r\n");
}
#endif 

