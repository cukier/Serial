/*
 * master.c
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

short send_stp = TRUE;
short ctrl_bto = FALSE;
short recolhe = FALSE;

int trata_bto() {
	short sobe = !input(bto_sobe);
	short desce = !input(bto_desce);
	int ret = 0xFF;

	if (sobe ^ desce) {
		if (!ctrl_bto) {
			delay_ms(debounce);
			if (!input(bto_sobe))
				ret = bto_sobe;
			if (!input(bto_desce))
				ret = bto_desce;
			ctrl_bto = TRUE;
		}
	} else if (ctrl_bto) {
		ctrl_bto = FALSE;
		ret = vbto_parar;
	}

	return ret;
}

void send(int iCmd) {
	int i = 0;
	if (iCmd != cmd_parar) {
		for (i = 1; i <= nrSlaves; ++i)
			printf("\n\r%02u%02u", i, iCmd);
	} else
		printf("\n\r%02u%02u", 0, iCmd);
}

void read() {
	int i = 0;

	for (i = 1; i <= nrSlaves; ++i) {
		printf("\n\r%02u%02u", i, cmd_pos);

		while (!recived)
			;
		if (recived) {
			recived = FALSE;
			r_addr = trans_addr(buffer);
			pos_elev[r_addr] = trans_pos(buffer);
			buffer[0] = '\0';
			line = 0;
			en_timer2 = TRUE;
		}
	}
}

int main(void) {

	clear_interrupt(INT_TIMER2);
	set_timer2(0);
	setup_timer_2(T2_DISABLED, 255, 1);

	clear_interrupt(INT_RDA);
	enable_interrupts(INT_RDA);
	enable_interrupts(INT_TIMER2);
	enable_interrupts(GLOBAL);

	while (TRUE) {
		switch (trata_bto()) {
		case bto_sobe:
			send(cmd_subir);
			recolhe = TRUE;
			break;
		case bto_desce:
			send(cmd_descer);
			recolhe = TRUE;
			break;
		case vbto_parar:
			send(cmd_parar);
			recolhe = FALSE;
			break;
		}

		if (recolhe) {
			read();
		}

		delay_ms(100);
	}

	return 0;
}
