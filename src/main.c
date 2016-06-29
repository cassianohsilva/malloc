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

#include "custom_malloc.h"

#define MAX 100

#define SIZE 1024*1024

int main() {
	//char buf[SIZE];
	char* buf = malloc(SIZE * sizeof(char));

	memset(buf, 0, SIZE);

	InitMem(buf, SIZE);

	int i;

	clock_t t1, t2;

	double tempo_cel = 0.0;
	double tempo_malloc = 0.0;

	for (i = 0; i < MAX; i++) {

		t1 = clock();
		char *k = (char *) myalloc(sizeof(char));
		t2 = clock();

		myfree(k);

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

	free(buf);
	/*
	 char *str,*str1;

	 str=myalloc(100);
	 printf("\nMemory address: %p",str);
	 printf("\nMCB count: %-3d \tAllocated Memory: %-10d",mcb_count,allocated_mem);
	 myfree(str);
	 str1=myalloc(200);
	 printf("\n\nMemory address: %p",str1);
	 printf("\nMCB count: %-3d \tAllocated Memory: %-10d\n",mcb_count,allocated_mem);

	 printf("--------------------------\n");

	 int *i = myalloc(sizeof(int));

	 printf("Valor lixo: %d\n", *i);

	 *i = 10;

	 printf("Valor lixo: %d\n", *i);

	 myfree(i);*/
}
