#include <REGX52.H>

void Timer_Init()
{
	//TMOD=0x01;    //0000 0001  TMOD不可按位寻址  TCON可按位寻址
	//配置TMOD  高四位为定时器1，低四位为定时器2（GATE C/T M1 M0）分别为（0 0 0 1）
	//GATE 可以选择是由外部和内部一起控制还是只是由TR0控制 这里GATE直接给0由TR0控制
	//C/T 置0为选择定时器  置1为计数器
	//M1 M0选择为0 1 为选择16位模式
	TMOD=TMOD&0xF0;  //把TMOD低四位清零，高四位保持不变
	TMOD=TMOD|0x01;  //把TMOD低四位置1，高四位保持不变
	TF0=0;     //清零防止产生中断
	TR0=1;     //配置定时器工作
	TH0=64535/256;  //256=2^8  就是在二进制里小数点向左移动8位  拿出了高八位
	TL0=64535%256; //这样操作之后就把整个数的高低位分开了
	ET0=1;  //IE   T0的中断允许位
	EA=1;   //IE   总中断允许位
	PT0=0;  //IP   选择低级优先级
}
//void Timer0_Routine() interrupt 1
//{
//	static unsigned int T0Count;
//	TL0=0x18;
//	TH0=0xFC;
//	T0Count++;
//	if(T0Count>=1000)
//	{
//		T0Count=0;
//	}
//}