#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRETO 1
#define BRANCO 0

//--------------------------------------------

typedef struct {
    int largura;
    int altura;
    int **data; /* Como funciona? ele aponta duas coisas, 
                   Primeiro: o ponteiro que aponta para o começo de uma linha de pixels
                   Segundo: o ponteiro principal que aponta para cada linha
                   Assim: {data} -> [Linha 0, Linha 1, Linha 2, ...]
                          {Linha 0} -> [P_0, P_1, P_2, ...]
                */
} Imagem;

//--------------------------------------------

Imagem* criarImagem(int largura, int altura) {
    Imagem *img_ptr = (Imagem*)malloc(sizeof(Imagem));
    if (img_ptr == NULL) 
        return NULL;
    (*img_ptr).largura = largura;
    (*img_ptr).altura = altura;

    (*img_ptr).data = (int**)malloc(altura * sizeof(int*));// aloca o array de ponteiros (as linhas)
    if ((*img_ptr).data == NULL) {
        free(img_ptr);
        return NULL;
    }
    for (int i = 0; i < altura; i++) { //aloca a memória para cada linha (as colunas)
        (*img_ptr).data[i] = (int*)malloc(largura * sizeof(int));
        if ((*img_ptr).data[i] == NULL) {

            for (int j = 0; j < i; j++) free((*img_ptr).data[j]);
            free((*img_ptr).data);
            free(img_ptr);             // caso falhar, libera tudo que foi alocado até agora
            return NULL;
        }
    }
    return img_ptr;

void liberaImagem(Imagem* img_ptr) {
    if (img_ptr != NULL) {
        if ((*img_ptr).data != NULL) {
            for (int i = 0; i < (*img_ptr).altura; i++) {
                free((*img_ptr).data[i]);
            }
            free((*img_ptr).data);
        }
        free(img_ptr);
    }
}

//--------------------------------------------


void abrirArquivo(int largura, int altura) { //abre o arquivo e fica disponivel para ler
    FILE *file;
    file = fopen("imagem.pbm", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        fclose(file);
        return;
    }
    char linha [100];
    while (fgets(linha, sizeof(linha), file) != NULL) { // Ignora comentários
        if (linha[0] == '#') {
            continue;
        }

        while(!feof(file)) {
            if (fgets(linha, sizeof(linha), file) != NULL) {
            printf("%s", linha);
            }
            if (sscanf(linha, "%d %d", &largura, &altura) == 2) {
                break;
                }
                printf("Erro ao ler dimensões da imagem.\n");
                fclose(file);
                return;
                //ou
            if (largura == 0 || altura == 0) {
                printf("Erro: Dimensões inválidas.\n");
                fclose(file);
                return;
            }
        }

        Image *img = criar(largura, altura); // cria uma estrutura
        if (img == NULL) {
            fclose(file);
            return;
        }
        for (int i = 0; i < altura; i++) { //preenche os pixels
            for (int j = 0; j < largura; j++) {
                if (fscanf(file, "%d", &img->data[i][j]) != 1) {
                    printf("Erro ao ler dados dos pixels em linha %d, coluna %d.\n", i, j);
                    free_image(img);
                    fclose(file);
                    return;
                }
            }
        }
    }
}

//--------------------------------------------

void separaImagem(int largura, int altura) { // vai separar a imagem em quadrantes
                    //lembrando, se o n ou m forem numeros impares, é para arredondar para cima (ao dividir no meio)

}

//--------------------------------------------

char codificaImagem() { //vai traduzir os quadrantes (P = Preto, B = Branco, X = começo do bloco)
                        //lembrando, se o quadrante inteiro for da msm cor, só coloca um "P" ou "B"
}

//--------------------------------------------

int main() {
    verificaImagem();

        
    fclose(file);
    return 0;
}