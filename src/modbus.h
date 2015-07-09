/*
 * modbus.h
 *
 *  Created on: 08/07/2015
 *      Author: cuki
 */

#ifndef MODBUS_H_
#define MODBUS_H_

typedef struct pre_req_str {
	unsigned char addr;
	unsigned char cmd;
	unsigned char from_h;
	unsigned char from_l;
	unsigned char to_h;
	unsigned char to_l;
} pre_req_type;

typedef union pre_req_un {
	pre_req_type data;
	unsigned char str[6];
} pre_req_un_type;

unsigned short CRC16(const unsigned char *nData, unsigned short wLength);
unsigned char getByte(unsigned short word, int offset);
int make_request(int addr, int cmd, int from, int to, unsigned char *request);

#endif /* MODBUS_H_ */
