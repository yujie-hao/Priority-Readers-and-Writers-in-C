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
	struct Thread_args* p = (struct Thread_args*)param;

	for (int i = 0; i < iter_count; i++) {
		// wait random time before write the shared var
		// Note: must sleep before the mutex lock! other wise, it lock first then sleep, other thread got blocked during this thread's sleep time. Not efficient

		int wait_ms = generat_rand_num(5000, 1000);
		usleep(wait_ms * 1000);


		if (readers_waiting_count < 0) {
			// readers number should always be non-negative
			return 0;
		}

		while (readers_waiting_count != 0) {
			// block until reader count is zero!
			pthread_cond_wait(&c_writer, &m_writer);
		}

		// should use mutex here, only one writer could write the shared_var, to prevent race condition
		pthread_mutex_lock(&m_writer);

		// create a random num [1, 100] to write to shared var
		int num = generat_rand_num(100, 1);
		*p->shared_var = num;
		printf("\nWriter#%d-%d: total reader count %d, wait for %d milli-second, wrote: %d\n ", p->id, i + 1, readers_waiting_count, wait_ms, *p->shared_var);

		pthread_mutex_unlock(&m_writer);
	}

	printf("Writer#%d: done!\n", p->id);
	return 0;
}
