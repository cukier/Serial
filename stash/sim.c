/*
 * sim.c
 *
 *  Created on: 10/09/2014
 *      Author: cuki
 */

#include <16F628A.h>

#fuses HS

#use delay(clock=16MHz)
#use rs232(xmit=PIN_B2, baud=9600)

#define cms_mstr	PIN_A0
#define cmd_mstr	PIN_A1
#define cms_slv		PIN_A2
#define cmd_slv		PIN_A3

#define pos_mstr	PIN_B0
#define pos_slv		PIN_B1

short ctrlMstr;
short ctrlSlv;
short mstr_sobe;
short slv_sobe;

signed long fuso_mstr;
signed long fuso_slv;

#INT_TIMER0
void isr_tmr0() {
	clear_interrupt(INT_TIMER0);
	if (mstr_sobe)
		fuso_mstr++;
	else
		fuso_mstr--;
	output_toggle(pos_mstr);
}

#INT_TIMER1
void isr_tmr1() {
	clear_interrupt(INT_TIMER1);
	if (slv_sobe)
		fuso_slv++;
	else
		fuso_slv--;
	output_toggle(pos_slv);
}

void trata_bto() {
	short a = !input(cms_mstr);
	short b = !input(cmd_mstr);
	short c = !input(cms_slv);
	short d = !input(cmd_slv);

	if (a ^ b) {
		if (ctrlMstr) {
			ctrlMstr = FALSE;
			mstr_sobe = a;
			enable_interrupts(INT_TIMER0);
		}
	} else if (!ctrlMstr) {
		ctrlMstr = TRUE;
		disable_interrupts(INT_TIMER0);
	}

	if (c ^ d) {
		if (ctrlSlv) {
			ctrlSlv = FALSE;
			slv_sobe = c;
			enable_interrupts(INT_TIMER1);
		}
	} else if (!ctrlSlv) {
		ctrlSlv = TRUE;
		disable_interrupts(INT_TIMER1);
	}
}

int main(void) {

	set_timer0(0);
	setup_timer_0(T0_INTERNAL | T0_DIV_256);

	set_timer1(0);
	setup_timer_1(T1_INTERNAL | T1_DIV_BY_2);

	clear_interrupt(INT_TIMER0);
	clear_interrupt(INT_TIMER1);
	enable_interrupts(GLOBAL);

	while (TRUE) {
		trata_bto();
	}

	return 0;
}
