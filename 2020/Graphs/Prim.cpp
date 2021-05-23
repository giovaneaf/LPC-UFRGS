/*

Esse código calcula a árvore geradora mínima com o algoritmo de Prim (muito parecido com Dijkstra)

Complexidade de tempo:  O ( V + E * log(V) )
onde V é o número de vértices e E é o número de arestas

*/

#include <bits/stdc++.h>

#define mp make_pair
#define INF 1000000000

using namespace std;

typedef long long ll;
// aqui for necessário usar um typedef para pair<int, int> devido ao tamanho da declaração da fila de prioridades
typedef pair<int, int> ii;

int n, m;

void Prim(int root, vector<pair<int, int>>* adjacencyList)
{
    vector<int> dist(n, INF);       // vetor que armazena a distância até o nodo, inicialmente infinito
    vector<bool> seen(n, false);    // vetor de visitado
    // fila de prioridades para escolher nodo de menor distância de maneira eficiente
    // os valores inseridos nesse par de int e par são 
    // (custo para inserir vizinho na árvore, (nodo, vizinho))
    priority_queue<pair<int, ii>, vector<pair<int, ii>>, greater<pair<int, ii>>> pq;
    dist[root] = 0;
    pq.push(mp(dist[root], mp(root, -1)));  // insere a raiz com custo zero para ser explorada e sem vizinho (-1)
    vector<pair<int, ii>> edges;    // guarda a resposta das arestas utilizadas
    int mstCost = 0;                // guarda o custo total da árvore
    while(pq.size())
    {
        int node = pq.top().second.first;   // nodo a ser explorado
        int curCost = pq.top().first;       // custo para inserir a aresta
        int neighborNode = pq.top().second.second; // vizinho, a aresta é (node, neighborNode) com custo curCost
        pq.pop();
        // se o nodo já foi explorado então já está na árvore, não adiciona de novo
        if(seen[node])
            continue;
        seen[node] = true;
        if(neighborNode != -1)
        {
            edges.push_back(mp(curCost, mp(neighborNode, node)));   // insere aresta na resposta
            mstCost += curCost;                                     // incrementa o custo da árvore
        }
        for(pair<int, int> p : adjacencyList[node])     // processa a aresta
        {
            int neighbor = p.first;         // vizinho
            int cost = p.second;            // custo da aresta
            if(dist[neighbor] > cost)       // se existe uma aresta com custo menor
            {
                dist[neighbor] = cost;                  // atualiza para essa aresta
                pq.push(mp(dist[neighbor], mp(neighbor, node)));    // insere como nodo a ser explorado
            }
        }
    }
    printf("Arvore geradora minima tem custo %d...\n", mstCost);
    for(pair<int, ii> edge : edges)
    {
        printf("Aresta (%d, %d) inserida na arvore com custo %d...\n", edge.second.first, edge.second.second, edge.first);
    }
}

int main()
{
    n = 7;  // número de nodos
    m = 9;  // número de arestas
    pair<int, int> edges[m] = {mp(4, 5), mp(0, 2), mp(1, 2), mp(0, 3), mp(0, 4), mp(1, 5), mp(0, 1), mp(2, 3), mp(3, 6)};
    int cost[m] = {5, 7, 2, 3, 4, 1, 6, 1, 1};
    vector<pair<int, int>> adjacencyList[n];
    int u, v;   // aresta possui vértices u e v
    // construção do grafo por lista de adjacência
    for(int i = 0; i < m; ++i)
    {
        u = edges[i].first; v = edges[i].second;
        adjacencyList[u].push_back(mp(v, cost[i]));
        adjacencyList[v].push_back(mp(u, cost[i])); // se for bidirecional precisa adicionar a aresta reversa
    }
    int root = 0;
    Prim(root, adjacencyList);                   // realiza o algoritmo de Prim a partir de root (não importa a raiz)
    return 0;
}