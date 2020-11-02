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
	struct Thread_args* p = (struct Thread_args*)param;
	for (int i = 0; i < iter_count; i++) {
		// wait random time before read the shared var
		int wait_ms = generat_rand_num(1000, 10);
		usleep(wait_ms * 1000);

		pthread_mutex_lock(&m_reader);
		if (readers_waiting_count < 0) {
			// readers number should always be non-negative
			return 0;
		}

		readers_waiting_count++;
		printf("\nReader#%d-%d: total reader count %d, wait for %d milli-second, read: %d\n", p->id, i + 1, readers_waiting_count, wait_ms, *p->shared_var);
		readers_waiting_count--;
		pthread_mutex_unlock(&m_reader);

		if (readers_waiting_count == 0) {
			pthread_cond_broadcast(&c_writer);
		}
	}

	printf("Reader#%d done!\n", p->id);
	return 0;
}
