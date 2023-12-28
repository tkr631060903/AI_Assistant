/**
 * @file Application_Callback.c
 * @author TanKairong (tkr631060903@gmail.com)
 * @brief 中断回调函数
 * @version 0.1
 * @date 2023-12-27
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "Application_Callback.h"
#include <string.h>

uint8_t uart1_Cmd[UART_Cmd_Length];
int cmd_Index = 0;

/**
 * @brief 串口中断回调函数
 *
 * @param huart
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
    extern uint8_t Uart1_ReceiveBuff;
    HAL_UART_Transmit(&huart1, &Uart1_ReceiveBuff, 1, 1000);
    uart1_Cmd[cmd_Index] = Uart1_ReceiveBuff;
    cmd_Index++;
    if (cmd_Index > UART_Cmd_Length - 1)
    {
        while (cmd_Index > 0)
        {
            uart1_Cmd[cmd_Index] = 0;
            cmd_Index--;
        }
        uart1_Cmd[0] = 0;
    }
    if (Uart1_ReceiveBuff == '\r')
    {
        printf("\n");
        if (strcmp("rst\r", (char*)uart1_Cmd) == 0)
        {
            printf("SysRest\r\n");
            __set_FAULTMASK(1); //关闭所有中断
            NVIC_SystemReset(); //进行软件复位
        }
        while (cmd_Index > 0)
        {
            uart1_Cmd[cmd_Index] = 0;
            cmd_Index--;
        }
        uart1_Cmd[0] = 0;
    }
    HAL_UART_Receive_IT(&huart1, &Uart1_ReceiveBuff, 1);
}
