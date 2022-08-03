#include <REGX52.H>
#include "Delay.h"
#include "UART.h"
unsigned char sec=0;
void main()
{
	UNIT_Init();
	while(1)
	{
		UART_sendbyte(sec);
		Delay(1000);
		sec++;
	}
}