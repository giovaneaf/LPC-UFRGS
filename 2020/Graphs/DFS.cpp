/*

Esse código faz um DFS iterativo e recursivo a partir da raiz.
Note que ao contrário do BFS não é possível calcular a menor distância.

Complexidade de tempo:  O ( V + E )
onde V é o número de vértices e E é o número de arestas

*/

#include <bits/stdc++.h>

#define mp make_pair

using namespace std;

typedef long long ll;

int n, m;

void DFSIt(int root, vector<int>* adjacencyList)
{
    vector<bool> seen(n, false);        // vetor de visitados
    stack<int> s;
    s.push(root);                           // inicia a pilha colocando o nodo raiz
    seen[root] = true;                      // marca raiz como visitada
    while(!s.empty())                       // enquanto tiver nodo para processar
    {
        int node = s.top(); 
        printf("Visitando nodo %d...\n", node);
        s.pop();
        for(int neighbor : adjacencyList[node])     // varre todos os vizinhos do nodo atual
        {
            if(!seen[neighbor])
            {
                // caso vizinho não seja visitado, coloca ele na fila para visitar
                seen[neighbor] = true;
                s.push(neighbor);
            }
        }
    }
}

void DFSRec(int node, vector<int>* adjacencyList, vector<bool>& seen)
{
    seen[node] = true;
    printf("Visitando o nodo %d...\n", node);
    for(int neighbor : adjacencyList[node])
    {
        if(!seen[neighbor])
        {
            DFSRec(neighbor, adjacencyList, seen);
        }
    }
}

int main()
{
    n = 7;  // número de nodos
    m = 6;  // número de arestas
    pair<int, int> edges[m] = {mp(4, 5), mp(0, 2), mp(1, 2), mp(0, 3), mp(0, 4), mp(1, 5)};
    vector<int> adjacencyList[n];
    int u, v;   // aresta possui vértices u e v
    // construção do grafo por lista de adjacência
    for(int i = 0; i < m; ++i)
    {
        u = edges[i].first; v = edges[i].second;
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u); // se for bidirecional precisa adicionar a aresta reversa
    }
    int root = 0;
    printf("DFS iterativo...\n");
    DFSIt(root, adjacencyList);        // faz DFS a partir do nodo raiz
    printf("\nDFS recursivo...\n");
    vector<bool> seen(n, false);       // cria vetor de visitados para DFS recursivo
    DFSRec(root, adjacencyList, seen); // faz DFS a partir do nodo raiz
    return 0;
}