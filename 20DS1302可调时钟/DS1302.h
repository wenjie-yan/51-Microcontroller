#ifndef _DS1302_H_
#define _DS1302_H_

	extern unsigned char DS1302_Time[];
	void DS1302_Init(void);
	void DS1302_WriteByte(unsigned char command,Data);
	unsigned char DS1302_ReadByte(unsigned char command);
	void DS1302_SetTime();
	void DS1302_ReadTime();
	
#endif