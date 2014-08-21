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

void send(int iaddr, int iCmd) {
	printf("\n\r%02u%02u", iaddr, iCmd);
	delay_ms(10);
}

void sendAll(int iCmd) {
	send(0, iCmd);
}

void sendRef() {
	printf("\n\r%02u%02u%04lu", 0, cmd_ref, posRef);
	delay_ms(10);
}

void read() {
	int i = 0;

	for (i = 1; i <= nrSlaves; ++i) {
		send(i, cmd_pos);

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
			sendAll(cmd_subir);
			recolhe = TRUE;
			break;
		case bto_desce:
			sendAll(cmd_descer);
			recolhe = TRUE;
			break;
		case vbto_parar:
			sendAll(cmd_parar);
			recolhe = FALSE;
			break;
		}

		if (recolhe) {
			read();
			sendRef();
		}

		delay_ms(100);
	}

	return 0;
}
