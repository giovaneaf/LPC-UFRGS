/*

Esse código executa o algoritmo do toposort.
Note que nodos "filhos", ou seja, com grau de entrada maior que 0 só serão processados após os nodos "pais"
Também é necessário que o grafo seja um DAG (Directed Acyclic Graph)

Existem duas formas de fazer o toposort, uma forma é processar os nodos enquanto executa a ordem topológica
que está representado na função chamada de toposort.
Outra forma é calcular a ordem da ordem topológica primeiro e depois processar os nodos nessa ordem que
está representado na função chamada de computeOrder e a ordem é guardada na pilha chamada de order.

Complexidade de tempo:  O ( V + E )
onde V é o número de vértices e E é o número de arestas

*/

#include <bits/stdc++.h>

#define mp make_pair

using namespace std;

typedef long long ll;

int n, m;

// Algoritmo que processa os nodos durante 
void toposort(vector<int>* adjacencyList)
{
	vector<int> inDegree(n, 0); 	// inicializa vetor de grau de Entrada
	for(int node = 0; node < n; ++node)
	{
		for(int neighbor : adjacencyList[node])
		{
			inDegree[neighbor]++; 	// incrementa o grau de entrada do vizinho
		}
	}
	queue<int> q; 		// fila de nodos a serem processados
	for(int node = 0; node < n; ++node)
	{
		if(inDegree[node] == 0) // se não tem "pais" então nodo pode ser processado
		{
			q.push(node);
		}
	}
	while(!q.empty())
	{
		int curNode = q.front();
		q.pop();
		printf("Visitando nodo %d...\n", curNode);
		for(int neighbor : adjacencyList[curNode])
		{
			inDegree[neighbor]--; 	// decrementa o grau de entrada do vizinho (pai já foi processado)
			if(inDegree[neighbor] == 0)
			{
				// se todos os "pais" foram processados então nodo pode ser processado
				q.push(neighbor);
			}
		}
	}
}

void computeOrder(int node, vector<int>* adjacencyList, stack<int>& order, vector<bool>& seen)
{
	seen[node] = true;
	for(int vizinho : adjacencyList[node])
	{
		if(!seen[vizinho])
			computeOrder(vizinho, adjacencyList, order, seen);
	}
	order.push(node);
}

int main()
{
	n = 6;	// número de nodos
	m = 7;	// número de arcos (aresta direcionada)
	pair<int, int> arc[m] = {mp(0, 3), mp(0, 2), mp(0, 4), mp(2, 1), mp(1, 5), mp(4, 5), mp(4, 2)};
	vector<int> adjacencyList[n];
	int u, v;	// aresta possui vértices u e v
	// construção do grafo por lista de adjacência
	for(int i = 0; i < m; ++i)
	{
		u = arc[i].first; v = arc[i].second;
		adjacencyList[u].push_back(v);
	}
	printf("Primeira maneira...\n");
	toposort(adjacencyList);	// realiza o algoritmo toposort (1ª maneira)
	putchar('\n');
	printf("Segunda maneira...\n");
	// realiza o algoritmo toposort (2ª maneira)
	stack<int> order;				// pilha que guarda a ordem topológica
	vector<bool> seen(n, false); 	// vetor de visitados
	for(int nodo = 0; nodo < n; ++nodo)
	{
		if(!seen[nodo])
		{
			computeOrder(nodo, adjacencyList, order, seen);
		}
	}
	while(!order.empty())
	{
		printf("Visitando nodo %d...\n", order.top());
		order.pop();
	}
	return 0;
}