/*

Esse código cria uma equação de parábola aleatória com geração randômica dos coeficientes A, B e C.
Relembrando que a equação da parábola é f(x) = A * x^2 + B * x + C

A ideia da busca ternária é encontrar o máximo/mínimo global quando há uma função unimodal, ou seja,
quando há um ponto x em que a função cresce para x < m e decresce para x > m ou vice-versa e o objetivo
é encontrar esse máximo/mínimo global x.

Note que a parábola é uma função unimodal e então sempre encontrará esse máximo/mínimo local

Esse algoritmo encontra o mínimo global (se A > 0) ou máximo local (se A < 0) entre os limites
da busca que é o intervalo [-10^18, 10^18] quando utilizada a função ternarySearchFrac que utiliza
valores fracionários.

Também há a versão inteira em ternarySearchInt onde o intervalo de busca é [-10^5, 10^5] para 
evitar overflow quando elevado ao quadrado e multiplicado pelos coeficientes. Note que a versão
inteira tem uma pequena modificação na condição de parada sendo necessário parar quando o intervalo
de busca for menor que 3 pois não podemos dividir em 3 regiões, logo quando a diferença for menor que
3 precisamos percorrer o intervalo de busca e encontrar o máximo ou mínimo global da função.

Complexidade de tempo:  O ( log(N) )
onde N é o tamanho do intervalo, note que na versão fracionária
o intervalo é infinito por isso criamos uma condição de parada
para que quando os valores estiverem muito próximos o algoritmo termine

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define EPS 1e-9
#define INF 0x3f3f3f3f

const int mod = 1e2+1;
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

// função da parábola para valores inteiros
ll f(ll x)
{
    return A*x*x + B*x + C;
}

void ternarySearchFrac()    // busca ternária com valores fracionários
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
        // enquanto quando os dois números não estiverem muito próximos (10^(-9))
        while(right-left > EPS)
        {
            numeroDeIter++;
            oneThird = left + (right-left)/3.0;
            twoThirds = left + 2.0*(right-left)/3.0;
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
            oneThird = left + (right-left)/3.0;
            twoThirds = left + 2.0*(right-left)/3.0;
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

void ternarySearchInt() // busca ternária com valores inteiros
{
    // ans armazenará o valor do mínimo ou máximo local
    ll left, right, oneThird, twoThirds, ans, fans, tmp;
    // valores inicializados com 10^5 para evitar overflow quando
    // elevado ao quadrado e multiplicado pelos coeficientes
    left = -100000;                             // ponteiro da esquerda
    right = 100000;                             // ponteiro da direita
    int numeroDeIter = 0;                       // conta o número de iterações
    bool globalMinima = true;
    if(A < 0)                                   // se parábola tem concavidade para cima então é máximo local
        globalMinima = false;
    if(globalMinima)                            // se é minimo local
    {
        // enquanto a diferença entre dois números for pelo menos 3, 
        // ou seja dá para dividir em 3 regiões distintas
        while(right-left > 2)
        {
            numeroDeIter++;
            oneThird = left + (right-left)/3;
            twoThirds = left + (2*(right-left))/3;
            if(f(twoThirds) < f(oneThird))  // se f(twoThirds) é menor, então está entre [oneThird, right]
            {
                left = oneThird;
            }
            else                            // senão então está entre [left, twoThirds]
            {
                right = twoThirds;
            }
        }
        fans = f(left);                     // ans vai armazenar a resposta, inicialmente left
        ans = left;
        for(ll i = left+1; i <= right; ++i) // varre até right para encontrar o mínimo local
        {
            tmp = f(i);
            if(tmp < fans)
            {
                fans = tmp;
                ans = i;
            }
        }
    }
    else                                    // analogamente para o máximo local
    {
        while(right-left > 2)
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
        fans = f(left);
        ans = left;                         // ans vai armazenar a resposta, inicialmente left
        for(ll i = left+1; i <= right; ++i) // varre até right para encontrar o máximo local
        {
            tmp = f(i);
            if(tmp > fans)
            {
                fans = tmp;
                ans = i;
            }
        }
    }
    printf("%s da funcao %lld*x^2 + %lld*x + %lld\n", globalMinima ? "Minimo local" : "Maximo local", A, B, C);
    printf("possui x = %lld com f(x) = %lld\n", ans, f(ans));
}




int main()
{
    srand(time(NULL));
    genCoefficients(); // gera os coeficientes A, B e C da parábola
    ternarySearchFrac();
    ternarySearchInt();
    return 0;
}