/*
 * custom_malloc.c
 *
 *  Created on: 29 de jun de 2016
 *      Author: cassiano
 */

#include "custom_malloc.h"

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define DEBUG_MALLOC 0

// Estrutura para representar os blocos
typedef struct {
	uint esta_disponivel :1;
	uint tamanho :31;
} MCB, *MCB_P;

byte *memoria;

// Inicio da memória
byte *memoria_inicio;
// Tamanho máximo da memória
int memoria_maxima;

// Tamanho total da memória em uso
int memoria_alocada;

// Número de blocos alocados
int numero_blocos;

byte *memoria_final;

//MCB_P memallocate(MCB_P, int);

enum {
	NEW_MCB = 0, NO_MCB, REUSE_MCB
};

// Enum para representar se um bloco está e uso ou não
enum {
	FREE, IN_USE
};

// Inicializa a memória
void embInicializar(size_t tamanho_em_bytes) {
	memoria = (char *)sbrk(0);

	if (sbrk(tamanho_em_bytes) == (void*) -1) {
		fprintf(stderr, "Não foi possível instanciar o alocador\n");
		memoria = NULL;
	} else {
		memset(memoria, 0, tamanho_em_bytes);

		memoria_maxima = tamanho_em_bytes;
		memoria_inicio = memoria;
		numero_blocos = 0;
		memoria_alocada = 0;
		memoria_final = memoria_inicio + tamanho_em_bytes;
	}
}

// Aloca a memória
void *embMalloc(int tamanho) {
	/* check whether any chunk (allocated before) is free first */

	MCB_P p_mcb;
	int flag = NO_MCB;

	p_mcb = (MCB_P) memoria_inicio;

	int sz;

	sz = sizeof(MCB);

	if ((tamanho + sz)
			> (memoria_maxima - (memoria_alocada + numero_blocos * sz))) {
		fprintf(stderr, "Tamanho máximo da memória excedido\n");
		return NULL;
	}

	// Pesquisa o primeiro bloco livre que pode caber a memória a ser alocada
	while (memoria_final > ((byte *) p_mcb + tamanho + sz)) {

		if (p_mcb->esta_disponivel == 0) {

			if (p_mcb->tamanho == 0) {
				flag = NEW_MCB;
				break;
			}
			if (p_mcb->tamanho > (tamanho + sz)) {
				flag = REUSE_MCB;
				break;
			}
		}
		p_mcb = (MCB_P) ((byte *) p_mcb + p_mcb->tamanho);

	}

	if (flag != NO_MCB) {
		p_mcb->esta_disponivel = 1;

		if (flag == NEW_MCB) {
			p_mcb->tamanho = tamanho + sizeof(MCB);
			numero_blocos++;
		}
		memoria_alocada += tamanho;
		return ((byte *) p_mcb + sz);
	}

	fprintf(stderr,
			"Não foi possível alocar a quantidade de memória requisitada\n");
	return NULL;
}

// TODO Implementar essa função
int MemEfficiency() {
	/* keep track of number of MCBs in a global variable */
	return numero_blocos;
	/* This function is complete as well. :-) */

}

// Libera um espaço de memória
void embFree(void *p) {
	// Marca um bloco como livre
	MCB_P ptr = (MCB_P) p;
	ptr--;

	numero_blocos--;
	ptr->esta_disponivel = FREE;

#if DEBUG_MALLOC
	printf("\nMemória alocada antes: %d\n", ptr->tamanho);
#endif

	memoria_alocada -= (ptr->tamanho - sizeof(MCB));

#if DEBUG_MALLOC
	printf("\nMemória alocada depois: %d\n", memoria_alocada);
	printf("\nMemória liberada\n");
#endif
}

void embDestruir() {
	free(memoria);

	memoria = NULL;
	memoria_inicio = NULL;
	memoria_final = NULL;

	memoria_maxima = 0;
	memoria_alocada = 0;
}
