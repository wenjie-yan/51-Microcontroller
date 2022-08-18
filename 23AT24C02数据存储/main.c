#include <REGX52.H>
#include "AT24C02.h"
#include "LCD1602.h"
#include "key.h"
#include "Delay.h"

unsigned int num;
unsigned char keynum;
unsigned char Data;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"NUMBER BANK!");
	while(1)
	{
		keynum=key();
		LCD_ShowNum(2,1,num,2);
		if(keynum==1){num++;LCD_ShowString(2,12,"      ");}
		if(keynum==2 && num>=1){num--;LCD_ShowString(2,12,"      ");}
			else if(keynum==2 && num==0){LCD_ShowString(2,12,"ERROR!");}
		if(keynum==3)
			{
				AT24C02_sendbyte(num,0);
				Delay(5);
				LCD_ShowString(2,8,"WRITE OK!");
				Delay(2000);
				LCD_ShowString(2,8,"         ");
			}
		if(keynum==4)
			{
				Data=AT24C02_readbyte(0);
				LCD_ShowString(2,9,"READ OK!");
				LCD_ShowNum(2,5,Data,2);
				Delay(2000);
				LCD_ShowString(2,9,"        ");
			}
	}
}