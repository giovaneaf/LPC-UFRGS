/*

Esse código cria uma equação de parábola aleatória com geração randômica dos coeficientes A, B e C.
Relembrando que a equação da parábola é f(x) = A * x^2 + B * x + C

Esse algoritmo encontra o mínimo global (se A > 0) ou máximo local (se A < 0) entre os limites
da busca que é o intervalo [-10^18, 10^18].

A ideia da busca ternária é encontrar o máximo/mínimo global quando há uma função unimodal, ou seja,
quando há um ponto x em que a função cresce para x < m e decresce para x > m ou vice-versa e o objetivo
é encontrar esse máximo/mínimo global x.

Note que a parábola é uma função unimodal e então sempre encontrará esse máximo/mínimo local

Complexidade de tempo:  O ( log(N) )
onde N é o tamanho do intervalo [-10^18, 10^18] que é 2*10^18

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define EPS 1e-9

const int mod = 1e4+1;
ll A, B, C;

void genCoefficients()
{
    A = rand()%mod * (rand()%2 ? -1 : 1);
    B = rand()%mod * (rand()%2 ? -1 : 1);
    C = rand()%mod * (rand()%2 ? -1 : 1);
    if(A == 0)
    {
        if(rand()%2)
            A = 1;
        else
            A = -1;
    }
}

// função da parábola é f(x) = A*x*x + B*x + C
double f(double x)
{
    return A*x*x + B*x + C;
}

void ternarySearch()
{
    double left, right, oneThird, twoThirds;
    left = -1e18;                           // ponteiro da esquerda
    right = 1e18;                           // ponteiro da direita
    int numeroDeIter = 0;                   // conta o número de iterações
    bool globalMinima = true;
    if(A < 0)                               // se parábola tem concavidade para cima então é máximo local
        globalMinima = false;
    if(globalMinima)                        // se é minimo local
    {
        while(right-left > EPS)
        {
            numeroDeIter++;
            oneThird = left + (right-left)/3;
            twoThirds = left + 2*(right-left)/3;
            if(f(twoThirds) < f(oneThird))  // se f(twoThirds) é menor, então está entre [oneThird, right]
            {
                left = oneThird;
            }
            else                            // senão então está entre [left, twoThirds]
            {
                right = twoThirds;
            }
        }
    }
    else                                    // analogamente para o máximo local
    {
        while(right-left > EPS)
        {
            numeroDeIter++;
            oneThird = left + (right-left)/3;
            twoThirds = left + 2*(right-left)/3;
            if(f(twoThirds) > f(oneThird))
            {
                left = oneThird;
            }
            else
            {
                right = twoThirds;
            }
        }
    }
    printf("%s da funcao %lld*x^2 + %lld*x + %lld\n", globalMinima ? "Minimo local" : "Maximo local", A, B, C);
    printf("possui x = %.5f com f(x) = %.5f\n", right, f(right));
}

int main()
{
    srand(time(NULL));
    genCoefficients(); // gera os coeficientes A, B e C da parábola
    ternarySearch();
    return 0;
}