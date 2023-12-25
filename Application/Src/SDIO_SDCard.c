#include "SDIO_SDCard.h"

extern SD_HandleTypeDef hsd;

/**
 *@brief 校验SD卡外设
 *
 * @return APP_Status
 */
APP_StatusTypeDef SDIO_SDCard_Check(void)
{
    if (HAL_SD_InitCard(&hsd) != HAL_OK)
    {
        return APP_ERROR;
    }
    uint32_t timeout = 1000;
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
 *@brief 使用DMA方式将数据写入SD卡
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
 *@brief 使用DMA方式从SD卡读取数据
 *
 * @param hsd 指向SD句柄的指针
 * @param pData 指向包含要传输的数据的缓冲区的指针
 * @param BlockAdd：将读取数据的块地址
 * @param NumberOfBlocks：要读取的块数
 * @return APP_Status
 */
APP_StatusTypeDef SDIO_SDCard_ReadBlocks_DMA(SD_HandleTypeDef* hsd, uint8_t* pData, uint32_t BlockAdd, uint32_t NumberOfBlocks)
{
    while (HAL_SD_GetCardState(hsd) != HAL_SD_CARD_TRANSFER) {
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
    if (HAL_DMA_Init(&hdma_sdio) != HAL_OK) {
        Error_Handler();
    }
    __HAL_LINKDMA(hsd, hdmarx, hdma_sdio);
    if (HAL_SD_ReadBlocks_DMA(hsd, pData, BlockAdd, NumberOfBlocks) != HAL_OK) {
        return APP_OK;
    }
    else {
        return APP_ERROR;
    }
}

#if 0
void Fill_Buffer(uint8_t* pBuffer, uint32_t BufferLength, uint32_t Offset);
void Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength);
void SDCard_WETest(void);
void SDCard_FatFS(void);
uint8_t Buffer_Block_Tx[512 * 5];
uint8_t Buffer_Block_Rx[512 * 5];
FATFS fs;                                        /* FatFs文件系统对象 */
FRESULT res;                                     /* 文件操作结果 */
BYTE work[_MAX_SS];                              /* Work area (larger is better for processing time) */
FIL file;                                        /* 文件对象 */
UINT fnum;                                       /* 文件成功读写数量 */
BYTE ReadBuffer[1024] = { 0 };                   /* 读缓冲区 */
BYTE WriteBuffer[] = "我是写入数据,我是写入数据."; /* 写缓冲区*/
void SDIO_SDCard_Test(void)
{
    printf("SDIO_SDCard_Test\r\n");
    HAL_SD_CardInfoTypeDef cardInfo;
    HAL_SD_GetCardInfo(&hsd, &cardInfo);
    printf("Card BlockNbr: %d\r\n", cardInfo.BlockNbr);
    // SDCard_WETest();
    SDCard_FatFS();
}
void SDCard_FatFS(void)
{
    // 文件系统挂载时会对SD卡初始化
    res = f_mount(&fs, "0:", 1);
    /*----------------------- 格式化测试 ---------------------------*/
    /* 如果没有文件系统就格式化创建创建文件系统 */
    if (res == FR_NO_FILESYSTEM) {
        printf("》SD卡还没有文件系统，即将进行格式化...\r\n");
        /* 格式化 */
        res = f_mkfs("0:", 0, sizeof(work));
        if (res == FR_OK) {
            printf("》SD卡已成功格式化文件系统。\r\n");
            /* 格式化后，先取消挂载 */
            res = f_mount(NULL, "0", 1);
            /* 重新挂载 */
            res = f_mount(&fs, "0", 1);
        }
        else {
            printf("《《格式化失败。》》\r\n");
            return;
        }
    }
    else if (res != FR_OK) {
        printf("SD卡挂载文件系统失败(%d)\r\n", res);
        printf("可能原因：SD卡初始化不成功。\r\n");
        return;
    }
    else {
        printf("》文件系统挂载成功，可以进行读写测试\r\n");
    }
    /*--------------------- 文件系统测试：写测试 -----------------------*/
    /* 打开文件，如果文件不存在则创建它 */
    printf("****** 即将进行文件写入测试... ******\r\n");
    res = f_open(&file, "0:hello.txt", FA_CREATE_ALWAYS | FA_WRITE);
    // res = f_open(&file, "0:hello.txt", FA_OPEN_ALWAYS | FA_WRITE);
    if (res == FR_OK) {
        printf("》打开/hello.txt文件成功，向文件写入数据。\r\n");
        /* 将指定存储区内容写入到文件内 */
        res = f_write(&file, WriteBuffer, sizeof(WriteBuffer), &fnum);
        if (res == FR_OK) {
            printf("》文件写入成功，写入字节数据：%d\n", fnum);
            printf("》向文件写入的数据为：\r\n%s\r\n", WriteBuffer);
        }
        else {
            printf("！！文件写入失败：(%d)\n", res);
        }
        /* 不再读写，关闭文件 */
        f_close(&file);
    }
    else {
        printf("！！打开/创建文件失败。\r\n");
    }
    /*------------------ 文件系统测试：读测试 --------------------------*/
    printf("****** 即将进行文件读取测试... ******\r\n");
    res = f_open(&file, "0:hello.txt", FA_OPEN_EXISTING | FA_READ);
    if (res == FR_OK) {
        printf("》打开文件成功。\r\n");
        res = f_read(&file, ReadBuffer, sizeof(ReadBuffer), &fnum);
        if (res == FR_OK) {
            printf("》文件读取成功,读到字节数据：%d\r\n", fnum);
            printf("》读取得的文件数据为：\r\n%s \r\n", ReadBuffer);
        }
        else {
            printf("！！文件读取失败：(%d)\n", res);
        }
    }
    else {
        printf("！！打开文件失败。\r\n");
    }
    /* 不再读写，关闭文件 */
    f_close(&file);

    /* 不再使用文件系统，取消挂载文件系统 */
    f_mount(NULL, "0:", 1);
}
void SDCard_WETest(void)
{
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

