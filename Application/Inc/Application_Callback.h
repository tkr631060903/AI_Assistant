/**
 * @file Application_Callback.h
 * @author TanKairong (tkr631060903@gmail.com)
 * @brief 中断回调函数
 * @version 0.1
 * @date 2023-12-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Application.h"

#define UART_Cmd_Length 10

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart);
