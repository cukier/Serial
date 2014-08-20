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

#include "definicoes.c"
#include "variaveis.c"
#include "interrupcoes.c"
#include "funcoes.c"

int main(void) {

	int r_addr;
	int cmd;

	clear_interrupt(INT_TIMER2);
	set_timer2(0);
	setup_timer_2(T2_DISABLED, 255, 1);

	set_timer0(0);
	setup_timer_0(T0_EXT_H_TO_L);

	clear_interrupt(INT_RDA);
	enable_interrupts(INT_RDA);
	enable_interrupts(INT_TIMER2);
	enable_interrupts(GLOBAL);

	output_low(saida_sobe);
	output_low(saida_desce);

	while (TRUE) {
		if (recived) {
			recived = FALSE;
			r_addr = trans_addr(buffer);
			cmd = trans_cmd(buffer);
			buffer[0] = '\0';
			line = 0;
			en_timer2 = TRUE;

			if (r_addr == addr || r_addr == 0) {
				if (cmd == cmd_subir)
					output_high(saida_sobe);
				else if (cmd == cmd_descer)
					output_high(saida_desce);
				else if (cmd == cmd_parar) {
					output_low(saida_sobe);
					output_low(saida_desce);
				}
				if (r_addr != 0)
					printf("\n\r%02u%04lu", addr, get_timer0());
			}
		}
	}

	return 0;
}
