/*
 * custom_malloc.h
 *
 *  Created on: 29 de jun de 2016
 *      Author: cassiano
 */

#ifndef EMB_MALLOC_H_
#define EMB_MALLOC_H_

#include <stdlib.h>

typedef char byte;
typedef unsigned int uint;

int embInicializar(size_t tamanho_em_bytes);

void *embMalloc(int tamanho);

int embFree(void *ponteiro);

void embDestruir();

#endif /* EMB_MALLOC_H_ */
