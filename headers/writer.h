/*
 * writer.h
 *
 *  Created on: Nov 1, 2020
 *      Author: yujiehao
 */

#ifndef WRITER_H_
#define WRITER_H_

#include <pthread.h>

extern int readers_waiting_count;
extern int iter_count;
extern int writers_amount;
extern int readers_amount;

extern pthread_mutex_t m_reader;
extern pthread_mutex_t m_writer;
extern pthread_cond_t c_reader;
extern pthread_cond_t c_writer;

void *writer (void *param);

#endif /* WRITER_H_ */
