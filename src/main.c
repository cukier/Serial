/*
 * main.c
 *
 *  Created on: 30 de nov de 2015
 *      Author: cuki
 */

#include<18F25K22.h>

#fuses HSH, NOPLLEN
#use delay(clock=25MHz)
#use rs232(uart1, baud=19200, stream=stream1)
#use rs232(uart2, baud=19200, stream=stream2)

#define buffer_size 30

int buffer1[buffer_size], buffer2[buffer_size];
int index1, index2;
short print = FALSE;

#INT_RDA
void isr_rda() {
	clear_interrupt(INT_RDA);
	buffer1[index1++] = fgetc(stream1);
	if (index1 >= buffer_size)
		index1 = 0;
	print = TRUE;
}

#INT_RDA2
void isr_rda2() {
	clear_interrupt(INT_RDA2);
	buffer2[index2++] = fgetc(stream2);
	if (index2 >= buffer_size)
		index2 = 0;
	print = TRUE;
}

int main(void) {

	clear_interrupt(INT_RDA);
	clear_interrupt(INT_RDA2);

	enable_interrupts(INT_RDA);
	enable_interrupts(INT_RDA2);
	enable_interrupts(GLOBAL);

	fprintf(stream1, "hello\n\r");
	fprintf(stream2, "hello\n\r");

	while (TRUE) {
		if (print) {
			print = FALSE;
			fprintf(stream1, "\n\r%d %c", index1, buffer1[index1 - 1]);
			fprintf(stream2, "\n\r%d %c", index2, buffer2[index2 - 1]);
		}
	}

	return 0;
}
