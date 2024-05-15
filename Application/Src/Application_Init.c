/**
 * @file Application_Init.c
 * @author TanKairong (tkr631060903@gmail.com)
 * @brief 应用初始化
 * @version 0.1
 * @date 2023-12-27
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "Application_Init.h"
#include "Application_Constant.h"
#include "UART_Debug.h"
#include "lcd.h"
#include "lcd_init.h"
#include "pic.h"


uint8_t Uart1_ReceiveBuff = 0;  //串口1接收缓冲区

/**
 * @brief 应用初始化
 *
 */
void Application_Init(void)
{
    // 初始化串口中断输入
    HAL_UART_Receive_IT(&huart1, &Uart1_ReceiveBuff, 1);
    printf("Init Success\r\n");

    float t = 0;
    LCD_Init();
    // LCD_Fill(0, 0, LCD_W, LCD_H, RED);
    LCD_Fill_DMA(0, 0, LCD_W, LCD_H, RED);
    //LED=0;
    uint32_t start = 0;
    uint32_t time = 0;
    // I2C_EEPROM_BuffWrite(0x00, (uint8_t*)gImage_2, 2056);
    uint8_t flag = 0;
    extern uint8_t lcd_whi;
    while (1)
    {
        start = HAL_GetTick();
        LCD_ShowChinese(40, 0, "ABC", RED, WHITE, 32, 0);
        LCD_ShowIntNum(40, 0, time, 3, RED, WHITE, 32);
        LCD_ShowString(10, 33, "LCD_W:", RED, WHITE, 32, 0);
        LCD_ShowIntNum(106, 33, LCD_W, 3, RED, WHITE, 32);
        LCD_ShowString(10, 66, "LCD_H:", RED, WHITE, 32, 0);
        LCD_ShowIntNum(106, 66, LCD_H, 3, RED, WHITE, 32);
        LCD_ShowFloatNum1(10, 99, t, 4, RED, WHITE, 32);
        t += 0.11;
        LCD_ShowPicture(160, 95, 40, 40, gImage_1);
        // LCD_ShowPicture(160,95,32,32,gImage_img);
        // LCD_ShowPicture(0, 0, 222, 135, gImage_qier);
        // if (flag == 0)
        // {
        //     LCD_Fill_DMA(0, 0, LCD_W, LCD_H, BLUE);
        //     printf("bule\n");
        //     flag = 1;
        // }else
        // {
        //     LCD_Fill_DMA(0, 0, LCD_W, LCD_H, WHITE);
        //     printf("white\n");
        //     flag = 0;
        // }
        // LCD_Fill(0, 0, LCD_W, LCD_H, BLUE);
        // LCD_Fill_DMA(0, 0, LCD_W, LCD_H, BLUE);
        time = HAL_GetTick() - start;
        // printf("time = %d\r\n", time);
        // HAL_Delay(3000);
        if (lcd_whi == 1)
        {
            LCD_Fill_DMA(0, 0, LCD_W, LCD_H, BLUE);
            lcd_whi = 0;
        }
    }
}
