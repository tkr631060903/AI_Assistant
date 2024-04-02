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
APP_StatusTypeDef WIFI_ESP8266_SendCmd(const char* AT_Cmd, const char* reply1, const char* reply2, uint32_t waittime)
{
    char cmd[100];
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
    if (WIFI_ESP8266_SendCmd("AT\r\n", "OK", NULL, 100) != APP_OK)
    {
        printf("SysRest\r\n");
        __set_FAULTMASK(1); //关闭所有中断
        NVIC_SystemReset(); //进行软件复位
    }
    return APP_OK;
}

/**
 *@brief 使用STA模式连接WIFI
 * 
 * @param WIFI_SSID 
 * @param WIFI_PASSWORD 
 * @return APP_StatusTypeDef 
 */
APP_StatusTypeDef WIFI_ESP8266_Connect(const char *WIFI_SSID, const char *WIFI_PASSWORD)
{
    if (WIFI_ESP8266_SendCmd("AT+CWMODE?", "OK", "+CWMODE:1", 100) != APP_OK)
    {
        WIFI_ESP8266_SetMode(STA);
    }
    WIFI_ESP8266_JoinAP(WIFI_SSID, WIFI_PASSWORD);
    return WIFI_ESP8266_SendCmd("AT+CWJAP?", WIFI_SSID, "OK", 100);
}

/**
 *@brief 发送连接WIFI指令
 *
 * @param SSID 连接目标WIFI名称
 * @param PASSWORD 连接目标WIFI密码
 * @return APP_StatusTypeDef
 */
APP_StatusTypeDef WIFI_ESP8266_JoinAP(const char  *SSID, const char *PASSWORD)
{
    char cmd[100];
    sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"", SSID, PASSWORD);
    return WIFI_ESP8266_SendCmd(cmd, "OK", NULL, 5000);
}

/**
 *@brief 设置WIFI模式
 * 
 * @param mode WIFI模式(STA/AP/STA_AP)
 * @return APP_StatusTypeDef 
 */
APP_StatusTypeDef WIFI_ESP8266_SetMode(WIFI_ESP8266_ModeTypeDef mode)
{
    switch (mode)
    {
    case STA:
        WIFI_ESP8266_SendCmd("AT+CWMODE=1", "OK", NULL, 100);
        WIFI_ESP8266_SendCmd("AT+RST", "OK", NULL, 100);
        HAL_Delay(3000);
        return WIFI_ESP8266_SendCmd("AT+CWMODE?", "OK", "+CWMODE:1", 100);
    case AP:
        WIFI_ESP8266_SendCmd("AT+CWMODE=2", "OK", NULL, 100);
        WIFI_ESP8266_SendCmd("AT+RST", "OK", NULL, 100);
        HAL_Delay(3000);
        return WIFI_ESP8266_SendCmd("AT+CWMODE?", "OK", "+CWMODE:2", 100);
    case STA_AP:
        WIFI_ESP8266_SendCmd("AT+CWMODE=3", "OK", NULL, 100);
        WIFI_ESP8266_SendCmd("AT+RST", "OK", NULL, 100);
        HAL_Delay(3000);
        return WIFI_ESP8266_SendCmd("AT+CWMODE?", "OK", "+CWMODE:3", 100);
    default:
        return APP_ERROR;
    }
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
    // appStatus = WIFI_ESP8266_SendCmd("AT\r\n", "OK", NULL, 100);
    // WIFI_ESP8266_SendCmd("AT+CWMODE=1\r\n", "OK", NULL, 100);
    // appStatus = WIFI_ESP8266_SendCmd("AT+CWMODE?\r\n", "+CWMODE:1", "OK", 100);
    // appStatus = WIFI_ESP8266_SendCmd("AT", "OK", NULL, 100);
    // WIFI_ESP8266_SendCmd("AT+CWMODE=1", "OK", NULL, 100);
    // appStatus = WIFI_ESP8266_SendCmd("AT+CWMODE?", "+CWMODE:1", "OK", 100);
    // printf("appStatus:%d\r\n", appStatus);
    char WIFI_SSID[] = "iQOONeo5";
    char WIFI_PASSWORD[] = "rong19980521";
    if (WIFI_ESP8266_SendCmd("AT+CWJAP?", WIFI_SSID, "OK", 100) != APP_OK)
    {
        appStatus = WIFI_ESP8266_Connect(WIFI_SSID, WIFI_PASSWORD);
        printf("appStatus:%d\r\n", appStatus);
    }
    WIFI_ESP8266_SendCmd("AT+CIPSTATUS", "OK", NULL, 100);
}
#endif
