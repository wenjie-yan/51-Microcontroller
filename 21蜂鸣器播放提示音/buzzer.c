#include <REGX52.H>
#include <INTRINS.H>
//蜂鸣器端口
sbit buzzer=P2^5;
/**
  * @brief 蜂鸣器私有延时函数，延时500us
  * @param 无
  * @retval 无
  */
void Delay500us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}
/**
  * @brief 蜂鸣器鸣响发声函数（1000HZ）
  * @param 时长ms
  * @retval 无
  */
void Buzzer(unsigned int ms)
{
	unsigned int i;
	for(i=0;i<ms*2;i++)
			{
				buzzer=!buzzer;
				Delay500us();
			}
}