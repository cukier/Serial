/*
 * vairaveis.c
 *
 *  Created on: 22/08/2014
 *      Author: cuki
 */

short ctrl_bto;
short RxOk;

int m_addr = 0xFF;
int r_addr = 0xFF;
int r_cmd = 0xFF;
int m_cmd = 0xFF;
int nrSlv = 2;
int i;
int line;

int buffer[bufferLen];

long r_pos = 12345;
long m_pos = 12345;

long *p;
long pos_slv[bufferLen];
