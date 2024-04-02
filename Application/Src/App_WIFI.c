#include "App_WIFI.h"
#include "string.h"
#include "UART_Debug.h"

/**
 *@brief 将WIFI的SSID和密码写入EEPROM，并且连接到WIFI
 * 
 * @param WIFI_SSID 
 * @param WIFI_PASSWORD 
 * @return APP_StatusTypeDef 
 */
APP_StatusTypeDef Wire_Connect_WIFIConfig(const char* WIFI_SSID, const char* WIFI_PASSWORD)
{
    size_t WIFI_SSID_Len = strlen(WIFI_SSID) + 1;
    size_t WIFI_PASSWORD_Len = strlen(WIFI_PASSWORD) + 1;
    I2C_EEPROM_StringWrite(WIFI_SSID_SAVEADDR, WIFI_SSID, WIFI_SSID_Len);
    I2C_EEPROM_StringWrite(WIFI_PASSWORD_SAVEADDR, WIFI_PASSWORD, WIFI_PASSWORD_Len);
    // char pData[WIFI_SSID_Len];
    // char pData2[WIFI_PASSWORD_Len];
    // I2C_EEPROM_StringRead(WIFI_SSID_SAVEADDR, pData, WIFI_SSID_Len);
    // I2C_EEPROM_StringRead(WIFI_PASSWORD_SAVEADDR, pData2, WIFI_PASSWORD_Len);
    // printf("SSID: %s\r\n", pData);
    // printf("Password: %s\r\n", pData2);
    return WIFI_ESP8266_Connect(WIFI_SSID, WIFI_PASSWORD);
    // return APP_OK;
}
