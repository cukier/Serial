/*
 * vairaveis.c
 *
 *  Created on: 22/08/2014
 *      Author: cuki
 */
//slv
short ctrl_bto;

int m_addr = 0xFF;
int r_addr = 0xFF;
int r_cmd = 0xFF;

long r_pos = 12345;
long m_pos = 12345;

int buffer[arrayLen];

//mstr

int m_cmd;
int nrSlv = 2;
int i;

long *p;
long pos_slv[arrayLen];
