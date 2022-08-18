#include <REGX52.H>
#include "I2C.h"
/**
  * @brief 給AT24C02发送字节
  * @param byte发送的字节
  * @param address发送的地址，范围0~256
  * @retval 无
  */
void AT24C02_sendbyte(unsigned char byte,address)
{
	I2C_start();
	I2C_sendbyte(0xA0);
	I2C_receiveack();
	I2C_sendbyte(address);
	I2C_receiveack();
	I2C_sendbyte(byte);
	I2C_receiveack();
	I2C_end();
}
/**
  * @brief 读取ROM中的数据
  * @param 地址
  * @retval 数据
  */
unsigned char AT24C02_readbyte(unsigned char address)
{
	unsigned char byte;
	I2C_start();
	I2C_sendbyte(0xA0);
	I2C_receiveack();
	I2C_sendbyte(address);
	I2C_receiveack();
	I2C_start();
	I2C_sendbyte(0xA1);
	I2C_receiveack();
	byte=I2C_receivebyte();
	I2C_sendack(1);
	I2C_end();
	return byte;
}