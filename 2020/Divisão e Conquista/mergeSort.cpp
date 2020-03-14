/*

Esse código gera um vetor de tamanho n (MACRO) com números aleatórios.
Após isso ele executa o Merge Sort ordenando o vetor e aproveita para calcular 
o número de inversões na hora de fazer o "merge" das duas metades ordenadas.

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define n 5
#define MAXN 100000
#define MINVALUE 0				// menor valor gerado no vetor
#define MAXVALUE 10000			// maior valor gerado no vetor

int numeros[MAXN];		// vetor de números
int auxiliar[MAXN];		// vetor auxiliar para o Merge Sort
ll numeroDeInversoes; 	// conta o número de inversões no array

// Geração de um número aleatório
int numeroAleatorio()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	static default_random_engine generator (seed);
	uniform_int_distribution<int> distribution(MINVALUE, MAXVALUE);
	return distribution(generator);
}

void merge(int esquerda, int meio, int direita)
{
	// ponteiroEsq e ponteiroDir são os ponteiros das duas metades ordenadas
	int ponteiroEsq, ponteiroDir, indice;
	ponteiroEsq = esquerda;
	ponteiroDir = meio+1;
	indice = esquerda;
	while(ponteiroEsq <= meio && ponteiroDir <= direita) // enquanto há elementos nas duas metades
	{
		// verifica qual deles é menor
		if(numeros[ponteiroDir] < numeros[ponteiroEsq])
		{
			// se o da direita é maior que o da esquerda então atualiza o número de inversões
			numeroDeInversoes += meio-ponteiroEsq+1;
			auxiliar[indice] = numeros[ponteiroDir];
			ponteiroDir++;
		}
		else
		{
			auxiliar[indice] = numeros[ponteiroEsq];
			ponteiroEsq++;
		}
		indice++;
	}
	while(ponteiroEsq <= meio)
	{
		auxiliar[indice] = numeros[ponteiroEsq];
		ponteiroEsq++;
		indice++;
	}
	while(ponteiroDir <= direita)
	{
		auxiliar[indice] = numeros[ponteiroDir];
		ponteiroDir++;
		indice++;
	}
	for(int i = esquerda; i <= direita; ++i)		// copia os valores ordenados no vetor de números
	{
		numeros[i] = auxiliar[i];
	}
}

void mergeSort(int esquerda, int direita)	// divisão do merge sort
{
	if(esquerda == direita)
	{
		return ;
	}
	int meio = (esquerda + direita)/2;
	mergeSort(esquerda, meio);				// ordena a primeira parte
	mergeSort(meio+1, direita);				// ordena a segunda parte
	merge(esquerda, meio, direita);			// faz a junção das duas partes ordenadas
}

int main()
{
	// Números gerados aleatoriamente
	for(int i = 0; i < n; ++i)
	{
		numeros[i] = numeroAleatorio();
	}
	printf("Numeros antes da ordenacao:\n");
	for(int i = 0; i < n; ++i)
	{
		printf("%d ", numeros[i]);
	}
	putchar('\n');
	numeroDeInversoes = 0;	// inicialização do número de inversões
	mergeSort(0, n-1);		// chama o mergeSort
	printf("Numeros apos a ordenacao:\n");
	for(int i = 0; i < n; ++i)
	{
		printf("%d ", numeros[i]);
	}
	putchar('\n');
	printf("O numero de inversoes no vetor original e igual a %lld\n", numeroDeInversoes);
	return 0;
}