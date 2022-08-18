#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Delay.h"
#include "key.h"
#include "timer0.h"

unsigned char keynum,MODE,timesetselect,flage;

void timeshow()
{
		DS1302_ReadTime();
		LCD_ShowNum(1,1,DS1302_Time[0],2);
		LCD_ShowNum(1,4,DS1302_Time[1],2);
		LCD_ShowNum(1,7,DS1302_Time[2],2);
		LCD_ShowNum(2,1,DS1302_Time[3],2);
		LCD_ShowNum(2,4,DS1302_Time[4],2);
		LCD_ShowNum(2,7,DS1302_Time[5],2);
}

void timeset()
{
	
	if(keynum==2)
	{
		timesetselect++;
		timesetselect%=6;
	}
	if(keynum==3)
	{
		DS1302_Time[timesetselect]++;
		if(DS1302_Time[0]>99){DS1302_Time[0]=0;}
		if(DS1302_Time[1]>12){DS1302_Time[1]=1;}
		if(DS1302_Time[1]==1 || DS1302_Time[1]==3 || DS1302_Time[1]==5 || 
			DS1302_Time[1]==7 || DS1302_Time[1]==8 || DS1302_Time[1]==12)
		{
			if(DS1302_Time[2]>31){DS1302_Time[2]=1;}
		}
		else if(DS1302_Time[1]==4 || DS1302_Time[1]==6 || DS1302_Time[1]==9 || 
			DS1302_Time[1]==11 )
		{
			if(DS1302_Time[2]>30){DS1302_Time[2]=1;}
		}
		else if(DS1302_Time[1]==2)
		{
			if(DS1302_Time[0]%4==0)
			{
				if(DS1302_Time[2]>29){DS1302_Time[2]=1;}
			}
			else
			{
				if(DS1302_Time[2]>28){DS1302_Time[2]=1;}
			}
		}
		if(DS1302_Time[3]>23){DS1302_Time[3]=0;}
		if(DS1302_Time[4]>59){DS1302_Time[4]=0;}
		if(DS1302_Time[5]>59){DS1302_Time[5]=0;}
		
	}
	if(keynum==4)
	{
		DS1302_Time[timesetselect]--;
		if(DS1302_Time[0]<0){DS1302_Time[0]=99;}
		if(DS1302_Time[1]<1){DS1302_Time[1]=12;}
		if(DS1302_Time[1]==1 || DS1302_Time[1]==3 || DS1302_Time[1]==5 || 
			DS1302_Time[1]==7 || DS1302_Time[1]==8 || DS1302_Time[1]==12)
		{
			if(DS1302_Time[2]<1){DS1302_Time[2]=31;}
			if(DS1302_Time[2]>31){DS1302_Time[2]=1;}
		}
		else if(DS1302_Time[1]==4 || DS1302_Time[1]==6 || DS1302_Time[1]==9 || 
			DS1302_Time[1]==11 )
		{
			if(DS1302_Time[2]<1){DS1302_Time[2]=30;}
			if(DS1302_Time[2]>30){DS1302_Time[2]=1;}
		}
		else if(DS1302_Time[1]==2)
		{
			if(DS1302_Time[0]%4==0)
			{
				if(DS1302_Time[2]<1){DS1302_Time[2]=29;}
				if(DS1302_Time[2]>29){DS1302_Time[2]=1;}
			}
			else
			{
				if(DS1302_Time[2]<1){DS1302_Time[2]=28;}
				if(DS1302_Time[2]>28){DS1302_Time[2]=1;}
			}
		}
		if(DS1302_Time[3]<0){DS1302_Time[3]=23;}
		if(DS1302_Time[4]<0){DS1302_Time[4]=59;}
		if(DS1302_Time[5]<0){DS1302_Time[5]=59;}
	}
	if(timesetselect==0 && flage==1){LCD_ShowString(1,1,"  ");}
	else{LCD_ShowNum(1,1,DS1302_Time[0],2);}
	if(timesetselect==1 && flage==1){LCD_ShowString(1,4,"  ");}
	else{LCD_ShowNum(1,4,DS1302_Time[1],2);}
	if(timesetselect==2 && flage==1){LCD_ShowString(1,7,"  ");}
	else{LCD_ShowNum(1,7,DS1302_Time[2],2);}
	if(timesetselect==3 && flage==1){LCD_ShowString(2,1,"  ");}
	else{LCD_ShowNum(2,1,DS1302_Time[3],2);}
	if(timesetselect==4 && flage==1){LCD_ShowString(2,4,"  ");}
	else{LCD_ShowNum(2,4,DS1302_Time[4],2);}
	if(timesetselect==5 && flage==1){LCD_ShowString(2,7,"  ");}
	else{LCD_ShowNum(2,7,DS1302_Time[5],2);}
	LCD_ShowNum(1,16,timesetselect,1);
	LCD_ShowNum(2,16,flage,1);

}

void main()
{
	LCD_Init();
	DS1302_Init();
	Timer_Init();
	LCD_ShowString(1,1,"  -  -  ");
	LCD_ShowString(2,1,"  :  :  ");
	DS1302_SetTime();
	
	while(1)
	{
		keynum=key();
		if(keynum==1)
		{
			if(MODE==0){MODE=1;}
			else if(MODE==1){MODE=0;DS1302_SetTime();DS1302_WriteByte(0X8E,0x80);}
		}
		switch(MODE)
		{
			case 0:timeshow();break;
			case 1:timeset();break;
		}
	}
}

void timerroutine()  interrupt 1
{
	static unsigned int T0Count;
	TL0=0x18;
	TH0=0xFC;
	T0Count++;
	if(T0Count>=500)
	{
		T0Count=0;
		flage=!flage;
	}
}







