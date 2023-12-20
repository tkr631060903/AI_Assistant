#include "UART_Debug.h"

extern UART_HandleTypeDef huart1;

void UART_Debug_INT(void)
{
  // uint8_t Uart1_ReceiveBuff;
  // HAL_UART_Receive_IT(&huart1, &Uart1_ReceiveBuff, sizeof(Uart1_ReceiveBuff));
  // HAL_UART_Transmit_IT(&huart1, &Uart1_ReceiveBuff, sizeof(Uart1_ReceiveBuff));
  uint8_t ch = 0;
  if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) != RESET)
  {
    ch = (uint16_t)READ_REG(huart1.Instance->DR);
    WRITE_REG(huart1.Instance->DR, ch);
  }
  if (ch == 'r')
  {
    printf("系统复位\r\n");
    __set_FAULTMASK(1); //关闭所有中断
	  NVIC_SystemReset(); //进行软件复位
  }
  
}

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
