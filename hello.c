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

#include<string.h>

int i = 0;
char comando[3][10];

char str[];

int main(void) {

	strcpy(comando[0], "cukier1");
	strcpy(comando[1], "cukier2");
	strcpy(comando[2], "cukier3");

	while (TRUE) {
		for (i = 0; i < 3; ++i) {
			str = comando[i];
			printf("%s\n\r", str);
			delay_ms(1000);
		}
	}

	return 0;
}
