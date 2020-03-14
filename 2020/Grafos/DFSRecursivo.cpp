/*

Esse código faz um DFS recursivo a partir da raiz.
Note que ao contrário do BFS não é possível calcular a menor distância.

*/

#include <bits/stdc++.h>

#define mp make_pair

using namespace std;

typedef long long ll;

int n, m;

void DFS(int nodoAtual, vector<int>* adjacencyList, vector<bool>& visitado)
{
	visitado[nodoAtual] = true;
	printf("Visitando o nodo %d\n", nodoAtual);
	for(int vizinho : adjacencyList[nodoAtual])
	{
		if(!visitado[vizinho])
		{
			DFS(vizinho, adjacencyList, visitado);
		}
	}
}

int main()
{
	n = 7;	// número de nodos
	m = 6;	// número de arestas
	pair<int, int> arestas[m] = {mp(4, 5), mp(0, 2), mp(1, 2), mp(0, 3), mp(0, 4), mp(1, 5)};
	vector<int> adjacencyList[n];
	int u, v;	// aresta possui vértices u e v
	// construção do grafo por lista de adjacência
	for(int i = 0; i < m; ++i)
	{
		u = arestas[i].first; v = arestas[i].second;
		adjacencyList[u].push_back(v);
		adjacencyList[v].push_back(u); // se for bidirecional precisa adicionar a aresta reversa
	}
	int raiz = 0;
	vector<bool> visitado(n, false);
	DFS(raiz, adjacencyList, visitado); // faz DFS a partir do nodo raiz
	return 0;
}