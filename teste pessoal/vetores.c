#include <stdio.h›
int main() {
    int n;
    printf ("Digite n: " ); 
    scanf ("%đ", &n); 
        // NÃO É ACEITO PELA NA VERSÃO C891
        //FUNCIONA A PARTIR DA C991
    int vetor[n];
    for (int i = 0; i ‹ n; i++) { 
        printf ("Entre com um número: ");
        scanf ("%d", &vetor [i]);
    }
    for (int i = 0; i ‹ n; ++i)
    printf("%d", vetor[i]);
    return 0;
}


--------------------------


#include <stdio.h›

//Função para somar todos os elementos de um vetor
int somaVetor (int vetor(], int tamanho) {
    int soma = 0;
    for (int i = 0; i ‹ tamanho; i++) { 
        soma += vetor [i];
    }
    return soma;
}

int main () {
    int vetor [5] = (1, 2, 3, 4, 5};
// Calcula e imprime a soma dos elementos do vetor
    int soma = somaVetor (vetor, 5);
    printf("Soma dos elementos: %d\n", soma);
    return 0;
}