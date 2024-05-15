#include "lcd_init.h"
#include "Application.h"
#include "UART_Debug.h"

extern SPI_HandleTypeDef hspi2;

void delay(uint16_t time)
{
	uint16_t i = 0;
    while (time--)
    {
        i = 9060;  //�Լ�����
        while (i--);
    }
}
/******************************************************************************
	  ����˵����LCD��������д�뺯��
	  ������ݣ�dat  Ҫд��Ĵ�������
	  ����ֵ��  ��
******************************************************************************/
void LCD_Writ_Bus(uint8_t dat)
{
	while (HAL_SPI_GetState(&hspi2) == HAL_SPI_STATE_RESET);//�����ձ�־λ
	HAL_SPI_Transmit(&hspi2, &dat, 1, 10);//����
	// HAL_SPI_Transmit_DMA(&hspi2, &dat, 1);
}

/******************************************************************************
	  ����˵����LCDд������
	  ������ݣ�dat д�������
	  ����ֵ��  ��
******************************************************************************/
void LCD_WR_DATA8(uint8_t dat)
{
	LCD_Writ_Bus(dat);
}


/******************************************************************************
	  ����˵����LCDд������
	  ������ݣ�dat д�������
	  ����ֵ��  ��
******************************************************************************/
void LCD_WR_DATA(uint16_t dat)
{
	LCD_Writ_Bus(dat >> 8);
	LCD_Writ_Bus(dat);
}


/******************************************************************************
	  ����˵����LCDд������
	  ������ݣ�dat д�������
	  ����ֵ��  ��
******************************************************************************/
void LCD_WR_REG(uint8_t dat)
{
	LCD_DC_Clr();//д����
	LCD_Writ_Bus(dat);
	LCD_DC_Set();//д����
}


/******************************************************************************
	  ����˵����������ʼ�ͽ�����ַ
	  ������ݣ�x1,x2 �����е���ʼ�ͽ�����ַ
				y1,y2 �����е���ʼ�ͽ�����ַ
	  ����ֵ��  ��
******************************************************************************/
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	if (USE_HORIZONTAL == 0)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1 + 52);
		LCD_WR_DATA(x2 + 52);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1 + 40);
		LCD_WR_DATA(y2 + 40);
		LCD_WR_REG(0x2c);//������д
	}
	else if (USE_HORIZONTAL == 1)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1 + 53);
		LCD_WR_DATA(x2 + 53);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1 + 40);
		LCD_WR_DATA(y2 + 40);
		LCD_WR_REG(0x2c);//������д
	}
	else if (USE_HORIZONTAL == 2)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1 + 40);
		LCD_WR_DATA(x2 + 40);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1 + 53);
		LCD_WR_DATA(y2 + 53);
		LCD_WR_REG(0x2c);//������д
	}
	else
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1 + 40);
		LCD_WR_DATA(x2 + 40);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1 + 52);
		LCD_WR_DATA(y2 + 52);
		LCD_WR_REG(0x2c);//������д
	}
}

void LCD_Init(void)
{
	// LCD_GPIO_Init();//��ʼ��GPIO
	// SPI1_Init();    //��ʼ��SPI1
	// LCD_RES_Clr();  //��λ
	// delay(100);
	// LCD_RES_Set();
	// delay(100);

	// LCD_BLK_Set();//�򿪱���
	// delay(100);

	LCD_WR_REG(0x11);
	delay(120);
	LCD_WR_REG(0x36);
	if (USE_HORIZONTAL == 0)LCD_WR_DATA8(0x00);
	else if (USE_HORIZONTAL == 1)LCD_WR_DATA8(0xC0);
	else if (USE_HORIZONTAL == 2)LCD_WR_DATA8(0x70);
	else LCD_WR_DATA8(0xA0);

	LCD_WR_REG(0x3A);
	LCD_WR_DATA8(0x05);

	LCD_WR_REG(0xB2);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x33);
	LCD_WR_DATA8(0x33);

	LCD_WR_REG(0xB7);
	LCD_WR_DATA8(0x35);

	LCD_WR_REG(0xBB);
	LCD_WR_DATA8(0x19);

	LCD_WR_REG(0xC0);
	LCD_WR_DATA8(0x2C);

	LCD_WR_REG(0xC2);
	LCD_WR_DATA8(0x01);

	LCD_WR_REG(0xC3);
	LCD_WR_DATA8(0x12);

	LCD_WR_REG(0xC4);
	LCD_WR_DATA8(0x20);

	LCD_WR_REG(0xC6);
	LCD_WR_DATA8(0x0F);

	LCD_WR_REG(0xD0);
	LCD_WR_DATA8(0xA4);
	LCD_WR_DATA8(0xA1);

	LCD_WR_REG(0xE0);
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x2B);
	LCD_WR_DATA8(0x3F);
	LCD_WR_DATA8(0x54);
	LCD_WR_DATA8(0x4C);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x0B);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x23);

	LCD_WR_REG(0xE1);
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x2C);
	LCD_WR_DATA8(0x3F);
	LCD_WR_DATA8(0x44);
	LCD_WR_DATA8(0x51);
	LCD_WR_DATA8(0x2F);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x20);
	LCD_WR_DATA8(0x23);

	LCD_WR_REG(0x21);

	LCD_WR_REG(0x29);
}








