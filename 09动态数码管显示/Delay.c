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