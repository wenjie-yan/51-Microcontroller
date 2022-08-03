#include <REGX52.H>
#include "timer0.h"
#include "key.h"
#include <INTRINS.H>
unsigned char keynum ,LEDMode;

void main()
{	P2=0xFE;
	Timer_Init(); //定时器初始化
	while(1)
	{
		keynum=key();
		if(keynum)
		{
			if(keynum==1)
			{
				LEDMode++;
				if(LEDMode>=2)LEDMode=0;
			}
		
		}
	}
}
 
void Timer0_Routine() interrupt 1
{
	static int T0count;
	TH0=64535/256;
	TL0=64535%256;
	T0count++;
	if (T0count>=500)
	{
		T0count=0;
		if(LEDMode==0)
			P2=_crol_(P2,1);
		if(LEDMode==1)
			P2=_cror_(P2,1);
	}
}





