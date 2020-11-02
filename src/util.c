/*
 * util.c
 *
 *  Created on: Nov 2, 2020
 *      Author: yujiehao
 */

#include <stdlib.h>
#include <time.h>

int generat_rand_num(int max, int min) {
	srand(time(NULL));
	return rand() % (max + 1 - min) + min;
}
