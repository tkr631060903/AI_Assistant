#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "Application.h"

#define USE_HORIZONTAL 2  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 135
#define LCD_H 240

#else
#define LCD_W 240
#define LCD_H 135
#endif



//-----------------LCD�˿ڶ���---------------- 

#define LCD_RES_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_1)//RES
#define LCD_RES_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_1)

#define LCD_DC_Clr()   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET)
#define LCD_DC_Set()   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET)

#define LCD_CS_Clr()   GPIO_ResetBits(GPIOA,GPIO_Pin_3)//CS
#define LCD_CS_Set()   GPIO_SetBits(GPIOA,GPIO_Pin_3)

#define LCD_BLK_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_4)//BLK
#define LCD_BLK_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_4)




// void LCD_GPIO_Init(void);//��ʼ��GPIO
void LCD_Writ_Bus(uint8_t dat);//ģ��SPIʱ��
void LCD_WR_DATA8(uint8_t dat);//д��һ���ֽ�
void LCD_WR_DATA(uint16_t dat);//д�������ֽ�
void LCD_WR_REG(uint8_t dat);//д��һ��ָ��
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��
#endif




