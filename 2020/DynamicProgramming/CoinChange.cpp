/*

Esse código computa, dado "m" moedas disponíveis com quantidade ilimitada,
o menor número de moedas necessárias para formar o valor "n".

Complexidade de tempo:  O ( n*m )
onde n é a quantidade que deseja formar e m é o número de moedas disponíveis

*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
 
#define mp(a, b) make_pair(a, b)
#define INFLL 0x3f3f3f3f3f3f3f3f
#define MAXN 251
#define MAXM 51

int n, m;			// n é a quantidade e m é o número de moedas disponíveis

ll memo[MAXN];		// tabela de memoização (programação dinâmica)
int coin[MAXM];

ll coinChange(int n, int m)
{
	// não tem como fazer moedas com valor maior que zero
	// a partir de nenhuma moeda disponível
	memset(memo, 0, sizeof(memo));
	memo[0] = 1; 	// 1 maneira de fazer 0 com 0 moedas
	for(int i = 0; i < m; ++i)		// para cada moeda disponível
	{
		for(int j = 0; j <= n; ++j)  // para cada quantidade possível
		{
			if(coin[i] <= j) 		 // se for possível adicionar essa moeda
			{
				// número de maneiras sem a moeda + número de maneiras com a moeda atual,
				// ou seja, número de maneiras da quantidade - moeda atual
				memo[j] += memo[j-coin[i]];
			}
		}
	}
	return memo[n];	// retorna o número de maneiras de fazer n com as m moedas
}

int main()
{
	cin >> n >> m;
	for(int i = 0; i < m; ++i) 	// ler o valor das m moedas disponíveis
		cin >> coin[i];
	printf("O menor num. de moedas para %d eh usar %lld moedas\n", n, coinChange(n, m));
	return 0;
}