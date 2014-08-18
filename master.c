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
int add_slv = 1;

short recived = FALSE;
short en_timer2 = TRUE;
short send_stp = TRUE;
short ctrl_bto = FALSE;

typedef struct elev_struct {
	int addr;
	long pos;
} elev_type;

elev_type elevador[4];

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

int trata_bto() {
	short sobe = !input(bto_sobe);
	short desce = !input(bto_desce);
	int ret = 0xFF;

	if (sobe ^ desce) {
		delay_ms(debounce);
		if (!input(bto_sobe))
			ret = bto_sobe;
		if (!input(bto_desce))
			ret = bto_desce;
		ctrl_bto = TRUE;
	} else if (!send_stp && ctrl_bto) {
		ctrl_bto = FALSE;
		send_stp = TRUE;
	}

	return ret;
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
		if (recived) {
			recived = FALSE;
			int addr = buffer[0] - 48;
			int pos = buffer[1] - 48;
			elevador[addr].addr = addr;
			elevador[0].pos = pos;
			buffer[0] = '\0';
			line = 0;
			en_timer2 = TRUE;
		}

		switch (trata_bto()) {
		case bto_sobe:
			printf("%u%u", add_slv, cmd_subir);
			break;
		case bto_desce:
			printf("%u%u", add_slv, cmd_descer);
			break;
		default:
			if (send_stp) {
				send_stp = FALSE;
				printf("%u%u", add_slv, cmd_parar);
			}
		}
		delay_ms(100);
	}

	return 0;
}
