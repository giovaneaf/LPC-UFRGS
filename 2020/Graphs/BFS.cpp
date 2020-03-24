/*

Esse código faz um BFS a partir da raiz calculando a menor distância entre a raiz e qualquer outro nodo

Complexidade de tempo:  O ( V + E )
onde V é o número de vértices e E é o número de arestas

*/

#include <bits/stdc++.h>

#define mp make_pair

using namespace std;

typedef long long ll;

int n, m;

void BFS(int root, vector<int>* adjacencyList)
{
	vector<int> dist(n, -1);		// vetor de distâncias
									// a distância até qualquer nodo é desconhecida (por default -1)
	queue<int> q;
	q.push(root);					// inicia a fila colocando o nodo raiz
	dist[root] = 0;					// a distância até a raiz é 0
	while(!q.empty())				// enquanto tiver nodo para processar
	{
		int node = q.front();	
		printf("Visitando nodo %d com distancia %d...\n", node, dist[node]);
		q.pop();
		for(int neighbor : adjacencyList[node])		// varre todos os vizinhos do nodo atual
		{
			if(dist[neighbor] == -1)
			{
				// se vizinho não foi alcançado, sua distância é 1 + distância do nodo atual
				dist[neighbor] = 1 + dist[node];
				q.push(neighbor);
			}
		}
	}
	printf("\nPartindo do nodo %d as distancias sao:\n\n", root);
	for(int nodo = 0; nodo < n; ++nodo)
	{
		if(dist[nodo] == -1)
		{
			printf("Nodo %d nao pode ser alcancado\n", nodo);
		}
		else
		{
			printf("Nodo %d tem distancia %d\n", nodo, dist[nodo]);
		}
	}
}

int main()
{
	n = 7; 	// número de nodos
	m = 6;	// número de arestas
	pair<int, int> edges[m] = {mp(4, 5), mp(0, 2), mp(1, 2), mp(0, 3), mp(0, 4), mp(1, 5)};
	vector<int> adjacencyList[n];
	int u, v;	// aresta possui vértices u e v
	// construção do grafo por lista de adjacência
	for(int i = 0; i < m; ++i)
	{
		u = edges[i].first; v = edges[i].second;
		adjacencyList[u].push_back(v);
		adjacencyList[v].push_back(u); // se for bidirecional precisa adicionar a aresta reversa
	}
	int root = 0;
	BFS(root, adjacencyList); // faz BFS a partir do nodo raiz
	return 0;
}