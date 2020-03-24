/*

Esse código gera um vetor de tamanho n (MACRO) com números aleatórios.
Após isso ele executa o Merge Sort ordenando o vetor e aproveita para calcular 
o número de inversões na hora de fazer o "merge" das duas metades ordenadas.

Complexidade de tempo:  O ( N*log(N) )
Onde N é o tamanho do vetor

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define n 5
#define MAXN 100000
#define MINVALUE 0				// menor valor gerado no vetor
#define MAXVALUE 10000			// maior valor gerado no vetor

int numbers[MAXN];		// vetor de números
int aux[MAXN];			// vetor auxiliar para o Merge Sort
ll numInversions; 		// variável que conta o número de inversões no array

// Geração de um número aleatório
int randomNumber()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	static default_random_engine generator (seed);
	uniform_int_distribution<int> distribution(MINVALUE, MAXVALUE);
	return distribution(generator);
}

void merge(int left, int mid, int right)
{
	// leftPtr e rightPtr são os ponteiros das duas metades ordenadas
	int leftPtr, rightPtr, index;
	leftPtr = left;
	rightPtr = mid+1;
	index = left;
	while(leftPtr <= mid && rightPtr <= right) // enquanto há elementos nas duas metades
	{
		// verifica qual deles é menor
		if(numbers[rightPtr] < numbers[leftPtr])
		{
			// se o da direita é maior que o da esquerda então atualiza o número de inversões
			numInversions += mid-leftPtr+1;
			aux[index] = numbers[rightPtr];
			rightPtr++;
		}
		else
		{
			aux[index] = numbers[leftPtr];
			leftPtr++;
		}
		index++;
	}
	while(leftPtr <= mid)
	{
		aux[index] = numbers[leftPtr];
		leftPtr++;
		index++;
	}
	while(rightPtr <= right)
	{
		aux[index] = numbers[rightPtr];
		rightPtr++;
		index++;
	}
	for(int i = left; i <= right; ++i)		// copia os valores ordenados no vetor de números
	{
		numbers[i] = aux[i];
	}
}

void mergeSort(int left, int right)	// divisão do merge sort
{
	if(left == right)
	{
		return ;
	}
	int mid = (left + right)/2;
	mergeSort(left, mid);				// ordena a primeira parte
	mergeSort(mid+1, right);				// ordena a segunda parte
	merge(left, mid, right);			// faz a junção das duas partes ordenadas
}

int main()
{
	// Números gerados aleatoriamente
	for(int i = 0; i < n; ++i)
	{
		numbers[i] = randomNumber();
	}
	printf("Numeros antes da ordenacao:\n");
	for(int i = 0; i < n; ++i)
	{
		printf("%d ", numbers[i]);
	}
	putchar('\n');
	numInversions = 0;	// inicialização do número de inversões
	mergeSort(0, n-1);		// chama o mergeSort
	printf("Numeros apos a ordenacao:\n");
	for(int i = 0; i < n; ++i)
	{
		printf("%d ", numbers[i]);
	}
	putchar('\n');
	printf("O numero de inversoes no vetor original e igual a %lld\n", numInversions);
	return 0;
}