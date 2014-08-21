/*
 * variaveis.c
 *
 *  Created on: 20/08/2014
 *      Author: cuki
 */

int buffer[buffer_size];
int line = 0;
int addr = 1;
int r_addr = 10;

long pos;

short recived = FALSE;
short en_timer2 = TRUE;
//escravo
int r_cmd = 0;
//mestre
int nrSlaves = 2;
int i = 0;
long posRef = 0;

long pos_elev[max_slv];

