/*
 * slave.c
 *
 *  Created on: 18/08/2014
 *      Author: cuki
 */

/*
 * master.c
 *
 *  Created on: 18/08/2014
 *      Author: cuki
 */

#include<18F252.h>
#zero_ram

#fuses HS
#use delay(clock=15MHz)
#use rs232(baud=9600,xmit=pin_c6,rcv=pin_c7)

//defines
#define buffer_size 256
//cmd
#define cmd_parar	0x00
#define cmd_subir	0x01
#define cmd_descer	0x02
//entradas
#define bto_sobe	PIN_B0
#define bto_desce	PIN_B1
//saidas
#define saida_sobe	PIN_C0
#define saida_desce	PIN_C1
//tempos
#define debounce 100

int buffer[buffer_size];
int line = 0;
int lido = 0;
int m_addr = 1;

short recived = FALSE;
short en_timer2 = TRUE;

#INT_RDA
void serial_isr() {
	clear_interrupt(INT_RDA);
	buffer[line++] = getc();
	buffer[line] = '\0';
	set_timer2(0);
	if (en_timer2) {
		en_timer2 = FALSE;
		setup_timer_2(T2_DIV_BY_16, 255, 1);
	}
}

#INT_TIMER2
void timer2_isr() {
	clear_interrupt(INT_TIMER2);
	setup_timer_2(T2_DISABLED, 255, 1);
	set_timer2(0);
	recived = TRUE;
}

int main(void) {

	int addr;
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

	while (TRUE) {
		if (recived) {
			recived = FALSE;
			addr = buffer[0] - 48;
			cmd = buffer[1] - 48;
			buffer[0] = '\0';
			line = 0;
			en_timer2 = TRUE;

			if (m_addr == addr) {
				if (cmd == cmd_subir)
					output_low(saida_sobe);
				else if (cmd == cmd_descer)
					output_low(saida_desce);
				else if (cmd == cmd_parar) {
					output_high(saida_sobe);
					output_high(saida_desce);
				}
				printf("%u%lu", m_addr, get_timer0());
			}
		}
	}

	return 0;
}
