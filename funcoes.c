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

	for (p = ptr; *p != '\0'; p++)
		;

	aux[0] = *(p - 4);
	aux[1] = *(p - 3);

	ret = atoi(aux);

	return ret;
}

long trans_pos(int *ptr) {

	long ret = 0xFFFF;
	int posArray[16];
	int i = 0;

	for (i = 1; i < line; ++i) {
		posArray[i - 1] = *ptr[i];
	}

	ret = atol(posArray);

	return ret;
}

int trans_cmd(int *ptr) {
	int ret = 0xFF;
	int aux[2];
	int *p;

	for (p = ptr; *p != '\0'; p++)
		;

	aux[0] = *(p - 2);
	aux[1] = *(p - 1);

	ret = atoi(aux);

	return ret;
}
