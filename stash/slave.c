/*
 * slave.c
 *
 *  Created on: 18/08/2014
 *      Author: cuki
 */

#include<18F252.h>
#zero_ram

#include<stdlib.h>

#fuses HS
#use delay(clock=15MHz)
#use rs232(baud=9600,xmit=pin_c6,rcv=pin_c7)

#include "defines.c"
#include "variaveis.c"
#include "funcoes.c"
#include "interrupcoes.c"

int main(void) {

	init_slv();

	while (TRUE) {

		if (RxOk) {
			RxOk = FALSE;
			trata_comunicacao();
		}

	}

	return 0;
}
