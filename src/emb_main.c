//============================================================================
// Name        : AA-SO.cpp
// Author      : Cassiano Honorio da Silva
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "emb_malloc.h"

typedef struct {
	char a[1000];
	int b[50];
} estrutura;

//#define MAX 100
//#define MAX 100

#define DEBUG 0

#define SIZE 1024*10

void imprimir(int * valores, int tamanho) {
	int i;

	for (i = 0; i < tamanho; i++) {
		printf(" %d ", valores[i]);
	}

	printf("\n");
}

void imprimir_uso() {
	printf("Uso:\n\tmain NUMERO_ITERACOES TAMANHO_VARIAVEL\n");
}

int main(int argc, char ** argv) {
	/*
	 if(!embInicializar(SIZE * sizeof(int))) {
	 return 0;
	 }

	 int tamanho_a = 10;
	 int tamanho_b = 7;

	 int * a = (int *) embMalloc(tamanho_a *sizeof(int));
	 int * b = (int *) embMalloc(tamanho_b *sizeof(int));

	 int i;
	 for(i = 0; i < tamanho_a; i++) {
	 a[i] = i;
	 }

	 for(i = 0; i < tamanho_b; i++) {
	 b[i] = i;
	 }

	 imprimir(a, tamanho_a);
	 imprimir(b, tamanho_b);

	 embFree(a);

	 // Vetor c

	 int tamanho_c = 1;

	 int * c = (int *) embMalloc(tamanho_c *sizeof(int));

	 for(i = 0; i < tamanho_c; i++) {
	 c[i] = tamanho_c - i;
	 }

	 imprimir(c, tamanho_c);

	 // Vetor d

	 int tamanho_d = 1;

	 int * d = (int *) embMalloc(tamanho_d *sizeof(int));

	 for(i = 0; i < tamanho_d; i++) {
	 d[i] = tamanho_d - i;
	 }

	 imprimir(d, tamanho_d);

	 printf("a: %p\n", a);
	 printf("b: %p\n", b);
	 printf("c: %p\n", c);
	 printf("d: %p\n", d);
	 */

	//char buf[SIZE];
	//char* buf = malloc(SIZE * sizeof(char));
//	memset(buf, 0, SIZE);
	//embInicializar(buf, SIZE);
//	embInicializar(SIZE  * sizeof(byte));
//	embInicializar(SIZE  * sizeof(int));
//	embInicializar(SIZE  * sizeof(double));

	if (argc < 3) {
		imprimir_uso();
		return 0;
	}

	int iteracoes = atoi(argv[1]);
	int tamanho_elemento = atoi(argv[2]);

	if (!iteracoes || !tamanho_elemento) {
		fprintf(stderr, "Parâmetros inválidos!\n");
		imprimir_uso();
		return 0;
	}

	char temp[tamanho_elemento];

	if (!embInicializar(SIZE * sizeof(temp))) {
		return 0;
	}

	int i;

	clock_t t1, t2;

	double tempo_emb = 0.0;
	double tempo_malloc = 0.0;

	for (i = 0; i < iteracoes; i++) {

		t1 = clock();

//		char *k = (char *) embMalloc(sizeof(char));
//		int *k = (int *) embMalloc(sizeof(int));
//		double *k = (double *) embMalloc(sizeof(double));
		void *k = embMalloc(sizeof(temp));

//		t1 = clock();
		embFree(k);
		t2 = clock();

		tempo_emb += (double) (t2 - t1) * 1000 / CLOCKS_PER_SEC;
	}

	for (i = 0; i < iteracoes; i++) {

		t1 = clock();
//		char *k = (char*) malloc(sizeof(char));temp

		void *k = malloc(sizeof(temp));
//		t1 = clock();
		free(k);
		t2 = clock();

		tempo_malloc += (double) (t2 - t1) * 1000 / CLOCKS_PER_SEC;
	}

#if DEBUG
	printf("\nTempo malloc:\t%f\n", tempo_malloc);
	printf("Tempo emb_malloc:\t%f\n", tempo_emb);
#endif

	char nome_arquivo[100];

//	sprintf(nome_arquivo, "resultados.txt", iteracoes,
//			SIZE * sizeof(estrutura));
	sprintf(nome_arquivo, "resultados_malloc_free.txt");

	FILE* arquivo = fopen(nome_arquivo, "a");

	fprintf(arquivo, "%d %lu %lf %lf %lf %lf\n", iteracoes, sizeof(temp),
			tempo_malloc / iteracoes, tempo_emb / iteracoes, tempo_malloc, tempo_emb);

	fclose(arquivo);

	embDestruir();
}
