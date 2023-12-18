#include "SPI_FLASH.h"

extern SPI_HandleTypeDef hspi1;

/**
 *@brief 发送一个字节数据
 * 
 * @param byte 待发送数据
 * @return 接收到的数据 
 */
uint8_t SPI_FLASH_SendByte(uint8_t byte)
{
  uint8_t data = 0;
  HAL_SPI_GetState(&hspi1);
  // status = HAL_SPI_TransmitReceive(&hspi1, &byte, &data, 1, 1000);
  HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_DMA(&hspi1, &byte, &data, 1);
  while (status != HAL_OK)
  {
  }
  //  status = HAL_SPI_Transmit(&hspi1, &byte, 1, 1000);
  // // status = HAL_SPI_Transmit_DMA(&hspi1, &byte, sizeof(&byte));
  // while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_TX_RX || status != HAL_OK)
  // {
  // }
  // status = HAL_SPI_Receive(&hspi1, &data, 1, 1000);
  // // status = HAL_SPI_Receive_DMA(&hspi1, &data, sizeof(&data));
  // while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_TX_RX || status != HAL_OK)
  // {
  // }
  return data;
}

/**
 *@brief 校验FLASH ID
 * 
 * @return APP_Status
 */
APP_StatusTypeDef SPI_FLASH_BufferReadJEDECID(void)
{
  uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

  SPI_FLASH_CS_LOW;

  SPI_FLASH_SendByte(W25X_JedecDeviceID);
  Temp0 = SPI_FLASH_SendByte(W25X_Dummy_Byte);
  Temp1 = SPI_FLASH_SendByte(W25X_Dummy_Byte);
  Temp2 = SPI_FLASH_SendByte(W25X_Dummy_Byte);

  SPI_FLASH_CS_HIGH;
  Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;
  printf("0x%x\r\n", Temp);
  if (Temp == W25Q64_FLASH_ID)
  {
    return APP_OK;
  }
  return APP_ERROR;
}

/**
 *@brief 校验FLASH外设
 * 
 * @return APP_Status
 */
APP_StatusTypeDef SPI_FLASH_Check(void)
{
  uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;
  SPI_FLASH_CS_LOW;
  SPI_FLASH_SendByte(W25X_JedecDeviceID);
  Temp0 = SPI_FLASH_SendByte(W25X_Dummy_Byte);
  Temp1 = SPI_FLASH_SendByte(W25X_Dummy_Byte);
  Temp2 = SPI_FLASH_SendByte(W25X_Dummy_Byte);
  SPI_FLASH_CS_HIGH;
  Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;
  if (Temp == W25Q64_FLASH_ID)
  {
    return APP_OK;
  }
  return APP_ERROR;
}

/**
 *@brief FLASH全片擦除
 * 
 */
void SPI_FLASH_ChipSector(void)
{
  SPI_FLASH_WriteEnable();
  SPI_FLASH_WaitForWriteEnd();
  SPI_FLASH_CS_LOW;
  SPI_FLASH_SendByte(W25X_ChipErase);
  SPI_FLASH_WaitForWriteEnd();
  SPI_FLASH_CS_HIGH;
}

/**
 * @brief 等待FLASH程序、擦除、写入完成
 * 
 */
void SPI_FLASH_WaitForWriteEnd(void)
{
  SPI_FLASH_CS_LOW;
  SPI_FLASH_SendByte(W25X_ReadStatusReg);
  while (SPI_FLASH_SendByte(W25X_Dummy_Byte) & 0x01);
  {
    printf("wait for write end\r\n");
  }
  SPI_FLASH_CS_HIGH;
}

/**
 *@brief FLASH写使能
 * 
 */
void SPI_FLASH_WriteEnable(void)
{
  SPI_FLASH_CS_LOW;
  SPI_FLASH_SendByte(W25X_WriteEnable);
  SPI_FLASH_CS_HIGH;
}

/**
 *@brief FLASH写入禁用
 * 
 */
void SPI_FLASH_WriteDisable(void)
{
  SPI_FLASH_CS_LOW;
  SPI_FLASH_SendByte(W25X_WriteDisable);
  SPI_FLASH_CS_HIGH;
}

/**
 *@brief FLASH扇区擦除,擦除4KB存储空间
 * 
 * @param SectorAddr 需擦除的扇区地址
 */
void SPI_FLASH_SectorSector(uint32_t SectorAddr)
{
  SPI_FLASH_WriteEnable();
  SPI_FLASH_WaitForWriteEnd();
  SPI_FLASH_CS_LOW;
  /* 发送扇区擦除指令*/
  SPI_FLASH_SendByte(W25X_SectorErase);
  /*发送擦除扇区地址的高位*/
  SPI_FLASH_SendByte((SectorAddr & 0xFF0000) >> 16);
  /* 发送擦除扇区地址的中位 */
  SPI_FLASH_SendByte((SectorAddr & 0xFF00) >> 8);
  /* 发送擦除扇区地址的低位 */
  SPI_FLASH_SendByte(SectorAddr & 0xFF);
  SPI_FLASH_CS_HIGH;
  SPI_FLASH_WaitForWriteEnd();
}

