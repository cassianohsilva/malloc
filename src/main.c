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
#define MAX 100

#define SIZE 1024

void imprimir(int * valores, int tamanho) {
	int i;

	for(i = 0; i < tamanho; i++) {
		printf(" %d ", valores[i]);
	}

	printf("\n");
}

int main() {

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

	/*
	//char buf[SIZE];
	//char* buf = malloc(SIZE * sizeof(char));

//	memset(buf, 0, SIZE);

	//embInicializar(buf, SIZE);
//	embInicializar(SIZE  * sizeof(byte));
//	embInicializar(SIZE  * sizeof(int));
//	embInicializar(SIZE  * sizeof(double));
	embInicializar(SIZE  * sizeof(estrutura));

	int i;

	clock_t t1, t2;

	double tempo_cel = 0.0;
	double tempo_malloc = 0.0;

	for (i = 0; i < MAX; i++) {

		t1 = clock();
//		char *k = (char *) embMalloc(sizeof(char));
//		int *k = (int *) embMalloc(sizeof(int));
//		double *k = (double *) embMalloc(sizeof(double));
		estrutura *k = (estrutura *) embMalloc(sizeof(estrutura));
		t2 = clock();

		embFree(k);

		tempo_cel += (double) (t2 - t1) * 1000 / CLOCKS_PER_SEC;
	}

	for (i = 0; i < MAX; i++) {

		t1 = clock();
		char *k = (char*) malloc(sizeof(char));
		t2 = clock();

		free(k);

		tempo_malloc += (double) (t2 - t1) * 1000 / CLOCKS_PER_SEC;
	}

	printf("\nTempo malloc: %f\n", tempo_malloc);
	printf("Tempo cel:   %f\n", tempo_cel);

	embDestruir();
	*/

//	free(buf);
}
