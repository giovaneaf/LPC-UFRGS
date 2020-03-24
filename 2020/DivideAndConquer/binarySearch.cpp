/*

Esse código faz uma busca binária em um valor que deve ser adivinhado.
O usuário insere o maior valor possível para o número escolhido e o número escolhido é gerado
aleatoriamente entre [0, maior valor possível] após isso mostrará qual o valor escolhido e então mostrará
os passos da busca binária até encontrar esse valor.

Complexidade de tempo:  O ( log(N) )
onde N é o maior valor possível

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void binarySearch(ll maxValue)
{
    // left é o ponteiro da esquerda, right é ponteiro da direita da busca binária
    // maxValue é o maior valor escolhido pelo usuário
    ll left, right, chosenNumber, mid;
    chosenNumber = rand()%(maxValue+1);     // gera um número aleatório entre 0 e maxValue
    left = 0;                   // ponteiro da esquerda
    right = maxValue;               // ponteiro da direita
    int numIter = 0;                // conta o número de iterações
    printf("Valor a ser adivinhado = %lld...\n", chosenNumber);
    getchar();
    printf("Pressione qualquer tecla para continuar e aparecer as iteracoes...\n"); 
    getchar();
    while(right >= left)
    {
        numIter++;
        mid = left + (right-left)/2;
        printf("Chute atual = %lld...\n", mid);
        if(mid == chosenNumber)             // se encontrou, mostra o número de iterações
        {
            printf("Encontrou o valor com %d it.\n", numIter);
            break;
        }
        else if(mid < chosenNumber)         // se chute é menor então atualiza o ponteiro da esquerda
        {
            left = mid+1;
        }
        else                                // se chute é maior então atualiza o ponteiro da direita
        {
            right = mid-1;
        }
    }
}

int main()
{
    srand(time(NULL));
    ll maxValue;
    printf("Insira o maior valor da busca binaria: ");
    while(cin >> maxValue)
    {
        binarySearch(maxValue);
        printf("Insira o maior valor da busca binaria: ");
    }
    return 0;
}