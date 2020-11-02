/*
 * reader.h
 *
 *  Created on: Nov 1, 2020
 *      Author: yujiehao
 */

#ifndef READER_H_
#define READER_H_

#include <pthread.h>

extern int readers_waiting_count;
extern int iter_count;
extern pthread_mutex_t mutex;
extern pthread_cond_t c_reader;
extern pthread_cond_t c_writer;

void *reader (void *param);

#endif /* READER_H_ */
