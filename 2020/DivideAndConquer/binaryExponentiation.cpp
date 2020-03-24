/*

Exponenciação rápida de números inteiros modular
Esse código calcula (base^exp)%modulo onde % é o resto da divisão inteira.
o módulo é muito utilizado aqui porque os números podem ser muito grandes 
e dar overflow nas variáveis.
Geralmente se usa o módulo de um número primo grande porque tem 
menos chance de dar colisão (já que o primo só divide 1 e ele mesmo)
para eles testarem o resultado.

O usuário insere a base e o expoente e a função binExpRec calcula recursivamente o resultado,
já a função binExpIt calcula iterativamente o resultado.

Complexidade de tempo:  O ( log(Expoente) )

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll modulo = 1e9+7;


ll binExpRec(ll base, ll exp, ll modulo)
{
	if(exp == 0) 					// se o expoente é zero então retorna 1
		return 1LL;
	if(exp&1) 						// se é ímpar
		return (base*binExpRec(base, exp-1, modulo))%modulo;
	return binExpRec((base*base)%modulo, exp/2, modulo);			// se é par
}

ll binExpIt(ll base, ll exp, ll modulo)
{
	ll result = 1LL;
	while(exp > 0LL)			// termina quando expoente é zero
	{
		if(exp&1) 				// parte ímpar	
		{
			result = (result*base)%modulo;
		}
		base = (base*base)%modulo;		// parte par
		// note que é feita a divisão inteira com ceiling em C/C++, então
		// se exp é ímpar ou par não importa, pois ele calculará exp/2 se par
		// e (exp-1)/2 se ímpar
		exp /= 2;
	}
	return result;
}

int main()
{
	ll base, exp;	// base é a base e exp é o expoente
	printf("Digite a base: ");
	cin >> base;
	printf("Digite a expoente: ");
	cin >> exp;
	printf("Resultado Recursivo...\n");
	printf("O valor de %lld elevado na %lld modulo %lld e %lld\n", base, exp, modulo, binExpRec(base, exp, modulo));
	printf("\nResultado Iterativo...\n");
	printf("O valor de %lld elevado na %lld modulo %lld e %lld\n", base, exp, modulo, binExpIt(base, exp, modulo));
	return 0;
}