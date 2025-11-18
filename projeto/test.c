#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRETO 1
#define BRANCO 0

//----------------

// Struct
typedef struct {
    int a; // altura
    int l; // largura
    int *dados; 
} Imagem;

//----------------

Imagem* criarImagem(int l, int a) {
    if (l <= 0 || a <= 0) {
        return NULL;
    }

    Imagem *img = (Imagem*)malloc(sizeof(Imagem));
    if (img == NULL) {
        return NULL;
    }
    
    (*img).l = l;
    (*img).a = a;

    (*img).dados = (int*)malloc(a * l * sizeof(int));
    if ((*img).dados == NULL) { 
        free(img); 
        return NULL; 
    }
    
    return img;
}

//----------------

void liberaImagem(Imagem* img) {
    if (img != NULL) {
        free((*img).dados); 
        free(img);
    }
}

//----------------

char* junta_strings(char *s1, const char *s2) {
    size_t len1 = (s1 != NULL) ? strlen(s1) : 0;
    size_t len2 = strlen(s2);
    
    char *nova_s = (char*)realloc(s1, len1 + len2 + 1);
    if (nova_s == NULL) {
        return NULL;
    }

    if (s1 == NULL) {
        strcpy(nova_s, s2);
    } else {
        strcat(nova_s, s2);
    }
    
    return nova_s;
}

//----------------

Imagem* ler_arquivo_pbm(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo); 
        return NULL; // abre arquivo
    }

    char linha[1024];
    int a = 0, l = 0;

    if (fgets(linha, sizeof(linha), arquivo) == NULL || strncmp(linha, "P1", 2) != 0) {
        printf("Erro: Arquivo não é um PBM P1 válido.\n"); //P1
        fclose(arquivo); 
        return NULL;
    }
    
    while (fgets(linha, sizeof(linha), arquivo) != NULL) { //comentários
        if (linha[0] == '#') {
            continue; 
        }
        if (sscanf(linha, "%d %d", &a, &l) == 2) {
            break; //dimensões 
        }
    }
    
    if (l <= 0 || a <= 0) {
        printf("Erro: Dimensões não encontradas ou inválidas.\n");
        fclose(arquivo); 
        return NULL;
    }

//----------------
    Imagem *img = criarImagem(l, a);
    if (img == NULL) { 
        fclose(arquivo); 
        return NULL; 
    }

    for (int i = 0; i < a; i++) { //le
        for (int j = 0; j < l; j++) {
            int indice = i * (*img).l + j;
            if (fscanf(arquivo, "%d", &((*img).dados[indice])) != 1) { //se tiver erro na imagem
                printf("Erro ao ler pixel em (%d, %d) - [Altura x Largura].\n", i, j); //informa onde
                liberaImagem(img); 
                fclose(arquivo); 
                return NULL;
            }
        }
    }

    fclose(arquivo);
    return img;
}

//----------------

int uniforme(Imagem* original_img, int inicio_r, int inicio_c, int a, int l) {
    if (l <= 0 || a <= 0) {
        return -1;
    }
    int indice_ref = inicio_r * (*original_img).l + inicio_c;
    int primeira_cor = (*original_img).dados[indice_ref];

    for (int i = 0; i < a; i++) {
        for (int j = 0; j < l; j++) {
            int indice_atual = (inicio_r + i) * (*original_img).l + (inicio_c + j);
            if ((*original_img).dados[indice_atual] != primeira_cor) {
                return -1;
            }
        }
    }
    return primeira_cor;
}

//----------------

char* codifica(Imagem* original_img, int inicio_r, int inicio_c, int a, int l) {
    if (l <= 0 || a <= 0) {
        return strdup(""); 
    }
    
    // BRANCO = B e PRETO = P
    int cor_uniforme = uniforme(original_img, inicio_r, inicio_c, a, l);
    if (cor_uniforme == BRANCO) {
        return strdup("B"); 
    }
    if (cor_uniforme == PRETO) {
        return strdup("P");
    }
    
    // Começa com X, e coloca ' ' na frente para mostrar as repartições com clareza
    char *codigo = strdup(" X");
    
    //Quadrantes
    int a1 = (a + 1) / 2; 
    int l1 = (l + 1) / 2; 
    int a2 = a - a1;      
    int l2 = l - l1;      

    codigo = junta_strings(codigo, codifica(original_img, inicio_r, inicio_c, a1, l1));
    codigo = junta_strings(codigo, codifica(original_img, inicio_r, inicio_c + l1, a1, l2));
    codigo = junta_strings(codigo, codifica(original_img, inicio_r + a1, inicio_c, a2, l1));
    codigo = junta_strings(codigo, codifica(original_img, inicio_r + a1, inicio_c + l1, a2, l2));

    return codigo;
}

//----------------

char* codificar_imagem(Imagem* img) {
    if (img == NULL) {
        return NULL;
    }
    return codifica(img, 0, 0, (*img).a, (*img).l);
}

//----------------

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <nome_do_arquivo.pbm>\n", argv[0]);
        return 1;
    }

    Imagem *img = ler_arquivo_pbm(argv[1]); 
    if (img == NULL) {
        return 1;
    }
    int opcao;

    printf("--- Menu ---\n");
    printf("1. Codificar a imagem (XBP)\n");
    printf("2. Mostrar a imagem\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Codificando imagem de %dx%d...\n", (*img).l, (*img).a);
            char *codigo_final = codificar_imagem(img);

            if (codigo_final != NULL) {
                printf("Código Final: %s\n", codigo_final);
                free(codigo_final);
            } else {
                printf("Perdão! Houve um erro durante a codificação. :(\n");
            }

            liberaImagem(img);
            break;

        case 2:
            if (img == NULL) {
                printf("Erro: Imagem nula.\n");
                return 1;
            }

            printf("\n--- Visualização da Imagem (%dx%d) ---\n", (*img).l, (*img).a);
            printf("'#' = Preto; '.' = Branco \n\n");

            for (int i = 0; i < (*img).a; i++) {
                for (int j = 0; j < (*img).l; j++) {
                    int indice = i * (*img).l + j;
                    int pixel = (*img).dados[indice];

                    if (pixel == PRETO) {
                        printf("#"); 
                    } else {
                        printf("."); 
                    }
                }
                printf("\n"); 
            }
            break;

        case 0:
            printf("Saindo do programa.\n");
            break;

        default:
            printf("Opcao invalida. Tente novamente.\n");
    }
    return 0;
}