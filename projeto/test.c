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

void ajuda(const char *nome_programa) {
    printf("Uso: %s [-? | -m | -f ARQ]\n\n", nome_programa);
    printf("Argumentos:\n");
    printf("-?, --help   : apresenta essa orientação na tela.\n");
    printf("-m, --manual : ativa o modo de entrada manual, em que o usuário fornece\n");
    printf("               todos os dados da imagem informando-os através do teclado.\n");
    printf("-f, --file   : considera a imagem representada no arquivo PBM (Portable bitmap).\n");
}

//----------------

Imagem* ler_imagem_manual() {
    int a, l;
    printf("\n--- MODO DE ENTRADA MANUAL ---\n");
    printf("Informe a altura (linhas) da imagem: ");
    if (scanf("%d", &a) != 1 || a <= 0) {
        printf("Erro: Altura inválida.\n");
        return NULL;
    }
    
    printf("Informe a largura (colunas) da imagem: ");
    if (scanf("%d", &l) != 1 || l <= 0) {
        printf("Erro: Largura inválida.\n");
        return NULL;
    }

    // 2. CRIA A ESTRUTURA
    Imagem *img = criarImagem(l, a);
    if (img == NULL) {
        printf("Erro: Falha ao alocar memória para a imagem.\n");
        return NULL;
    }

    printf("\nInforme os pixels (0 para Branco, 1 para Preto) em ordem: \n");
    printf("Total de %d pixels a serem informados (linha por linha):\n", a * l);
    
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < l; j++) {
            int pixel_lido;
            printf("Pixel [%d, %d]: ", i + 1, j + 1); 
            
            if (scanf("%d", &pixel_lido) != 1) {
                printf("Erro: Entrada não é um número.\n");
                liberaImagem(img);
                return NULL;
            }
            
            if (pixel_lido != PRETO && pixel_lido != BRANCO) {
                printf("Erro: Pixel deve ser 0 (Branco) ou 1 (Preto).\n");
                liberaImagem(img);
                return NULL;
            }
            
            int indice = i * (*img).l + j;
            (*img).dados[indice] = pixel_lido;
        }
    }

    printf("\nLeitura manual concluída.\n");
    return img;
}

//----------------

int main(int argc, char *argv[]) {
    const char *nome_programa = argv[0];
    Imagem *img = NULL;
    int opcao; 
    if (argc < 2) {
        printf("Erro: Argumentos insuficientes.\n");
        ajuda(nome_programa);
        return 1;
    }

    if (strcmp(argv[1], "-?") == 0 || strcmp(argv[1], "--help") == 0) {
        ajuda(nome_programa);
        return 0;

    } else if (strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "--file") == 0) {
        if (argc != 3) {
            printf("Erro: A opção -f requer o nome do arquivo PBM.\n");
            ajuda(nome_programa);
               return 1;
        }
    
        const char *nome_arquivo = argv[2];
        img = ler_arquivo_pbm(nome_arquivo);
        if (img == NULL) {
            printf("Não foi possível carregar a imagem do arquivo.\n");
            return 1;
        }

    } else if (strcmp(argv[1], "-m") == 0 || strcmp(argv[1], "--manual") == 0) {
        img = ler_imagem_manual();
        if (img == NULL) {
            printf("Falha na leitura manual da imagem. Saindo.\n");
            return 1;
        }
        
    } else {
        printf("Erro: Opção inválida: %s\n", argv[1]);
        ajuda(nome_programa);
        return 1;
    }
    
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