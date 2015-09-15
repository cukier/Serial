/*
 * serial.h
 *
 *  Created on: 07/07/2015
 *      Author: cuki
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <stdlib.h>

extern int open_port(char *porta);
extern int set_port(int baud_rate, int fd);
extern int make_serial_transaction(int fd, unsigned char *request,
		unsigned char *response, int size);

#endif /* SERIAL_H_ */
