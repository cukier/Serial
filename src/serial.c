/*
 * serial.c
 *
 *  Created on: 05/12/2014
 *      Author: cuki
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <stdlib.h>

#include "serial.h"

int main(int argc, char **argv) {

	int fd, n, cont, tentativas;
	unsigned char str[8], buffer[1024];

	if (argc == 1) {
		printf("No Door?\n\r");
		return 1;
	}

	fd = open_port(argv[1]);

	set_port(9600, fd);

	make_request(1, 3, 0, 10, str);

	n = write(fd, str, 8);

	printf("Enviados %d bytes\n\r", n);

	usleep(5000);

//	n = -1;
//	while (n == -1) {
//		n = read(fd, buffer, 1024);
//		tentativas++;
//	}

	printf("lido %d bytes\n\r", n);
	if (n > 0)
		for (cont = 0; cont < n; ++cont)
			printf("0x%X ", str[cont]);
	printf("\n\rTetativas de leitura %d\n\r", tentativas);

	close(fd);

	return 0;

}
