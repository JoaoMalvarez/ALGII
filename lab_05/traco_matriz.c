#include <stdio.h>
#include <stdlib.h>
#define LINHAS (4)
#define COLUNAS (4)

void popula_matriz(int matriz[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            printf("Matriz[%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }
}

void imprime_matriz(int matriz[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            printf("%2d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int tracoMatriz(int linhas, int colunas, int matriz[LINHAS][COLUNAS]) {
    int soma = 0;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (i == j) {
                soma += matriz[i][j]; 
            }
        }
    }
    return soma;
}

int main() {
    // declara a matriz
    int matriz[LINHAS][COLUNAS]; 
    popula_matriz(matriz);
    imprime_matriz(matriz);
    int traco = tracoMatriz(LINHAS, COLUNAS, matriz);
    printf("Traço da Matriz: %d\n", traco);
    return 0;   
}