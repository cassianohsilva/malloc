#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	
	int numero_iteracoes = 20;
	int tamanho_variavel = 20;

	int max_iteracoes = 1001;
	int max_tamanho_variavel = 1001;

	int i, j;

	for (i = numero_iteracoes; i < max_iteracoes; i += 20) {
		for (j = tamanho_variavel; j < max_tamanho_variavel; j += 20) {
			char comando[100];

			sprintf(comando, "./emb_main %d %d", i, j);

			system(comando);
		}
	}

	return 0;
}