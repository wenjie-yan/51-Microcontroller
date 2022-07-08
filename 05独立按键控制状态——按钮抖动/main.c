#include <REGX52.H>
void Delay(unsigned int x)		//@11.0592MHz
{
	unsigned char i, j;
    while(x)
	{
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
		x--;
	}
}

void main()
{
	while(1)
	{
		if(P3_1==0)
		{
			Delay(15);
			while(P3_1==0);
			Delay(15);
			P2_0=~P2_0;
		}
	}
}