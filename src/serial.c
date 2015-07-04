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

int main(int argc, char **argv) {

	int fd, n;
	unsigned char str[9], buffer[1024];

	str[0] = 0x01;
	str[1] = 0x03;
	str[2] = 0x00;
	str[3] = 0x00;
	str[4] = 0x00;
	str[5] = 0x0A;
	str[6] = 0xC5;
	str[7] = 0xCD;
	str[8] = '\0';

	fd = open_port("/dev/ttyS9");

	set_port(19200, fd);

	n = write(fd, str, 8);

	printf("Enviados %d bytes\n\r", n);

	n = read(fd, buffer, 1024);

	printf("lido %d bytes\n\r", n);
	if (n > 0)
		printf("%s\n\r", buffer);

	close(fd);

	return 0;

}
