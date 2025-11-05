#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *file;

    file = fopen(argv[1], "r"); //r = ler | r+ = le, substitui
                                //w =substitui o texto | w+ = le, escreve e substitui
                                //a = escrita no final | a+ = le, escreve e adicona no final
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char palavra[50];
    fscanf(file, "%s", palavra); //fscan (normal) + f (file) = fscanf
    printf("Valor lido: %s\n", palavra);
    
/*
    int tamanho;
    int valor;
    fscanf(file, "%ls", &tamanho);
    for (int i = 0; i < tamanho; i++) {
        fscanf(file, "%d\n", &valor);
        printf("%d", valor);
    }
*/

    char linha[100];
    while (fgets(linha, sizeof(linha), file) != NULL) { //fgets = mostra o max
        printf("Valor lido da Linha: %s\n", linha);
    }
    fclose(file);
    return 0;
}