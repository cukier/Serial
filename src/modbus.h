/*
 * modbus.h
 *
 *  Created on: 08/07/2015
 *      Author: cuki
 */

#ifndef MODBUS_H_
#define MODBUS_H_

unsigned short CRC16(const unsigned char *nData, unsigned short wLength);
unsigned char getByte(unsigned short word, int offset);
int make_request(int addr, int cmd, int from, int to, unsigned char *request);

#endif /* MODBUS_H_ */
