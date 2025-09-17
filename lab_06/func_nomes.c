#include <stdio.h>
#include <string.h>
#define LINHAS (10)
#define COLUNAS (50)

int busca_nome(int linhas, int colunas, char nomes[linhas][colunas], char nome[]) {
    for (int i = 0; i < linhas; i++) {
        if (strcasecmp(nomes[i], nome) == 0) { // strcasecmp faz a comparação ignorando maiúsculas e minúsculas
            return i;
        }
    }
    return -1; // -1 já que não representa um índice válido, sem poder usar o 0 já que é um índice válido começando com 0 a lista
}

int main() {
    char lista_nomes[LINHAS][COLUNAS];
    char nome[COLUNAS];
    // popula a matriz
    for (int i = 0; i < LINHAS; i++) {
        fgets(lista_nomes[i], COLUNAS, stdin);
    }
    printf("*** LISTA DE NOMES ***\n"); 
    for (int i = 0; i < LINHAS; i++) {
        printf("%s\n", lista_nomes[i]);
    }
    printf("********************\n");
    fgets(nome, COLUNAS, stdin);
    printf("Nome a ser buscado: %s\n", nome);
    int pos = busca_nome(LINHAS, COLUNAS, lista_nomes, nome);
    printf("Posição do nome na lista: %d\n", pos);

    return 0;
}