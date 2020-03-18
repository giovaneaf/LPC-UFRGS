/*

Esse código faz um Dijkstra a partir da raiz calculando a menor distância entre a raiz e qualquer outro nodo

*/

#include <bits/stdc++.h>

#define mp make_pair
#define INF 1000000000

using namespace std;

typedef long long ll;

int n, m;

void Dijkstra(int root, vector<pair<int, int>>* adjacencyList)
{
	vector<int> dist(n, INF); 	// vetor que armazena a distância até o nodo, inicialmente infinito
	// fila de prioridades para escolher nodo de menor distância de maneira eficiente
	// os valores inseridos nesse par são (custo até o nodo, nodo)
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	dist[root] = 0;
	pq.push(mp(dist[root], root));	// insere raiz com distância zero para ser explorada
	while(pq.size())
	{
		int node = pq.top().second;	// nodo a ser explorado
		int curCost = pq.top().first;
		pq.pop();
		// se o nodo já foi explorado então vai para o próximo (pode ser usado um vetor booleano auxiliar)
		if(curCost > dist[node])
			continue;
		for(pair<int, int> p : adjacencyList[node])		// processa a aresta
		{
			int neighbor = p.first;			// vizinho
			int cost = p.second;			// custo da aresta
			if(dist[neighbor] > dist[node] + cost)	// se existe um caminho mais curto
			{
				dist[neighbor] = dist[node] + cost; 	// atualiza para esse caminho
				pq.push(mp(dist[neighbor], neighbor));	// insere como nodo a ser explorado
			}
		}
	}
	printf("Comecando pelo nodo %d...\n", root);
	for(int i = 0; i < n; ++i)
	{
		if(dist[i] < INF)
			printf("A menor distancia ate o nodo %d = %d...\n", i, dist[i]);
		else
			printf("Nao e possivel chegar no nodo %d...\n", i);
	}
}

int main()
{
	n = 7; 	// número de nodos
	m = 9;	// número de arestas
	pair<int, int> edges[m] = {mp(4, 5), mp(0, 2), mp(1, 2), mp(0, 3), mp(0, 4), mp(1, 5), mp(0, 1), mp(2, 3), mp(3, 4)};
	int cost[m] = {5, 7, 2, 3, 4, 1, 6, 1, 1};
	vector<pair<int, int>> adjacencyList[n];
	int u, v;	// aresta possui vértices u e v
	// construção do grafo por lista de adjacência
	for(int i = 0; i < m; ++i)
	{
		u = edges[i].first; v = edges[i].second;
		adjacencyList[u].push_back(mp(v, cost[i]));
		adjacencyList[v].push_back(mp(u, cost[i])); // se for bidirecional precisa adicionar a aresta reversa
	}
	int root = 0;
	Dijkstra(root, adjacencyList); // realiza Dijkstra a partir de root
	return 0;
}