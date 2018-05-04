/*
 * interrupcoes.c
 *
 *  Created on: 02/09/2014
 *      Author: cuki
 */

#int_rda
void isr_rda() {
	clear_interrupt(INT_RDA);
	buffer[line++] = getc();
	buffer[line] = "\0";
	RxOk = recivedOk(buffer);
	if (RxOk && line)
		line = 0;
}
