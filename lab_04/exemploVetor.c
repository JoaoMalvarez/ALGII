#include <stdio.h>
#define TAMANHO_VETOR 7

int modificaVetor(int vetor[], int tamanho) {
    int qtde = 0;
    for (int i = 0 ; i < tamanho; i++) {
        if (vetor[i] >= 10 && vetor[i] <= 20) {
            vetor[i] = 0;
            qtde++;
        }
    }
    return qtde;
}

int main() {
    //declara o vetor
    int numeros[TAMANHO_VETOR];
    //popula o vetor
    for (int i = 0; i < TAMANHO_VETOR; i++) {
        printf("Valor[%d]: ", i);
        scanf("%d", &numeros[i]);
    }
    //chama a função criada
    int totalModificacoes = modificaVetor(numeros, TAMANHO_VETOR);
    //apresenta o vetor
    for (int i = 0; i < TAMANHO_VETOR; i++) {
        printf("Valor[%d]: %d\n", i, numeros[i]);
    }
    printf("\n");
    printf("Total de modificações: %d\n", totalModificacoes);
    return 0;
}