/*
 * serial.c
 *
 *  Created on: 05/12/2014
 *      Author: cuki
 */

#include "serial.h"
#include "modbus.h"

int main(int argc, char **argv) {

	int fd, n, cont, ms, tempo_maximo, tentativas, leitura[1024];
	unsigned char str[8], buffer[1024];

	cont = 0;

	if (argc == 1) {
		printf("No Door?\n\r");
		return EXIT_FAILURE;
	} else if (argc == 2) {
		printf("No time?\n\r");
		return EXIT_FAILURE;
	} else if (argc == 3) {
		printf("No tries?");
		return EXIT_FAILURE;
	}

	tempo_maximo = atoi(argv[2]);
	tentativas = atoi(argv[3]);

	fd = open_port(argv[1]);
	set_port(19200, fd);

	printf(
			"Em execucao: porta %s, tempo maximo %s segundos e %s tentativas\n\r",
			argv[1], argv[2], argv[3]);

	make_read_request(1, 0, 10, str);

	for (cont = 0; cont < tentativas; ++cont) {
		printf("Enviados %d bytes", (int) write(fd, str, 8));

		n = -1;
		while ((n == -1) & (ms <= tempo_maximo * 1000)) {
			n = read(fd, buffer, 1024);
			ms++;
			usleep(1000);
			if (ms > tempo_maximo * 1000) {
				printf("Tempo excedido: %ds\r", tempo_maximo);
			}
		}

		leitura[cont] = ms;
		if (ms >= 1000)
			printf(" lido %d bytes em %.3f segundos\r", n, (float) ms / 1000);
		else
			printf(" lido %d bytes em %d milisegundos\r", n, ms);
		ms = 0;
		usleep(100000);
	}

	printf("\n\rTempos lidos:\r");
	for (cont = 0; cont < tentativas; ++cont)
		printf("%.3f ", (float) leitura[cont] / 1000);

	close(fd);

	return EXIT_SUCCESS;
}
