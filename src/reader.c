/*
 * reader.c
 *
 *  Created on: Nov 1, 2020
 *      Author: yujiehao
 */

#include <stdio.h>
//#ifndef HEADERS_GLOABL_H_
//#endif
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../headers/util.h"
#include "../headers/reader.h"

#ifndef HEADERS_GLOBAL_H_
#include "../headers/global.h"
#endif

void *reader (void *param) {
	for (int i = 0; i < iter_count; i++) {
		// should NOT use mutex here, since multiple reader could read shared var simultaneously,
		// without race condition
		if (readers_waiting_count < 0) {
			// readers number should always be non-negative
			return 0;
		}

		readers_waiting_count++;
		// wait random time before read the shared var [1 sec, 5 sec]
		int wait_sec = generat_rand_num(5, 1);
		printf("Reader#x: total reader count %d, wait for %d seconds ", readers_waiting_count, wait_sec);
		sleep(wait_sec);
		printf(" --> read: %d\n", *(int*)param);
		readers_waiting_count--;
		pthread_cond_signal(&c_writer);

	}


	printf("Reader#x done!\n");
	return 0;
}
