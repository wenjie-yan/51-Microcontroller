#include <REGX52.H>

sbit SCL=P2^1;
sbit SDA=P2^0;

/**
  * @brief I2C通讯开始标志
  * @param 无
  * @retval 无
  */
void I2C_start()
{
	SCL=1;
	SDA=1;
	SDA=0;
	SCL=0;
}
/**
  * @brief I2C通讯结束标志
  * @param 无
  * @retval 无
  */
void I2C_end()
{
	SCL=0;
	SDA=0;
	SCL=1;
	SDA=1;
}
/**
  * @brief 发送一个字节
  * @param byte发送的字节
  * @retval 无
  */
void I2C_sendbyte(unsigned char byte)
{
	int i;
	for(i=0;i<8;i++)
	{
		SDA=byte&(0x80>>i);
		SCL=1;
		SCL=0;
	}
}
/**
  * @brief 接受字节
  * @param 无
  * @retval byte接受的字节
  */
unsigned char I2C_receivebyte()
{
	unsigned char byte=0x00;
	int i;
	SDA=1;//接收数据之前，主机要释放SDA数据线
	for(i=0;i<8;i++)
	{
		SCL=1;
		if(SDA)
		{
			byte|=(0x80>>i);
		}
		SCL=0;
	}
	return byte;
}
/**
  * @brief 发送应答
  * @param ack发送的应答
  * @retval 无
  */
void I2C_sendack(unsigned char ack)
{
	SDA=ack;
	SCL=1;
	SCL=0;
}
/**
  * @brief 接受应答
  * @param 无
  * @retval 接受的应答
  */
unsigned char I2C_receiveack()
{
	unsigned char ack=0;
	SDA=1;
	SCL=1;
	if(SDA)
	{
		ack=1;
	}
	SCL=0;
	return ack;
}