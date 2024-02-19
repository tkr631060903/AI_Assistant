/**
 *@file WIFI_ESP8266.c
 * @author TanKairong (tkr631060903@gmail.com)
 * @brief ESP8266驱动基于STM32F103 HAL库编写
 * @version 0.1
 * @date 2024-01-04
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "WIFI_ESP8266.h"
#include <string.h>
#include "UART_Debug.h"

char WIFI_ESP8266_Reply[WIFI_ESP8266_Reply_Length]; //ESP8266应答内容

/**
 *@brief 对ESP8266(UART3)发送AT命令，并可以设置期望返回信息和等待时间
 * 两个期望返回信息为与关系
 * @param AT_Cmd AT命令
 * @param reply1 期望ESP8266返回消息1，为NULL则不期望
 * @param reply2 期望ESP8266返回消息2，为NULL则不期望
 * @param waittime 等待时间ms
 * @return APP_Status
 */
APP_StatusTypeDef WIFI_ESP8266_Cmd(char* AT_Cmd, char* reply1, char* reply2, uint32_t waittime)
{
    char cmd[1];
    strcpy(cmd, AT_Cmd);
    strcat(cmd, "\r\n");
    extern int WIFI_ESP8266_Reply_Index;
    memset(WIFI_ESP8266_Reply, 0, WIFI_ESP8266_Reply_Length);   // 初始化WIFI_ESP8266_Reply，WIFI_ESP8266_Reply全置为0
    WIFI_ESP8266_Reply_Index = 0;
    HAL_UART_Transmit(&huart3, (uint8_t*)cmd, strlen(cmd), 1000);
    // HAL_UART_Transmit(&huart3, (uint8_t*)AT_Cmd, strlen(AT_Cmd), 1000);
    // int AT_Cmd_Length = (int)strlen(AT_Cmd);
    // do {
    //     // HAL_UART_Transmit(&huart1, (uint8_t*)AT_Cmd, sizeof(AT_Cmd), 1000);
    //     // HAL_UART_Transmit(&huart3, (uint8_t*)AT_Cmd, sizeof(AT_Cmd), 1000);
    //     AT_Cmd_Length -= 4;
    //     AT_Cmd += 4;
    // } while (AT_Cmd_Length >= 0);
    if (reply1 == NULL && reply2 == NULL)
    {
        return APP_OK;
    }
    HAL_Delay(waittime);
    printf("WIFI_ESP8266_Reply:%s\r\n", WIFI_ESP8266_Reply);
    if ((strstr(WIFI_ESP8266_Reply, reply1) != NULL) && (strstr(WIFI_ESP8266_Reply, reply2) != NULL))
    {
        return APP_OK;
    }
    else if ((strstr(WIFI_ESP8266_Reply, reply1) != NULL) && (reply2 == NULL)) {
        return APP_OK;

    }
    return APP_ERROR;
}

/**
 *@brief 校验ESP8266
 *
 * @return APP_Status
 */
APP_StatusTypeDef WIFI_ESP8266_Check(void)
{
    HAL_Delay(1000);
    if (WIFI_ESP8266_Cmd("AT\r\n", "OK", NULL, 100) != APP_OK)
    {
        printf("SysRest\r\n");
        __set_FAULTMASK(1); //关闭所有中断
        NVIC_SystemReset(); //进行软件复位
    }
    return APP_OK;
}

#ifdef WIFI_ESP8266_Debug
void WIFI_ESP8266_Test(void)
{
    // HAL_Delay(2000);
    // char AT_Cmd[] = "AT\r\n";
    // HAL_UART_Transmit(&huart3, (uint8_t*)AT_Cmd, sizeof(AT_Cmd), 1000);
    // HAL_UART_Transmit(&huart1, (uint8_t*)AT_Cmd, sizeof(AT_Cmd) - 1, 1000);
    // char AT_RST_CMD[] = "AT+RST\r\n";
    // HAL_UART_Transmit(&huart3, (uint8_t*)AT_RST_CMD, sizeof(AT_RST_CMD), 1000);
    // HAL_UART_Transmit(&huart1, (uint8_t*)AT_RST_CMD, sizeof(AT_RST_CMD) - 1, 1000);
    HAL_Delay(1000);
    APP_StatusTypeDef appStatus;
    // appStatus = WIFI_ESP8266_Cmd("AT\r\n", "OK", NULL, 100);
    // WIFI_ESP8266_Cmd("AT+CWMODE=1\r\n", "OK", NULL, 100);
    // appStatus = WIFI_ESP8266_Cmd("AT+CWMODE?\r\n", "+CWMODE:1", "OK", 100);
    appStatus = WIFI_ESP8266_Cmd("AT", "OK", NULL, 100);
    WIFI_ESP8266_Cmd("AT+CWMODE=1", "OK", NULL, 100);
    appStatus = WIFI_ESP8266_Cmd("AT+CWMODE?", "+CWMODE:1", "OK", 100);
    printf("appStatus:%d\r\n", appStatus);
}
#endif
