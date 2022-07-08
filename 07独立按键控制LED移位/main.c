#include <REGX52.H>
char a;
void Delay(unsigned int x)	
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
	P2=~0x01;
	while(1)
	{
		if(P3_1==0)
		{
			Delay(15);
			while(P3_1==0);
			Delay(15);
			a++;
			if(a>=8)
				a=0;
			P2=~(0x01<<a);
		};
		if(P3_0==0)
		{
			Delay(15);
			while(P3_0==0);
			Delay(15);
			if(a==0)
				a=7;
			else
				a--;
			
			P2=~(0x01<<a);
		}					
	}
}