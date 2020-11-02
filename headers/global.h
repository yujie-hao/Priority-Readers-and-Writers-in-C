/*
 * gloabl.h
 *
 *  Created on: Nov 2, 2020
 *      Author: yujiehao
 */

#ifndef HEADERS_GLOBAL_H_
#define HEADERS_GLOBAL_H_

#include <pthread.h>

struct Thread_args
{
	int* shared_var;
	int id;
};

#endif /* HEADERS_GLOBAL_H_ */
