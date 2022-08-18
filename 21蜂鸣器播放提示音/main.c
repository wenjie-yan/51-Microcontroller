#include <REGX52.H>
#include "Key.h"
#include "Delay.h"
#include "Nixie.h"
#include "buzzer.h"

unsigned char keynum;



void main()
{
	while(1)
	{
		keynum=Key();
		if(keynum)
		{
			Buzzer(100);
			Nixie(1,keynum);
		}
	}
}
