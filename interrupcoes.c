/*
 * interrupcoes.c
 *
 *  Created on: 20/08/2014
 *      Author: cuki
 */

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
