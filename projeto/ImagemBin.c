#include <stdio.h>
#include <stdlib.h>

void abrirArquivo() { //abre o arquivo e fica disponivel para ler
    FILE *file;
    file = fopen("imagem.pbm", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    char linha [100];
    while(!feof(file)) {
        if (fgets(linha, sizeof(linha), file) != NULL) {
            printf("%s", linha);
        }
    if (fgets(linha, sizeof(linha), file) != NULL) {
    scanf("%s %s", col, lin)
    }
}

void separaImagem() { // vai separar a imagem em quadrantes
                    //lembrando, se o n ou m forem numeros impares, é para arredondar para cima (ao dividir no meio)

}

char codificaImagem() { //vai traduzir os quadrantes (P = Preto, B = Branco, X = começo do bloco)
                        //lembrando, se o quadrante inteiro for da msm cor, só coloca um "P" ou "B"
}



int main() {
    verificaImagem();

        
    fclose(file);
    return 0;
}