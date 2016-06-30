/*
 * custom_malloc.c
 *
 *  Created on: 29 de jun de 2016
 *      Author: cassiano
 */

#include "emb_malloc.h"

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define DEBUG_MALLOC 0

// Estrutura para representar os blocos
typedef struct {
	uint disponivel :1;
	uint tamanho :31;
} BDM;

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
	NOVO_BLOCO = 0, SEM_BLOCO, REUTILIZAR_BLOCO
};

// Enum para representar se um bloco está e uso ou não
enum {
	LIVRE, OCUPADO
};

// Inicializa a memória
int embInicializar(size_t tamanho_em_bytes) {
	memoria = (char *) sbrk(0);

	if (sbrk(tamanho_em_bytes) == (void*) -1) {
		fprintf(stderr, "Não foi possível instanciar o alocador\n");
		memoria = NULL;

		return 0;
	} else {
		memset(memoria, 0, tamanho_em_bytes);

		memoria_maxima = tamanho_em_bytes;
		memoria_inicio = memoria;
		numero_blocos = 0;
		memoria_alocada = 0;
		memoria_final = memoria_inicio + tamanho_em_bytes;
	}

	return 1;
}

// Aloca a memória
void *embMalloc(int tamanho) {
	BDM* bloco;
	int flag = SEM_BLOCO;

	bloco = (BDM*) memoria_inicio;

	int tamanho_bloco = sizeof(BDM);

	if ((tamanho + tamanho_bloco)
			> (memoria_maxima - (memoria_alocada + numero_blocos * tamanho_bloco))) {
		fprintf(stderr, "Tamanho máximo da memória excedido\n");
		return NULL;
	}

	// Pesquisa o primeiro bloco livre que pode caber a memória a ser alocada
	while (memoria_final > ((byte *) bloco + tamanho + tamanho_bloco)) {
		if (bloco->disponivel == LIVRE) {

			if (bloco->tamanho == 0) {
				flag = NOVO_BLOCO;
				break;
			}
			if (bloco->tamanho > (tamanho + tamanho_bloco)) {
				flag = REUTILIZAR_BLOCO;
				break;
			}
		}
		bloco = (BDM*) ((byte *) bloco + bloco->tamanho);
	}

	if (flag != SEM_BLOCO) {
		bloco->disponivel = OCUPADO;

		if (flag == NOVO_BLOCO) {
			bloco->tamanho = tamanho + sizeof(BDM);
			numero_blocos++;
		}
		memoria_alocada += tamanho;
		return ((byte *) bloco + tamanho_bloco);
	}

	fprintf(stderr,
			"Não foi possível alocar a quantidade de memória requisitada\n");
	return NULL;
}

int embMemoria() {
	printf("Tamanho total da memória: %d bytes\n", memoria_maxima);
	printf("Tamanho total da memória alocada: %d bytes\n", memoria_alocada);

	return numero_blocos;
}

// Libera um espaço de memória
int embFree(void *ponteiro) {
	// Marca um bloco como livre
	if (ponteiro) {
		BDM* ponteiro_bloco = (BDM*) ponteiro;
		ponteiro_bloco--;

		numero_blocos--;
		ponteiro_bloco->disponivel = LIVRE;

		memoria_alocada -= (ponteiro_bloco->tamanho - sizeof(BDM));

		return 1;
	} else {
		return 0;
	}
}

void embDestruir() {
//	free(memoria);

	memoria = NULL;
	memoria_inicio = NULL;
	memoria_final = NULL;

	memoria_maxima = 0;
	memoria_alocada = 0;
}
