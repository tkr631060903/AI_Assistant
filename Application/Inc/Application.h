/**
 * @file Application.h
 * @author TanKairong (tkr631060903@gmail.com)
 * @brief 应用入口
 * @version 0.1
 * @date 2023-12-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __Application_H__
#define __Application_H__

#include "main.h"

// 定义结构体类型
// typedef struct
// {
// 	void (*Application_main)(void);
// 	void (*Application_Error_Handler)(void);
// 	void (*Application_Assert_Failed)(void);
// } Application_t;

// extern Application_t Application;

void Application_main(void); 
void Application_Error_Handler(void);
void Application_Assert_Failed(void);

#endif
