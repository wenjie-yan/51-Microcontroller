#include <REGX52.H>

sbit DS1302_SCLK=P3^6;
sbit DS1302_IO=P3^4;
sbit DS1302_CE=P3^5;

#define SECOND   0X80
#define MINUTE   0X82
#define HOUR     0X84
#define DATE     0X86
#define MONTH    0X88
#define DAY      0X8A
#define YEAR     0X8C
#define WP       0X8E

 char DS1302_Time[]={22,8,8,16,58,40,1};
/**
  * @brief 时钟初始化
  * @param 无
  * @retval 无
  */
void DS1302_Init(void)
{
	DS1302_CE=0;
	DS1302_SCLK=0;
}	
/**
  * @brief 时钟写入字节
  * @param command命令行，决定输入的地址
  * @param Data数据行，决定填入的数据 BCD码形式
  * @retval 无
  */
void DS1302_WriteByte(unsigned char command,Data)
{
	unsigned char i;
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		DS1302_IO=command&(0x01<<i);
		DS1302_SCLK=1;
		DS1302_SCLK=0;
	}
	for(i=0;i<8;i++)
	{
		DS1302_IO=Data&(0x01<<i);
		DS1302_SCLK=1;
		DS1302_SCLK=0;
	}
	DS1302_CE=0;
}
/**
  * @brief 读取字节，存入Data中
  * @param command读取的地址
  * @retval Data数据
  */
unsigned char DS1302_ReadByte(unsigned char command)
{
	unsigned char i,Data=0x00;
	command |= 0x01;
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		DS1302_IO=command&(0x01<<i);
		DS1302_SCLK=0;
		DS1302_SCLK=1;
	}
	for(i=0;i<8;i++)
	{
		DS1302_SCLK=1;
		DS1302_SCLK=0;
		if(DS1302_IO){Data|=0x01<<i;}
	}
	DS1302_CE=0;
	return Data;
}
/**
  * @brief 设置时间，时间初始化数据在上面的数组中
  * @param 无
  * @retval 无
  */
void DS1302_SetTime()
{
	DS1302_WriteByte(WP,0x00);//关闭写保护
	DS1302_WriteByte(YEAR,DS1302_Time[0]/10*16+DS1302_Time[0]%10);//写入年数据，将16进制转为BCD码
	DS1302_WriteByte(MONTH,DS1302_Time[1]/10*16+DS1302_Time[1]%10);
	DS1302_WriteByte(DATE,DS1302_Time[2]/10*16+DS1302_Time[2]%10);
	DS1302_WriteByte(HOUR,DS1302_Time[3]/10*16+DS1302_Time[3]%10);
	DS1302_WriteByte(MINUTE,DS1302_Time[4]/10*16+DS1302_Time[4]%10);
	DS1302_WriteByte(SECOND,DS1302_Time[5]/10*16+DS1302_Time[5]%10);
	DS1302_WriteByte(DAY,DS1302_Time[6]/10*16+DS1302_Time[6]%10);
//	DS1302_WriteByte(WP,0x80);//打开写保护
}
/**
  * @brief 读取时间，将时间存到TIME数组
  * @param 无
  * @retval 无
  */
void DS1302_ReadTime()
{
	unsigned char temp;
	temp=DS1302_ReadByte(YEAR);
	DS1302_Time[0]=temp/16*10+temp%16;//BCD码转16进制
	temp=DS1302_ReadByte(MONTH);
	DS1302_Time[1]=temp/16*10+temp%16;
	temp=DS1302_ReadByte(DATE);
	DS1302_Time[2]=temp/16*10+temp%16;
	temp=DS1302_ReadByte(HOUR);
	DS1302_Time[3]=temp/16*10+temp%16;
	temp=DS1302_ReadByte(MINUTE);
	DS1302_Time[4]=temp/16*10+temp%16;
	temp=DS1302_ReadByte(SECOND);
	DS1302_Time[5]=temp/16*10+temp%16;
	temp=DS1302_ReadByte(DAY);
	DS1302_Time[6]=temp/16*10+temp%16;
}







