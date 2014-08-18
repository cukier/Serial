/*
 * encodersim.c
 *
 *  Created on: 15/08/2014
 *      Author: cuki
 */

#include <18F452.h>

#fuses HS

#use delay(clock=16MHz)
//#use rs232(xmit=PIN_C6, baud=9600)

//saidas
#define canal_a PIN_C7
#define canal_b PIN_C6
#define canal_z PIN_C5
//entradas
#define av PIN_B0
#define rv PIN_B1
//timers
#define tmr0_reg 59755
#define debouce 100
//estados de saida do encoder
#define estado_a 0
#define estado_b 1
#define estado_c 2
#define estado_d 3
//resolucao do encoder
#define resolucao 512

short ctrl = FALSE;
short emAvanco = FALSE;
short ligaTimer = FALSE;
int estado = 0;
signed long cont = 0;

#INT_TIMER0
void isr_timer0() {

	clear_interrupt(INT_TIMER0);
	set_timer0(tmr0_reg);

	if (emAvanco)
		++estado;
	else
		--estado;

	if (estado == estado_d + 1)
		estado = estado_a;
	else if (estado == 0xFF)
		estado = estado_d;

	switch (estado) {
	case estado_a:
		output_high(canal_a);
		output_high(canal_b);
		if (emAvanco)
			++cont;
		if (cont >= resolucao)
			cont = 0;
		break;
	case estado_b:
		output_high(canal_a);
		output_low(canal_b);
		break;
	case estado_c:
		output_low(canal_a);
		output_low(canal_b);
		break;
	case estado_d:
		output_low(canal_a);
		output_high(canal_b);
		if (!emAvanco)
			--cont;
		if (cont < 0)
			cont = resolucao - 1;
		break;
	}

	if (estado == estado_a && !cont)
		output_high(canal_z);
	else
		output_low(canal_z);
}

void check_bto() {

	short i_av = !input(av);
	short i_rv = !input(rv);

	if (i_av ^ i_rv) {
		if (i_av) {
			delay_ms(debouce);
			if (i_av)
				emAvanco = TRUE;
		}
		if (i_rv) {
			delay_ms(debouce);
			if (i_rv)
				emAvanco = FALSE;
		}
		if (ligaTimer) {
			ligaTimer = FALSE;
			set_timer0(tmr0_reg);
			setup_timer_0(T0_INTERNAL | T0_DIV_1);
		}
	} else if (!ligaTimer) {
		ligaTimer = TRUE;
		setup_timer_0(T0_OFF);
	}
}

int main(void) {

	set_timer0(tmr0_reg);
	setup_timer_0(T0_OFF);
	clear_interrupt(INT_TIMER0);
	enable_interrupts(INT_TIMER0 | GLOBAL);

	port_b_pullups(TRUE);

	estado = estado_a;
	output_low(canal_a);
	output_low(canal_b);
	output_high(canal_z);

	while (TRUE) {
		check_bto();
	}

	return 0;
}
