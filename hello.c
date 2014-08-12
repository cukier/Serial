/*
 * hello.c
 *
 *  Created on: 12/08/2014
 *      Author: cuki
 */

#include<18F252.h>
#zero_ram

#fuses HS
#use delay(clock=15MHz)
#use rs232(baud=9600,xmit=pin_c6,rcv=pin_c7)

long i = 0;

int main(void) {
	while (TRUE) {
		printf("Hello %lu\n\r", i++);
		delay_ms(100);
	}

	return 0;
}
