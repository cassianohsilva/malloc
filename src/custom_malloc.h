/*
 * custom_malloc.h
 *
 *  Created on: 29 de jun de 2016
 *      Author: cassiano
 */

#ifndef CUSTOM_MALLOC_H_
#define CUSTOM_MALLOC_H_

void InitMem(char *ptr, int size_in_bytes);

void *myalloc(int elem_size);

void myfree(void *p);

#endif /* CUSTOM_MALLOC_H_ */
