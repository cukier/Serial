/*
 * modbus.h
 *
 *  Created on: 08/07/2015
 *      Author: cuki
 */

#ifndef MODBUS_H_
#define MODBUS_H_

#define READ_MULTIPLE_REGISTERS		0x03
#define WRITE_SINGLE_REGISTER		0X06
#define WRITE_MULTIPLE_REGISTERS	0x0A

unsigned short CRC16(const unsigned char *nData, unsigned short wLength);
unsigned char getByte(unsigned short word, int offset);
int make_write_request(int addr, int reg, int value, unsigned char *request);
int make_read_request(int addr, int from, int to, unsigned char *request);

#endif /* MODBUS_H_ */
