/**
 * @file UART_Debug.h
 * @author TanKairong (tkr631060903@gmail.com)
 * @brief uart1调试串口
 * @version 0.1
 * @date 2023-12-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __UART_Debug_H__
#define __UART_Debug_H__

#include "Application.h"

void UART_Debug_INT(void);
int fputc(int ch, FILE* f);

#endif
