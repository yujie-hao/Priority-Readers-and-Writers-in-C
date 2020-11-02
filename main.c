/*
 * main.c
 *
 *  Created on: Nov 1, 2020
 *      Author: yujiehao
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "headers/reader.h"
#include "headers/writer.h"

int readers_waiting_count = 0;
int iter_count = 5;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // mutex lock
pthread_cond_t c_reader = PTHREAD_COND_INITIALIZER; // reader pthread condition var
pthread_cond_t c_writer = PTHREAD_COND_INITIALIZER; // writer pthread condition var

int main(int argc, char *argv[]) {
	printf("******\nStart priority reader and writer program\n---\n");

	pthread_t tid1, tid2; // thread identifiers
	int shared_var = 0;

	if (pthread_create(&tid1, NULL, writer, &shared_var) != 0) {
		fprintf(stderr, "Unable to create the writer thread\n");
		exit(1);
	}

	if (pthread_create(&tid2, NULL, reader, &shared_var) != 0) {
		fprintf(stderr, "Unable to create the reader thread\n");
		exit(2);
	}

	pthread_join(tid1, NULL); //wait for writer thread to exit
	pthread_join(tid2, NULL); //wait for reader thread to exit

	printf("---\nFinished priority reader and writer program\n******\n");
}
