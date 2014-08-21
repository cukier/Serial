/*
 * fucoes.c
 *
 *  Created on: 20/08/2014
 *      Author: cuki
 */

int trans_addr(int *ptr) {
	int ret = 0xFF;
	int aux[2];
	int *p;

	for (p = ptr; *p != '\r'; p++)
		;

	aux[0] = *(p + 2);
	aux[1] = *(p + 1);

	ret = atoi(aux);

	return ret;
}

long trans_pos(int *ptr) {

	int ret = 0xFF;
	int aux[4];
	int *p;

	for (p = ptr; *p != '\r'; p++)
		;

	aux[0] = *(p + 6);
	aux[1] = *(p + 5);
	aux[2] = *(p + 4);
	aux[3] = *(p + 3);

	ret = atol(aux);

	return ret;
}

int trans_cmd(int *ptr) {
	int ret = 0xFF;
	int aux[2];
	int *p;

	for (p = ptr; *p != '\r'; p++)
		;

	aux[0] = *(p + 4);
	aux[1] = *(p + 3);

	ret = atoi(aux);

	return ret;
}
