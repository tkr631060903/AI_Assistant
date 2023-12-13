#ifndef __Application_H__
#define __Application_H__

#include "main.h"
#include <stdio.h>
#include "Application_Constant.h"
#include "Application_Init.h"
#include "I2C_EEPROM.h"
#include "SPI_FLASH.h"
#include "SDIO_SDCard.h"

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
