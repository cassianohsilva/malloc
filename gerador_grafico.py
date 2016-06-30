import ast

import numpy as np
from matplotlib import pyplot as plt

def linha_para_resultado(linha):

	linha_separada = linha.split()

	return [int(linha_separada[0]), int(linha_separada[1]), float(linha_separada[2]), float(linha_separada[3]), float(linha_separada[4]), float(linha_separada[5])]

	pass

def main():

	# arquivo = open("resultados.txt", "r")
	arquivo = open("resultados_malloc_free.txt", "r")
	

	linhas = arquivo.readlines()
	
	resultados = [ linha_para_resultado(l) for l in linhas]
	# resultados = [ ast.literal_eval(l[1]) for l in linhas]

	x_malloc = []
	y_malloc = []

	x_emb = []
	y_emb = []

	# for i in range(0, 2500, 50):
	for i in range(5, 500, 50):

		x_malloc.append(resultados[i][0])
		y_malloc.append(resultados[i][4])

		x_emb.append(resultados[i][0])
		y_emb.append(resultados[i][5])

		pass

	# for resultado in resultados:
	# 	pass

	# print(linhas[0].split())
	# print(resultados[0:10])

	plt.xticks(np.arange(20, 401, 40.0))

	plt.plot(x_malloc, y_malloc, label = "malloc")
	plt.plot(x_emb, y_emb, label = "emb_malloc")

	plt.ylabel('Tempo de Execução (ms)')
	plt.xlabel('Número de iterações')

	plt.legend(loc='upper left')

	# plt.show()
	plt.savefig('malloc_x_emb_malloc_free.png', dpi = 150)

	# print(list(range(20, 1001, 20)))

	pass


if __name__ == '__main__':
	main()