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

int open_port(char *porta) {
	int fd;

	fd = open(porta, O_RDWR | O_NOCTTY | O_NDELAY);

	if (fd == -1) {
		fprintf(stderr, "Problemas ao abrir a porta \"%s\" : %s\n", porta,
				strerror(errno));
		exit(-1);
	}

	return fd;
}

int set_port(int baud_rate, int fd) {
	struct termios options;
	speed_t speed;

	switch (baud_rate) {
	default:
	case 9600:
		speed = B9600;
		break;
	case 19200:
		speed = B19200;
		break;
	}

	tcgetattr(fd, &options);
	cfsetispeed(&options, speed);
	cfsetospeed(&options, speed);
	options.c_cflag |= (CLOCAL | CREAD);
	tcsetattr(fd, TCSANOW, &options);

	return 0;
}

int get_msg_size(char *msg) {
	int cont;
	for (cont = 0; *msg != '\0'; msg++, cont++)
		;

	return cont;
}

int read_port(int fd, char *buffer, int size) {
	int n = read(fd, buffer, size);
	if (n < 0) {
		fputs("read failed!\n", stderr);
		exit(2);
	}
	return (fd);
}

int main(int argc, char **argv) {

	int fd, n, s;
	char str[160];
	char buffer[32];

	if (argc == 1) {
		printf("no door?\n\r");
		exit(1);
	}

	fd = open_port(argv[1]);

	set_port(9600, fd);

	strcpy(str, "\fHelloDude");

	s = get_msg_size(str);

	printf("Tamanho da mensagem %d\n\r", s);

	n = write(fd, str, s);

	printf("Enviados %d bytes\n\r", n);

//	fcntl(fd, F_SETFL, 0);
	printf("Lendo\n\r");
	read_port(fd, buffer, 32);

	printf("Recebido\n\r%s", buffer);

	close(fd);

	return 0;

}
