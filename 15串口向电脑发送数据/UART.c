#include <REGX52.H>

/**
  * @brief 串口初始化
  * @param 无
  * @retval 无
  */
void UNIT_Init()
{
	SCON=0x40;   //0100 0000 该寄存器控制（SM0 SM1 REN TB8 RB8 TI RI）
	//SM0 SM1取01选择方式一，即8位UART波特率可变模式
	//REN位是决定是否可以接收
	//TB8 RB8是方式2，3不需配置
	//TI RI为是否发送中断请求，发送时机器自动置1，需手动置0
	PCON |= 0x80;
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xF4;		//设置定时初始值
	TH1 = 0xF4;		//设置定时重载值
	ET1=0;			//禁止定时器1中断
	TR1 = 1;		//定时器1开始计时
}
/**
  * @brief 串口发送一个字节数据
* @param Byte为发送的数据
  * @retval 无
  */
void UART_sendbyte(unsigned char byte)
{
	SBUF=byte;
	while(TI==0);
	TI=0;
}
