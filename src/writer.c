/*
 * writer.c
 *
 *  Created on: Nov 1, 2020
 *      Author: yujiehao
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../headers/util.h"
#include "../headers/writer.h"

#ifndef HEADERS_GLOBAL_H_
#include "../headers/global.h"
#endif

void *writer (void *param) {
	int* int_ptr = (int*)param;

	for (int i = 0; i < iter_count; i++) {
		// should use mutex here, only one writer could write the shared_var, to prevent race condition
		pthread_mutex_lock(&mutex);

		if (readers_waiting_count < 0) {
			// readers number should always be non-negative
			return 0;
		}

		while (readers_waiting_count != 0) {
			// block until reader count is zero!
			pthread_cond_wait(&c_writer, &mutex);
		}

		// create a random num [1, 100] to write to shared var
		*int_ptr = generat_rand_num(100, 1);
		int wait_sec = generat_rand_num(5, 1);
		printf("Writer#y: total reader count %d, wait for %d seconds ", readers_waiting_count, wait_sec);
		sleep(wait_sec);
		printf(" --> wrote: %d\n", *int_ptr);

		pthread_mutex_unlock(&mutex);
	}

	printf("Writer#y: done!\n");
	return 0;
}
