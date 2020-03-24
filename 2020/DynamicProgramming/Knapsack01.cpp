/*

Esse código computa o maior valor para cada capacidade da mochila sem repetição.
Há a versão bottom-up e a versão top-down.

Note que na versão bottom-up é necessário preencher toda a tabela de memoização
enquanto que a top-down só calcula os estados necessários para calcular o máximo
de uma capacidade fixa (que está setado em 10)

Complexidade de tempo:  O ( N*W )
onde N é o número de elementos e W é a maxCapacity, ou seja, 
a capacidade máxima que pode ser carregada.

*/

#include <bits/stdc++.h>

#define mp make_pair
#define INF 1000000000

using namespace std;

typedef long long ll;

const int n = 4;
const int maxCapacity = 17;

int weight[] = {2, 3, 5, 7};			// peso dos ítens
int	value[] =  {5, 3, 10, 6};			// valor dos ítens

int memo[n][maxCapacity+1];				// tabela de memoização (programação dinâmica)

void KnapsackBU()
{
	for(int curW = 0; curW <= maxCapacity; ++curW)	// para cada capacidade
	{
		if(curW < weight[0])		// se não consegue colocar na mochila 
			memo[0][curW] = 0;
		else 						// caso contrário, o máximo é colocar o item na mochila
			memo[0][curW] = value[0];
	}
	for(int item = 1; item < n; ++item) 	// para cada outro item
	{
		for(int curW = 0; curW <= maxCapacity; ++curW)	// para cada capacidade
		{
			memo[item][curW] = memo[item-1][curW];
			// se é possível colocar item atual na mochila pega o melhor entre colocar ou não o item na mochila
			if(curW >= weight[item])
			{
				memo[item][curW] = max(memo[item][curW], value[item] + memo[item-1][curW-weight[item]]);
			}
		}
	}
	for(int curW = 0; curW <= maxCapacity; ++curW)	// para cada capacidade
	{
		printf("Com capacidade %d posso conseguir um valor maximo de %d...", curW, memo[n-1][curW]);
		
		// Recuperando os itens escolhidos percorrendo a matriz ao contrário
		int tmpj = curW;
		printf("Itens escolhidos = { ");
		for(int tmpi = n-1; tmpi >= 0; tmpi--)
		{
			if(memo[tmpi][tmpj] == 0) break;
			if(tmpi > 0 && memo[tmpi][tmpj] == memo[tmpi-1][tmpj])
				continue;
			printf("%d ", tmpi);
			tmpj -= weight[tmpi];
		}
		printf("}\n");
	}
}

int KnapsackTD(int item, int curW)
{
	if(item >= n || curW == 0) 		// se não tem mais oq colocar então o máximo é zero
		return 0;
	if(memo[item][curW] == -1)		// se ainda não calculou para esse estado
	{
		int ans = KnapsackTD(item+1, curW);
		if(curW >= weight[item])
			ans = max(ans, value[item] + KnapsackTD(item+1, curW - weight[item]));
		memo[item][curW] = ans;
	}
	return memo[item][curW];
}

void recoverAnswer(int curW)
{
	printf("Itens escolhidos = { ");
	for(int item = 0; item < n; ++item)
	{
		if(memo[item][curW] <= 0) break;
		if(item < n-1 && memo[item][curW] == memo[item+1][curW])
			continue;
		printf("%d ", item);
		curW -= weight[item];
	}
	printf("}\n");
}

int main()
{
	printf("Problema da mochila versao bottom up...\n");
	KnapsackBU();					// problema da mochila resolvido bottom-up
	printf("\nProblema da mochila versao top down...\n");
	memset(memo, -1, sizeof(memo));	// necessária inicialização da tabela de memoização
	int curW = 10;
	KnapsackTD(0, curW);				// problema da mochila resolvido top-down
	printf("Com capacidade %d posso conseguir um valor maximo de %d...", curW, memo[0][curW]);
	recoverAnswer(curW);					// função para recuperar a resposta quando top-down
	return 0;
}