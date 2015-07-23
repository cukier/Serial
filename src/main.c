/*
 * serial.c
 *
 *  Created on: 05/12/2014
 *      Author: cuki
 */

#include "serial.h"
#include "modbus.h"

int main(int argc, char **argv) {

	int fd, n, cont, tentativas;
	unsigned char str[8], buffer[1024];

	if (argc == 1) {
		printf("No Door?\n\r");
		return EXIT_FAILURE;
	}

	fd = open_port(argv[1]);
	set_port(19200, fd);

	make_request(1, 3, 0, 10, str);

	write(fd, str, 8);
	printf("Enviados %d bytes\n\r", n);
	n = -1;
	while (n == -1) {
		n = read(fd, buffer, 1024);
		tentativas++;
		usleep(1000);
		if (tentativas > 10000) {
			printf("Número de tentativas excedeu 10s\n\r");
			return EXIT_FAILURE;
		}
	}

	printf("lido %d bytes\n\r", n);
	if (n > 0)
		for (cont = 0; cont < n; ++cont)
			printf("0x%X ", buffer[cont]);
	printf("\n\rTetativas de leitura %.3f segundos\n\r",
			(float) tentativas / 1000);
	close(fd);

	return EXIT_SUCCESS;
}
