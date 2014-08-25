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

#include "defines.c"
#include "variaveis.c"
#include "funcoes.c"

int main(void) {

	m_cmd = cmd_parar;

	while (TRUE) {

		m_cmd = trata_bto(m_cmd);

		if (m_cmd == cmd_subir || m_cmd == cmd_descer) {
			p = recall_pos(nrSlv, r_pos);
			for (i = 0; i < nrSlv; ++i) {
				pos_slv[i] = *(p + i);
			}
		}
		delay_ms(100);
	}

	return 0;
}

