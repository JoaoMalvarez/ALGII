#include <stdio.h>
#include <string.h>
#define LINHAS (10)
#define COLUNAS (50)

int main() {
    char lista_nomes[LINHAS][COLUNAS];
    // popula a matriz
    for (int i = 0; i < LINHAS; i++) {
        fgets(lista_nomes[i], COLUNAS, stdin);
    }
    for (int i = 0; i < LINHAS; i++) {
        printf("%s\n", lista_nomes[i]);
    }

    return 0;
}