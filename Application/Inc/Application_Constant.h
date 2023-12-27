/**
 * @file Application_Constant.h
 * @author TanKairong (tkr631060903@gmail.com)
 * @brief 全局常量定义
 * @version 0.1
 * @date 2023-12-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __Application_Constant_H__
#define __Application_Constant_H__

typedef enum
{
  APP_OK       = 0x00U,
  APP_ERROR    = 0x01U,
  APP_BUSY     = 0x02U,
  APP_TIMEOUT  = 0x03U
} APP_StatusTypeDef;

#endif
