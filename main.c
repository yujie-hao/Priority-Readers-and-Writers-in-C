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

int main(int argc, char *argv[]) {
	printf("***\nStart priority reader and writer program\n---\n");

	pthread_t tid1, tid2; // thread identifiers

	if (pthread_create(&tid1, NULL, writer, NULL) != 0) {
		fprintf(stderr, "Unable to create the writer thread\n");
		exit(1);
	}

	if (pthread_create(&tid2, NULL, reader, NULL) != 0) {
		fprintf(stderr, "Unable to create the reader thread\n");
		exit(2);
	}

	pthread_join(tid1, NULL); //wait for writer thread to exit
	pthread_join(tid2, NULL); //wait for reader thread to exit

	printf("---\nFinished priority reader and writer program\n***\n");
}
