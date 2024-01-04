/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SPI_FLASH_CS_Pin GPIO_PIN_0
#define SPI_FLASH_CS_GPIO_Port GPIOC
#define SPI_FLASH_SCK_Pin GPIO_PIN_5
#define SPI_FLASH_SCK_GPIO_Port GPIOA
#define SPI_FLASH_MISO_Pin GPIO_PIN_6
#define SPI_FLASH_MISO_GPIO_Port GPIOA
#define SPI_FLASH_MOSI_Pin GPIO_PIN_7
#define SPI_FLASH_MOSI_GPIO_Port GPIOA
#define LED_G_Pin GPIO_PIN_0
#define LED_G_GPIO_Port GPIOB
#define LED_B_Pin GPIO_PIN_1
#define LED_B_GPIO_Port GPIOB
#define WIFI_UART_TX_Pin GPIO_PIN_10
#define WIFI_UART_TX_GPIO_Port GPIOB
#define WIFI_UART_RX_Pin GPIO_PIN_11
#define WIFI_UART_RX_GPIO_Port GPIOB
#define SDIO_SDCARD_D0_Pin GPIO_PIN_8
#define SDIO_SDCARD_D0_GPIO_Port GPIOC
#define SDIO_SDCARD_D1_Pin GPIO_PIN_9
#define SDIO_SDCARD_D1_GPIO_Port GPIOC
#define DEBUG_USART_TX_Pin GPIO_PIN_9
#define DEBUG_USART_TX_GPIO_Port GPIOA
#define DEBUG_USART_RX_Pin GPIO_PIN_10
#define DEBUG_USART_RX_GPIO_Port GPIOA
#define SDIO_SDCARD_D2_Pin GPIO_PIN_10
#define SDIO_SDCARD_D2_GPIO_Port GPIOC
#define SDIO_SDCARD_D3_Pin GPIO_PIN_11
#define SDIO_SDCARD_D3_GPIO_Port GPIOC
#define SDIO_SDCARD_CK_Pin GPIO_PIN_12
#define SDIO_SDCARD_CK_GPIO_Port GPIOC
#define SDIO_SDCARD_CMD_Pin GPIO_PIN_2
#define SDIO_SDCARD_CMD_GPIO_Port GPIOD
#define LED_R_Pin GPIO_PIN_5
#define LED_R_GPIO_Port GPIOB
#define I2C_EEPROM_SCL_Pin GPIO_PIN_6
#define I2C_EEPROM_SCL_GPIO_Port GPIOB
#define I2C_EEPROM_SDA_Pin GPIO_PIN_7
#define I2C_EEPROM_SDA_GPIO_Port GPIOB
#define WIFI_ESP8266_EN_Pin GPIO_PIN_8
#define WIFI_ESP8266_EN_GPIO_Port GPIOB
#define WIFI_ESP8266_RST_Pin GPIO_PIN_9
#define WIFI_ESP8266_RST_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
