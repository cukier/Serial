#include "serial.h"

int open_port(char *porta) {
	int fd;

	fd = open(porta, O_RDWR | O_NOCTTY | O_NDELAY);

	if (fd == -1)
		fprintf(stderr, "Problemas ao abrir a porta \"%s\" : %s\n", porta,
				strerror(errno));
	else
		fcntl(fd, F_SETFL, FNDELAY);

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

	if (tcgetattr(fd, &options) == -1)
		return -1;
	if (cfsetispeed(&options, speed) == -1)
		return -1;
	if (cfsetospeed(&options, speed) == -1)
		return -1;

	options.c_cflag |= (CLOCAL | CREAD); //Enable the receiver and set local mode
	options.c_cflag &= ~PARENB; /* Mask the character size to 8 bits, no parity */
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8; /* Select 8 data bits */
	options.c_cflag &= ~CRTSCTS; /* Disable hardware flow control */
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); //Raw Input
	options.c_iflag &= ~(IXON | IXOFF | IXANY); //disable software flow control
	options.c_oflag &= ~OPOST; //Raw output

	if (tcsetattr(fd, TCSANOW, &options) == -1)
		return -1;

	return 0;
}

int make_serial_transaction(int fd, unsigned char *request,
		unsigned char *response, int size) {
	int n;

	write(fd, request, size);
	usleep(300000);
	n = read(fd, response, size);

	if (n != size)
		return -1;

	return 0;
}

