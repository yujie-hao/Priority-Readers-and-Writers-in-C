/*
 * main.c
 *
 *  Created on: Nov 1, 2020
 *      Author: yujiehao
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "headers/global.h"
#include "headers/reader.h"
#include "headers/writer.h"
#include "headers/util.h"

int readers_waiting_count = 0;
int iter_count = 4;
int readers_amount = 10;
int writers_amount = 6;

pthread_mutex_t m_reader = PTHREAD_MUTEX_INITIALIZER;  // mutex lock
pthread_mutex_t m_writer = PTHREAD_MUTEX_INITIALIZER;  // mutex lock
pthread_cond_t c_reader = PTHREAD_COND_INITIALIZER; // reader pthread condition var
pthread_cond_t c_writer = PTHREAD_COND_INITIALIZER; // writer pthread condition var

int main(int argc, char *argv[]) {
	printf("******\nStart priority reader and writer program\n---\n");

	pthread_t tid_readers[readers_amount], tid_writers[writers_amount]; // thread identifiers
	int shared_var = 0;
	int readersNum[readers_amount], writersNum[writers_amount];
	struct Thread_args writer_thread_args[writers_amount], reader_thread_args[readers_amount];

	for (int i = 0; i < writers_amount; i++) {
		// attention: i here is visible for all threads in this for loop scope.
		// hence use array to represent i for different threads --> I made mistake here, exactly what is explained by
		// https://classroom.udacity.com/courses/ud923/lessons/3155139407/concepts/31640693250923
		writersNum[i] = i;
		writer_thread_args[i].id = writersNum[i] + 1;
		writer_thread_args[i].shared_var = &shared_var;

		if (pthread_create(&tid_writers[i], NULL, writer, (void *)(&writer_thread_args[i])) != 0) {
			fprintf(stderr, "Unable to create the writer thread\n");
			exit(1);
		}

		printf("Created writer#%d\n", writer_thread_args[i].id);
		//Note: need to sleep some time here! Otherwise all writer's random sleep time is based on almost same time seed!
		int wait_ms = generat_rand_num(2000, 1000);
		usleep(wait_ms * 1000);
	}

	for (int i = 0; i < readers_amount; i++) {
		readersNum[i] = i;
		reader_thread_args[i].id = readersNum[i] + 1;
		reader_thread_args[i].shared_var = &shared_var;
		if (pthread_create(&tid_readers[i], NULL, reader, (void *)(&reader_thread_args[i])) != 0) {
			fprintf(stderr, "Unable to create the reader thread\n");
			exit(2);
		}
		printf("Created reader#%d\n", reader_thread_args[i].id);
		int wait_ms = generat_rand_num(2000, 1000);
		usleep(wait_ms * 1000);
	}

	for (int i = 0; i < writers_amount; i++) {
		pthread_join(tid_writers[i], NULL); //wait for writer thread to exit
	}

	for (int i = 0; i < readers_amount; i++) {
		pthread_join(tid_readers[i], NULL); //wait for reader thread to exit
	}

	printf("---\nFinished priority reader and writer program\n******\n");

	return 0;
}
