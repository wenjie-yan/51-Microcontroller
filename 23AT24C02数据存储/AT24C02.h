#ifndef _AT24C02_H_
#define _AT24C02_H_

void AT24C02_sendbyte(unsigned char byte,address);
unsigned char AT24C02_readbyte(unsigned char address);

#endif