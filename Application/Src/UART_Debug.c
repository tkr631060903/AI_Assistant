#include "UART_Debug.h"

extern UART_HandleTypeDef huart1;

/**
 *@brief printf重定义
 * 
 * @param ch 
 * @param f 
 * @return int 
 */
int fputc(int ch, FILE* f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 1000);
  return ch;
}
