/*
 * serial.h
 *
 *  Created on: 07/07/2015
 *      Author: cuki
 */

#ifndef SERIAL_H_
#define SERIAL_H_

extern int open_port(char *porta);
extern int set_port(int baud_rate, int fd);
extern int make_transaction(int fd, unsigned char *request, unsigned char *response,
		int req_size, int res_size);

#endif /* SERIAL_H_ */
