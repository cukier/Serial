/*
 * funcoes.c
 *
 *  Created on: 21/08/2014
 *      Author: cuki
 */

int send_cmd(int cmd) {
	printf("%02u%02u\r\n", 0, cmd);
	delay_ms(100);
	return cmd;
}

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

int trata_bto() {
	short sobe = !input(bto_sobe);
	short desce = !input(bto_desce);
	int ret = 0xFF;

	if (sobe ^ desce) {
		if (!ctrl_bto) {
			delay_ms(debounce);
			if (!input(bto_sobe))
				ret = send_cmd(cmd_subir);
			if (!input(bto_desce))
				ret = send_cmd(cmd_descer);
			ctrl_bto = TRUE;
		}
	} else if (ctrl_bto) {
		ctrl_bto = FALSE;
		ret = send_cmd(cmd_parar);
	}

	return ret;
}

void send_cmd(int addr, int cmd) {
	printf("%02u%02u\n\r", addr, cmd);
	delay_ms(20);
}

void send_pos(int addr, long pos) {
	printf("%02u%05lu\n\r", addr, pos);
	delay_ms(20);
}
