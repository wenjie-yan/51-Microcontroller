#ifndef _I2C_H_
#define _I2C_H_

void I2C_start();
void I2C_end();
void I2C_sendbyte(unsigned char byte);
unsigned char I2C_receivebyte();
void I2C_sendack(unsigned char ack);
unsigned char I2C_receiveack();

#endif