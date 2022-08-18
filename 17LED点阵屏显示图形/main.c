#include <REGX52.H>
#include "Delay.h"

sbit RCK=P3^5;   //RCLK上升沿锁存
sbit SCK=P3^6;   //SRCLK上升沿移位
sbit SER=P3^4;   //串行数据

#define MATRIX_LED_PORT  P0

/**
  * @brief 74HC595写入一个字节
  * @param 写入的8位16进制串行数据
  * @retval 无
  */
void _74HC595_WriteByte(unsigned char byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		SER=byte&(0x80>>i);  //与门，如果Byte最高位为1那么SER为1，相反为0  1111 0000 &1000 0000=1000 0000>1
		SCK=1;    //上升沿移位一次
		SCK=0;
	}
	RCK=1;
	RCK=0;
}

/**
  * @brief LED点阵屏列显示
  * @param Column列数  范围0-7
  * @param Data选择列中的并行数据
  * @retval 无
  */
void MatrixLED_ShowColumn(unsigned char Column,unsigned char Data)
{
	_74HC595_WriteByte(Data);
	MATRIX_LED_PORT=~(0x80>>Column);
	Delay(1);
	MATRIX_LED_PORT=0xFF;
}

void main()
{
	SCK=0;
	RCK=0;
	while(1)
	{
		MatrixLED_ShowColumn(0,0x3C);
		MatrixLED_ShowColumn(1,0x42);
		MatrixLED_ShowColumn(2,0xA9);
		MatrixLED_ShowColumn(3,0x85);
		MatrixLED_ShowColumn(4,0x85);
		MatrixLED_ShowColumn(5,0xA9);
		MatrixLED_ShowColumn(6,0x42);
		MatrixLED_ShowColumn(7,0x3C);
		
	}
}