/*
 * vairaveis.c
 *
 *  Created on: 22/08/2014
 *      Author: cuki
 */

short ctrl_bto;
short RxOk;

int m_addr = 0xFF; //meu endereco
int r_addr = 0xFF; //endereco lido
int aux_addr = 0xFF;
int m_cmd = 0xFF; // meu comando atual
int r_cmd = 0xFF; //comando lido
int l_cmd = 0xFF; //ultimo comando recebido
int nrSlv = 2; //nr de escravos da rede
int i;
int line; //linha do buffer de leitrua

int buffer[bufferLen]; //buffer de leitura

long r_pos = 12345; //posicao recebida
long m_pos = 12345; //minha posicao

long *p;
long pos_slv[bufferLen]; //posicao de todos os escravos