/**
 *@brief 页写入,需要先进行擦除
 * 
 * @param pBuffer 写入数据缓冲区
 * @param WriteAddr 写入起始地址
 * @param NumByteToWrite 写入数据个数
 */
void SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
  if (NumByteToWrite > SPI_FLASH_PageSize)
  {
    printf("error: NumByteToWrite > SPI_FLASH_PageSize\r\n");
    return;
  }
  SPI_FLASH_WriteEnable();
  SPI_FLASH_WaitForWriteEnd();
  SPI_FLASH_CS_LOW;
  SPI_FLASH_SendByte(W25X_PageProgram);
  /* 发送写入起始地址的高位 */
  SPI_FLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
  /* 发送写入起始地址的中位 */
  SPI_FLASH_SendByte((WriteAddr & 0xFF00) >> 8);
  /* 发送写入起始地址的低位 */
  SPI_FLASH_SendByte(WriteAddr & 0xFF);
  while (NumByteToWrite--)
  {
    SPI_FLASH_SendByte(*pBuffer);
    pBuffer++;
  }
  SPI_FLASH_CS_HIGH;
  SPI_FLASH_WaitForWriteEnd();
}

/**
 *@brief 写数据,需要先进行擦除
 * 
 * @param pBuffer 写入数据缓冲区
 * @param WriteAddr 写入起始地址
 * @param NumByteToWrite 写入数据个数
 */
void SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
  uint8_t pageCount, addr, dataCount, addrCount;
  // 计算要写入多少页数据
  pageCount = NumByteToWrite / SPI_FLASH_PageSize;
  // 计算写入地址是否对齐页的起始地址
  addr = WriteAddr % SPI_FLASH_PageSize;
  // 计算剩余不满一页的字节数
  dataCount = NumByteToWrite % SPI_FLASH_PageSize;
  // 计算剩余多少数据能对齐到页地址，当前页还能写入多少数据
  addrCount = SPI_FLASH_PageSize - addr;
  if (addr == 0)
  {
    // 刚好页对齐
    if (pageCount == 0)
    {
      // 数据 ≤ 页大小，直接写入
      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
    }
    else
    {
      // 先将整页写入
      while (pageCount--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr += SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }
      // 再将剩余的数据写入
      SPI_FLASH_PageWrite(pBuffer, WriteAddr, dataCount);
    }
  }
  // 起始地址与SPI_FLASH_PageSize 不对齐
  else
  {
    // 刚好页对齐
    if (pageCount == 0)
    {
      if (dataCount > addrCount)
      {
        // 当前页写不完数据，先写满当前页
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, addrCount);
        // 写入剩下数据
        WriteAddr += addrCount;
        pBuffer += addrCount;
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, dataCount - addrCount);
      }
      else
      {
        // 当前页能写完数据
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else
    {
      // 写入数据多于当前页空间，先写满当前页
      NumByteToWrite -= addrCount;
      SPI_FLASH_PageWrite(pBuffer, WriteAddr, addrCount);
      WriteAddr += addrCount;
      pBuffer += addrCount;
      // 写入剩下整页数据
      pageCount = NumByteToWrite / SPI_FLASH_PageSize;
      while (pageCount--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr += SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }
      // 计算是否还有不满一页的数据
      dataCount = NumByteToWrite % SPI_FLASH_PageSize;
      if (dataCount != 0)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, dataCount);
      }
    }

  }
}

/**
 *@brief 读数据
 * 
 * @param pBuffer 读取数据缓冲区
 * @param ReadAddr 读取数据起始地址
 * @param NumByteToRead 读取数据个数
 */
void SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
  SPI_FLASH_CS_LOW;
  SPI_FLASH_SendByte(W25X_ReadData);
  /* 发送写入起始地址的高位 */
  SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
  /* 发送写入起始地址的中位 */
  SPI_FLASH_SendByte((ReadAddr & 0xFF00) >> 8);
  /* 发送写入起始地址的低位 */
  SPI_FLASH_SendByte(ReadAddr & 0xFF);
  while (NumByteToRead--)
  {
    *pBuffer = SPI_FLASH_SendByte(W25X_Dummy_Byte);
    pBuffer++;
  }
  SPI_FLASH_CS_HIGH;
}

void SPI_FLASH_Test(void)
{
  SPI_FLASH_SectorSector(0x123456);
  uint32_t FLASH_WriteAddress = 0x123456;
  uint16_t BufferSize = 64;
  uint8_t Tx_Buffer[64];
  for (uint8_t i = 0; i < BufferSize; i++) {
    Tx_Buffer[i] = i;
  }
  // SPI_FLASH_PageWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);
  SPI_FLASH_BufferWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);
  uint8_t Rx_Buffer[64];
  SPI_FLASH_BufferRead(Rx_Buffer, FLASH_WriteAddress, BufferSize);
  for (uint8_t i = 0; i < BufferSize; i++) {
    printf("0x%02X ", Rx_Buffer[i]);
  }
}
