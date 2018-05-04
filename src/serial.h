/*
 * serial.h
 *
 *  Created on: 07/07/2015
 *      Author: cuki
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include <stdbool.h>
#include <stdint.h>

extern int open_port(char *porta);
extern int set_port(int baud_rate, int fd);
int make_transaction(int fd, unsigned char *msg, unsigned char *resp,
		int commnad_size);
extern bool check_response(unsigned char *response, unsigned char *request);
int make_read_transaction(int fd, unsigned char *response, int commnad_size);
extern unsigned char * freqtouchar(float frequencie);

#endif /* SERIAL_H_ */
