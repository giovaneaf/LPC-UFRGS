/*

Esse código cria uma equação de parábola aleatória com geração randômica dos coeficientes A, B e C.
Relembrando que a equação da parábola é f(x) = A * x^2 + B * x + C
Esse algoritmo encontra um mínimo local (se A > 0) ou máximo local (se A < 0) entre os limites
da busca que é o intervalo [0, 10^18]. 

A ideia da busca ternária é encontrar o máximo/mínimo global quando há uma função unimodal, ou seja,
quando há um ponto x em que a função cresce para x < m e decresce para x > m ou vice-versa e o objetivo
é encontrar esse máximo/mínimo global x.

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define EPS 1e-9

const int mod = 1e4+1;
ll A, B, C;

void geraCoeficientes()
{
	A = rand()%mod * (rand()%2 ? -1 : 1);
	B = rand()%mod * (rand()%2 ? -1 : 1);
	C = rand()%mod * (rand()%2 ? -1 : 1);
	if(A == 0)
	{
		if(rand()%2)
			A = 1;
		else
			A = -1;
	}
}

// função da parábola é f(x) = A*x*x + B*x + C
double f(double x)
{
	return A*x*x + B*x + C;
}

void buscaTernaria()
{
	double esquerda, direita, umTerco, doisTercos;
	esquerda = 0;							// ponteiro da esquerda
	direita = 1e18;							// ponteiro da direita
	int numeroDeIter = 0;					// conta o número de iterações
	bool minimoLocal = true;
	if(A < 0)								// se parábola tem concavidade para cima então é máximo local
		minimoLocal = false;
	if(minimoLocal)						// se é minimo local
	{
		while(direita-esquerda > EPS)
		{
			numeroDeIter++;
			umTerco = esquerda + (direita-esquerda)/3;
			doisTercos = esquerda + 2*(direita-esquerda)/3;
			if(f(doisTercos) < f(umTerco))	// se f(doisTercos) é menor, então está entre [umTerco, direita]
			{
				esquerda = umTerco;
			}
			else							// senão então está entre [esquerda, doisTercos]
			{
				direita = doisTercos;
			}
		}
	}
	else									// analogamente para o máximo local
	{
		while(direita-esquerda > EPS)
		{
			numeroDeIter++;
			umTerco = esquerda + (direita-esquerda)/3;
			doisTercos = esquerda + 2*(direita-esquerda)/3;
			if(f(doisTercos) > f(umTerco))
			{
				esquerda = umTerco;
			}
			else
			{
				direita = doisTercos;
			}
		}
	}
	printf("%s da funcao %lld*x^2 + %lld*x + %lld\n", minimoLocal ? "Minimo local" : "Maximo local", A, B, C);
	printf("possui x = %.5f com f(x) = %.5f\n", direita, f(direita));
}

int main()
{
	srand(time(NULL));
	geraCoeficientes(); // gera os coeficientes A, B e C da parábola
	buscaTernaria();
	return 0;
}