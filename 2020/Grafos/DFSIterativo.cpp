/*

Esse código faz um DFS iterativo a partir da raiz.
Note que ao contrário do BFS não é possível calcular a menor distância.

*/

#include <bits/stdc++.h>

#define mp make_pair

using namespace std;

typedef long long ll;

int n, m;

void DFS(int raiz, vector<int>* adjacencyList)
{
	vector<bool> visitado(n, false); 		// vetor de visitados
	stack<int> s;
	s.push(raiz);							// inicia a pilha colocando o nodo raiz
	visitado[raiz] = true;					// marca raiz como visitada
	while(!s.empty())						// enquanto tiver nodo para processar
	{
		int nodoAtual = s.top();	
		printf("Visitando nodo %d\n", nodoAtual);
		s.pop();
		for(int vizinho : adjacencyList[nodoAtual])		// varre todos os vizinhos do nodo atual
		{
			if(!visitado[vizinho])
			{
				// caso vizinho não seja visitado, coloca ele na fila para visitar
				visitado[vizinho] = true;
				s.push(vizinho);
			}
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
	DFS(raiz, adjacencyList); // faz DFS a partir do nodo raiz
	return 0;
}