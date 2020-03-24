/*

Exponenciação rápida de matrizes modular
Esse código calcula f(n) para a seguinte recorrência:

f(0) = 1
f(1) = 5
f(2) = 9
f(n) = f(n-1) + f(n-3) - 3, para n >= 3

[0 1 0  0]   [ f(n-3)]   [ f(n-2)]
[0 0 1  0]   [ f(n-2)]   [ f(n-1)]
[1 0 1 -1] * [ f(n-1)] = [  f(n) ]
[0 0 0  1]   [   3   ]   [   3   ]

Conseguimos construir essa matriz para calcular f(n) para n grande, pois a cada multiplicação
por essa matriz de coeficiente obtemos o resultado do próximo vetor assim como na de Fibonacci
Esse link mostra como converter recorrência em matriz:
http://fusharblog.com/solving-linear-recurrence-for-programming-contest/

Complexidade de tempo:  O ( log(Expoente) * N^3 )
onde N eh o numero de linhas e colunas da matriz quadrada.

*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define MODN 1000000007  // mod N fornecido pelo problema.

// Multiplica (A * B)%MODN e escreve na matriz C
// A e B podem possuir dimensões distintas
void multiply_matrix_mod (const vector<vector<ll>> A, const vector<vector<ll>> B, vector<vector<ll>>& C) 
{
    // A[i][j] : linha i coluna j.  linha e coluna iniciam em zero.

    int A_ROW = A.size();       // tamanho da linha de A
    int A_COL = A[0].size();    // tamanho da coluna de A = tamanho da linha de B
    int B_COL = B[0].size();    // tamanho da coluna de B
    
    for(int i = 0; i < A_ROW; i++)  // zera a matriz C para guardar valor
    {
        fill(C[i].begin(), C[i].end(), 0);
    }

    for (ll i = 0; i < A_ROW; i++)
    {
        for (ll j = 0; j < B_COL; j++)
        {
            for (ll k = 0; k < A_COL; k++) 
            {
                // Aplicação da multiplicação de matrizes tradicional
                // move coluna na primeira matriz e linha na segunda matriz
                C[i][j] += (A[i][k]  * B[k][j]) % MODN;
                C[i][j] %= MODN;
            }
        }
    }
    
}

/*
Gera a matriz identidade em mat como elemento neutro (usado na variável result do arquivo binaryExponentiation.cpp na função binExpIt, o elemento neutro da multiplicação de inteiros é o número 1)
*/
void make_identity(vector<vector<ll>> &mat)
{
    // mat deve ser matriz quadrada.
    for (unsigned i = 0, l = mat.size(); i < l; i++)
        for (unsigned j = 0; j < l; j++)
            mat[i][j] = (i == j);
}

//  Calcula a matrix^exp e a resposta está em res
//  Para a multiplicação de matrizes se usa result do mesmo tamanho de matrix, logo
//  elas possuem a mesma dimensão e também elas tem que ser quadradas, ou seja, mesmo
//  número de linhas e colunas
void mat_mod_fastexp(vector<vector<ll>> matrix, ll exp, vector<vector<ll>> &result) 
{
    make_identity(result);  // res é a result do arquivo binaryExponentiation.cpp na função binExpIt
    while (exp > 0) 
    { 
        if (exp & 1) 
            multiply_matrix_mod(result, matrix, result);
        exp = exp >> 1; 
        multiply_matrix_mod(matrix, matrix, matrix);
    } 
}

const int N = 4;    // tamanho da matriz

ll f(ll n)  // calcula f(n)
{
    vector<vector<ll>> initial(4, vector<ll>(1, 0));
    // preenche matriz com valores iniciais
    /*
        [ f(0) ]
        [ f(1) ]
        [ f(2) ]
        [  3   ]
    */
    initial = {{1}, {5}, {9}, {3}};
    if(n < 3)
        return initial[n][0];
    vector<vector<ll>> mat(N, vector<ll>(N, 0));    // cria matriz NxN
    vector<vector<ll>> result(N, vector<ll>(N, 0)); // cria matriz da resposta NxN
    // preenche a matriz com coeficientes obtidos da recorrência
    mat = {{0, 1, 0, 0}, {0, 0, 1, 0}, {1, 0, 1, -1}, {0, 0, 0, 1}};
    mat_mod_fastexp(mat, n-2, result);              // realiza a exponenciação rápida
    vector<vector<ll>> ans(4, vector<ll>(1));
    // multiplica a matriz resultado da exponenciação (result) com
    // o vetor inicial chamado initial e guarda o valor em ans
    multiply_matrix_mod(result, initial, ans);
    return ans[2][0];   // retorna a posição f(n)
}

int main()
{
    ll n;
    while(cin >> n)
    {
        printf("%lld\n", f(n));
    }
    return 0;
}