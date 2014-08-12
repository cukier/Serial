/*
 * repetidor.c
 *
 *  Created on: 12/08/2014
 *      Author: cuki
 */

#include<18F252.h>
#zero_ram

#fuses HS
#use delay(clock=15MHz)
#use rs232(baud=9600,xmit=pin_c6,rcv=pin_c7)

#define buffer_size 256

int buffer[buffer_size];
int line = 0;
int lido = 0;

#INT_RDA
void serial_isr() {
	clear_interrupt(INT_RDA);
	buffer[line++] = getc();
	buffer[line] = '\0';
}

int main(void) {

	clear_interrupt(INT_RDA);
	enable_interrupts(INT_RDA);
	enable_interrupts(GLOBAL);

	while (TRUE) {
		if (buffer[0] != '\0') {
			printf("%s", buffer);
			buffer[0] = '\0';
			line = 0;
		}
		delay_ms(1500);
	}

	return 0;
}
