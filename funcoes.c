/*
 * funcoes.c
 *
 *  Created on: 21/08/2014
 *      Author: cuki
 */

int getAddr(int *str) {

	int *p;
	int aux[2];

	p = str;

	aux[0] = *p;
	aux[1] = *(p + 1);

	return atoi(aux);
}

int getCmd(int *str) {

	int *p;
	int aux[2];

	p = str;

	aux[0] = *(p + 2);
	aux[1] = *(p + 3);

	return atoi(aux);
}

long getPos(int *str) {

	int *p;
	int aux[5];

	p = str;

	for (i = 0; i < 5; ++i)
		aux[i] = *(p + i + 2);

	return atol(aux);

}

int send_cmd(int addr, int cmd) {
	delay_ms(latencia);
	printf("%02u%02u\n\r", addr, cmd);
	return cmd;
}

void send_pos(int addr, long pos) {
	delay_ms(latencia);
	printf("%02u%05lu\n\r", addr, pos);
}

long *recall_pos(int nrSlaves, long pos) {
	int i;
	static long ret[bufferLen];
	int aux[bufferLen];

	send_cmd(allSlvs, cmd_w);
	send_pos(allSlvs, pos);

	for (i = 1; i <= nrSlaves; ++i) {
		send_cmd(i, cmd_r);
		gets(aux);
		ret[i - 1] = getPos(aux);
	}

	return ret;
}

int trata_bto(int cmd) {
	short sobe = !input(bto_sobe);
	short desce = !input(bto_desce);
	int ret = cmd;

	if (sobe ^ desce) {
		if (!ctrl_bto) {
			delay_ms(debounce);
			if (!input(bto_sobe))
				ret = send_cmd(allSlvs, cmd_subir);
			if (!input(bto_desce))
				ret = send_cmd(allSlvs, cmd_descer);
			ctrl_bto = TRUE;
		}
	} else if (ctrl_bto) {
		ctrl_bto = FALSE;
		ret = send_cmd(allSlvs, cmd_parar);
	}

	return ret;
}

int trata_comunicacao() {

	r_addr = 0xFF;
	r_cmd = 0xFF;

	r_addr = getAddr(buffer);
	r_cmd = getCmd(buffer);

	if (r_addr == m_addr || !r_addr) {
		if (r_cmd == cmd_w) {
			gets(buffer);
			r_pos = getPos(buffer);
		} else if (r_cmd == cmd_r) {
			m_pos++;
			send_pos(m_addr, m_pos);
		}
	}

	return r_cmd;
}

void subir() {
	output_low(pin_desce);
	delay_ms(latencia >> 1);
	output_high(pin_sobe);
}

void descer() {
	output_low(pin_sobe);
	delay_ms(latencia >> 1);
	output_high(pin_desce);
}

void parar() {
	output_low(pin_sobe);
	output_low(pin_desce);
	m_pos += get_timer0();
	set_timer0(0);
}

int getMAddr() {
	int aux = input_a();
	return ((input_a() & 0xF0) >> 4) & 0x0F;
}

void init_mstr() {
//	set_timer0(T0_EXT_H_TO_L | T0_DIV_1);
//	set_timer1(T1_EXTERNAL | T1_DIV_BY_1);

	clear_interrupt(INT_RDA);
	enable_interrupts(INT_RDA);
	enable_interrupts(GLOBAL);

	m_cmd = cmd_parar;
	nrSlv = getMAddr();

	parar();
}

void init_slv() {
//	set_timer0(T0_EXT_H_TO_L | T0_DIV_1);
//	set_timer1(T1_EXTERNAL | T1_DIV_BY_1);

	clear_interrupt(INT_RDA);
	enable_interrupts(INT_RDA);
	enable_interrupts(GLOBAL);

	m_cmd = cmd_parar;
	m_addr = getMAddr();

	parar();
}

void trata_cmd(int cmd) {

	switch (cmd) {
	case cmd_subir:
		subir();
		break;
	case cmd_descer:
		descer();
		break;
	case cmd_parar:
		parar();
		cmd_parar;
		break;
	default:
	}
}

short recivedOk(int *buff) {
	int *p;

	for (p = buff; *p != '\0'; p++)
		if (*p == '\n' && *(p + 1) == '\r')
			return TRUE;

	return FALSE;
}
