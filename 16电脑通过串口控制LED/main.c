#include <REGX52.H>
#include "Delay.h"
#include "UART.h"

void main()
{
	UNIT_Init();
	while(1)
	{
		
	}
}

void UART_routine() interrupt 4
{
	if(RI==1)
	{
		P2=SBUF;
		UART_sendbyte(SBUF);
		RI=0;
	}
}