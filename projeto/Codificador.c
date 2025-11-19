#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h> 

#define PRETO 1
#define BRANCO 0
#define ALTURA_MAX 768
#define LARGURA_MAX 1024
#define TAMANHO_MAX 3500000 

typedef struct {
    int a; // altura
    int l; // largura
    int dados[ALTURA_MAX * LARGURA_MAX]; 
} Imagem; 

Imagem imagemEstaticaGlobal;
char CodigoFinalGlobal[TAMANHO_MAX];
int indiceCodificacaoGlobal = 0;

void pularComentariosEspacos (FILE *file);

// ----------------------------------------------------

Imagem* criarImagem(int l, int a) {
    if (l <= 0 || a <= 0 || l > LARGURA_MAX || a > ALTURA_MAX) {
        printf("Erro: Dimensões inválidas ou excedem o limite estático (%dx%d).\n", LARGURA_MAX, ALTURA_MAX);
        return NULL;
    }

    imagemEstaticaGlobal.l = l;
    imagemEstaticaGlobal.a = a;
    
    return &imagemEstaticaGlobal;
}


// ----------------------------------------------------

char* junta_strings(char *s1, const char *s2) {
    // A codificação é escrita diretamente no buffer global,
    // então esta função apenas retorna s1 para manter o fluxo de ponteiros.
    return s1; 
}

// ----------------------------------------------------

int uniforme(Imagem* original_img, int inicio_r, int inicio_c, int a, int l) {
    if (l <= 0 || a <= 0) {
        return -1;
    }
    
    int primeira_cor = original_img->dados[inicio_r * original_img->l + inicio_c];

    for (int i = 0; i < a; i++) {
        for (int j = 0; j < l; j++) {
            int indice_atual = (inicio_r + i) * original_img->l + (inicio_c + j);
            if (original_img->dados[indice_atual] != primeira_cor) {
                return -1;
            }
        }
    }
    return primeira_cor;
}

// ----------------------------------------------------

char* codifica(Imagem* original_img, int inicio_r, int inicio_c, int a, int l) {
    if (l <= 0 || a <= 0) {
        return NULL;
    }
    
    int cor_uniforme = uniforme(original_img, inicio_r, inicio_c, a, l);
    char char_codigo = '\0';
    
    if (cor_uniforme == BRANCO) {
        char_codigo = 'B'; 
    } else if (cor_uniforme == PRETO) {
        char_codigo = 'P';
    } else {
        char_codigo = 'X';
    }
    
    if (indiceCodificacaoGlobal < TAMANHO_MAX - 2) {
        CodigoFinalGlobal[indiceCodificacaoGlobal++] = char_codigo;
        
        if (char_codigo == 'X') {
            CodigoFinalGlobal[indiceCodificacaoGlobal++] = ' ';
        }
        
    } else {
        printf("\nErro.\n");
        return NULL;
    }
    
    if (cor_uniforme == BRANCO || cor_uniforme == PRETO) {
        return CodigoFinalGlobal; 
    }

    int a1 = (a + 1) / 2;
    int l1 = (l + 1) / 2;
    int a2 = a - a1;
    int l2 = l - l1;

    codifica(original_img, inicio_r, inicio_c, a1, l1);
    codifica(original_img, inicio_r, inicio_c + l1, a1, l2);
    codifica(original_img, inicio_r + a1, inicio_c, a2, l1);
    codifica(original_img, inicio_r + a1, inicio_c + l1, a2, l2);

    return CodigoFinalGlobal;
}

// ----------------------------------------------------

char* codificar_imagem(Imagem* img) {
    if (img == NULL) {
        return NULL;
    }
    
    indiceCodificacaoGlobal = 0;
    
    char *resultado = codifica(img, 0, 0, img->a, img->l);
    
    CodigoFinalGlobal[indiceCodificacaoGlobal] = '\0';
    
    return resultado;
}

// ----------------------------------------------------

void pularComentariosEspacos (FILE *file) {
    int c;

    while (1) {
        c = fgetc (file);

        if (c == EOF) return; 
        
        if (isspace(c)) { 
            continue; 
        }
        if (c == '#') {
            while ((c = fgetc(file)) != '\n' && c != EOF) {} 
            continue;
        }
        ungetc (c, file);
        break;
    }
}

// ----------------------------------------------------

