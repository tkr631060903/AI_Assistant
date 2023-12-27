/**
 * @file Application_RTOS.c
 * @author TanKairong (tkr631060903@gmail.com)
 * @brief 应用操作系统任务
 * @version 0.1
 * @date 2023-12-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Application_RTOS.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

extern UART_HandleTypeDef huart1;

void myTask(void* argument)
{
    vTaskDelete(NULL);
    while (1)
    {
        HAL_UART_Transmit(&huart1, (uint8_t*)"myTask\r\n", sizeof("myTask\r"), 1000);
        HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
        vTaskDelay(2000);
    }

}
