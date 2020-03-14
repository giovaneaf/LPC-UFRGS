/*

Esse código faz um BFS a partir da raiz calculando a menor distância entre a raiz e qualquer outro nodo

*/

#include <bits/stdc++.h>

#define mp make_pair

using namespace std;

typedef long long ll;

int n, m;

void BFS(int raiz, vector<int>* adjacencyList)
{
	vector<int> distancia(n, -1); 	// a distância até qualquer nodo é desconhecida (por default -1)
	queue<int> q;
	q.push(raiz);					// inicia a fila colocando o nodo raiz
	distancia[raiz] = 0;			// a distância até a raiz é 0
	while(!q.empty())				// enquanto tiver nodo para processar
	{
		int nodoAtual = q.front();	
		printf("Visitando nodo %d com distancia %d\n", nodoAtual, distancia[nodoAtual]);
		q.pop();
		for(int vizinho : adjacencyList[nodoAtual])		// varre todos os vizinhos do nodo atual
		{
			if(distancia[vizinho] == -1)
			{
				// se vizinho não foi alcançado, sua distância é 1 + distância do nodo atual
				distancia[vizinho] = 1 + distancia[nodoAtual];
				q.push(vizinho);
			}
		}
	}
	printf("\nPartindo do nodo %d as distancias sao:\n\n", raiz);
	for(int i = 0; i < n; ++i)
	{
		if(distancia[i] == -1)
		{
			printf("Nodo %d nao pode ser alcancado\n", i);
		}
		else
		{
			printf("Nodo %d tem distancia %d\n", i, distancia[i]);
		}
	}
}

int main()
{
	n = 7; 	// número de nodos
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
	BFS(raiz, adjacencyList); // faz BFS a partir do nodo raiz
	return 0;
}