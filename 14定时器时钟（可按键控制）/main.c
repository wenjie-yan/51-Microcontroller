#include <REGX52.H>
#include "LCD1602.h"
#include "timer0.h"
#include "Delay.h"

unsigned char sec=50,min=58,hour=22;
void main()
{
	LCD_Init();
	Timer_Init();
	LCD_ShowString(1,1,"Clock:");
	LCD_ShowString(2,3,":");
		LCD_ShowString(2,6,":");
	while(1)
	{
		LCD_ShowNum(2,1,hour,2);
		LCD_ShowNum(2,4,min,2);
		LCD_ShowNum(2,7,sec,2);
		if(P3_1==0)
			{
				Delay(20);
				while(P3_1==0);
				Delay(20);
				if(hour<=22)
					hour++;
				else
					(hour=0);
			}
		if(P3_0==0)
			{
				Delay(20);
				while(P3_0==0);
				Delay(20);
				if(min<=58)
					min++;
				else
					(min=0);
			}
		if(P3_2==0)
			{
				Delay(20);
				while(P3_2==0);
				Delay(20);
				if(sec<=58)
					sec++;
				else
					(sec=0);
			}
	}
}
void Timer0_Routine() interrupt 1
{
	static int T0count;
	TH0=64535/256;
	TL0=64535%256;
	T0count++;
	if (T0count>=1000)
	{
		T0count=0;
		if(sec<=58)
			sec++;
		else
		{
			if(min<=58)
				min++;
			else
			{
				if(hour<=22)
					hour++;
				else
					hour=0;
				min=0;
			}
			sec=0;
		}
	}
}