Imagem* ler_arquivo_pbm(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo); 
        return NULL; 
    }

    char linha[1024];
    int a = 0, l = 0;

    if (fgets(linha, sizeof(linha), arquivo) == NULL || strncmp(linha, "P1", 2) != 0) {
        printf("Erro: Arquivo não é um PBM P1 válido.\n");
        fclose(arquivo); 
        return NULL;
    }
    
    pularComentariosEspacos(arquivo);
    
    if (fscanf(arquivo, "%d %d", &l, &a) != 2) {
        printf("Erro: Dimensões não encontradas ou inválidas.\n");
        fclose(arquivo); 
        return NULL;
    }

    Imagem *img = criarImagem(l, a);
    if (img == NULL) { 
        fclose(arquivo); 
        return NULL; 
    }

    for (int i = 0; i < a; i++) {
        for (int j = 0; j < l; j++) {
            pularComentariosEspacos(arquivo);
            int indice = i * img->l + j;
            if (fscanf(arquivo, "%d", &(img->dados[indice])) != 1) { 
                printf("Erro ao ler pixel em (%d, %d).\n", i, j); 
                liberaImagem(img); 
                fclose(arquivo); 
                return NULL;
            }
        }
    }

    fclose(arquivo);
    return img;
}

// ----------------------------------------------------

Imagem* ler_imagem_manual() {
    int a, l;
    printf("\n--- MODO DE ENTRADA MANUAL ---\n");
    printf("Informe a altura (linhas, máx %d): ", ALTURA_MAX);
    if (scanf("%d", &a) != 1 || a <= 0) {
        printf("Erro: Altura inválida.\n");
        return NULL;
    }
    
    printf("Informe a largura (colunas, máx %d): ", LARGURA_MAX);
    if (scanf("%d", &l) != 1 || l <= 0) {
        printf("Erro: Largura inválida.\n");
        return NULL;
    }

    Imagem *img = criarImagem(l, a);
    if (img == NULL) {
        printf("Erro: Falha ao alocar memória estática para a imagem (limite excedido).\n");
        return NULL;
    }

    printf("\nInforme os pixels (0 para Branco, 1 para Preto) em ordem: \n");
    
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < l; j++) {
            int pixel_lido;
            printf("Pixel [%d, %d]: ", i + 1, j + 1);
            if (scanf("%d", &pixel_lido) != 1) {
                printf("Erro: Entrada não é um número. Saindo.\n");
                liberaImagem(img);
                return NULL;
            }
            if (pixel_lido != PRETO && pixel_lido != BRANCO) {
                printf("Erro: Pixel deve ser 0 (Branco) ou 1 (Preto). Saindo.\n");
                liberaImagem(img);
                return NULL;
            }
            int indice = i * img->l + j;
            img->dados[indice] = pixel_lido;
        }
    }

    printf("\nLeitura manual concluída.\n");
    return img;
}

// ----------------------------------------------------

void ajuda(const char *nome_programa) {
    printf("Uso: %s [-? | -m | -f ARQ]\n\n", nome_programa);
    printf("Argumentos:\n");
    printf("-?, --help  : apresenta essa orientação na tela.\\n");
    printf("-m, --manual : ativa o modo de entrada manual, em que o usuário fornece\\n");
    printf("               todos os dados da imagem informando-os através do teclado.\\n");
    printf("-f, --file  : considera a imagem representada no arquivo PBM (Portable bitmap).\\n");
}

// ----------------------------------------------------

int main(int argc, char *argv[]) {
    const char *nome_programa = argv[0];
    Imagem *img = NULL;
    int opcao = -1; 
    
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
            printf("Não foi possível carregar a imagem do arquivo. Saindo.\n");
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
    
    do {
        printf("\n--- Menu ---\n");
        printf("1. Codificar a imagem (XBP)\n");
        printf("2. Mostrar a imagem\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        if (scanf("%d", &opcao) != 1) {
            printf("Opção inválida. Tente novamente.\n");
            opcao = -1; 
            continue;
        }

        switch (opcao) {
            case 1:
                printf("Codificando imagem de %dx%d...\n", img->l, img->a);
                char *codigo_final = codificar_imagem(img); 

                if (codigo_final != NULL) {
                    printf("Código Final: %s\n", codigo_final);
                } else {
                    printf("Perdão! Houve um erro durante a codificação. :(\n");
                }
                break;

            case 2:
                printf("\n--- Visualização da Imagem (%dx%d) ---\n", img->l, img->a);
                printf("'P' = Preto; 'B' = Branco \n\n");

                for (int i = 0; i < img->a; i++) {
                    for (int j = 0; j < img->l; j++) {
                        int indice = i * img->l + j;
                        printf(img->dados[indice] == PRETO ? "P" : "B"); 
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
    } while (opcao != 0);

    liberaImagem(img); 
    
    return 0;
}