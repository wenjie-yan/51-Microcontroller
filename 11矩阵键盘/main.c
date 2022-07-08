#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"
/**
  * @brief 矩阵键盘读取按键键码
  * @param 无
  * @retval KeyNumber 按下按键的键码值
  */
unsigned char KeyNum;
void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Welcome!");
	while(1)
	{
		KeyNum=MatrixKey();
		if(KeyNum)
		{
			LCD_ShowNum(2,1,KeyNum,2);
		}
	}
}