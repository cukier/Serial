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

	aux[0] = *(p + 2);
	aux[1] = *(p + 3);
	aux[2] = *(p + 4);
	aux[3] = *(p + 5);
	aux[4] = *(p + 6);

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

long *recall_pos(int nrSlaves, long pos) {
	int i;
	static long ret[arrayLen];
	int aux[arrayLen];

	send_cmd(allSlvs, cmd_w);
	send_pos(allSlvs, pos);

	for (i = 1; i <= nrSlaves; ++i) {
		delay_ms(latencia);
		send_cmd(i, cmd_r);
		gets(aux);
		ret[i - 1] = getPos(aux);
	}

	return ret;
}
