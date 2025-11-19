/*Grupo:
    - Heloisa Martelle - 10738274
    - João Pedro Mazzante Alvarez - 10723837
    - Mateus Machado - 10741262

    // Link do vídeo: COLOQUEM AQUI
*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h> 

// Constantes do projeto
#define PRETO 1
#define BRANCO 0
#define ALTURA_MAX 768
#define LARGURA_MAX 1024
#define TAMANHO_MAX 3500000 

// Estrutura que armazena uma imagem PBM em memória
typedef struct {
    int a; // altura
    int l; // largura
    int dados[ALTURA_MAX * LARGURA_MAX]; // Armazena os pixels da imagem
} Imagem; 

// Variáveis globais para evitar malloc
Imagem imagemEstaticaGlobal;
char CodigoFinalGlobal[TAMANHO_MAX];
int indiceCodificacaoGlobal = 0;

// Função auxiliar para ignorar comentários e espaços no arquivo PBM
void pularComentariosEspacos (FILE *file);

// ----------------------------------------------------

Imagem* criarImagem(int l, int a) {
    // Cria imagem usando buffer estático global
    if (l <= 0 || a <= 0 || l > LARGURA_MAX || a > ALTURA_MAX) {
        printf("Erro: Dimensões inválidas ou excedem o limite estático (%dx%d).\n", LARGURA_MAX, ALTURA_MAX);
        return NULL;
    }

    imagemEstaticaGlobal.l = l;
    imagemEstaticaGlobal.a = a;
    
    return &imagemEstaticaGlobal;
}

// ----------------------------------------------------

// A função apenas mantém compatibilidade com o enunciado, pois usamos buffer global
char* junta_strings(char *s1, const char *s2) {
    return s1; 
}

// ----------------------------------------------------

// Verifica se uma subimagem é uniforme (todos pixels iguais)
int uniforme(Imagem* original_img, int inicio_r, int inicio_c, int a, int l) {
    if (l <= 0 || a <= 0) {
        return -1;
    }
    
    int primeira_cor = original_img->dados[inicio_r * original_img->l + inicio_c];

    // Percorre toda a subimagem
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < l; j++) {
            int indice_atual = (inicio_r + i) * original_img->l + (inicio_c + j);
            if (original_img->dados[indice_atual] != primeira_cor) {
                return -1; // Não é uniforme
            }
        }
    }
    return primeira_cor; // Retorna BRANCO ou PRETO
}

// ----------------------------------------------------

// Função recursiva que implementa o algoritmo XBP descrito no PDF
char* codifica(Imagem* original_img, int inicio_r, int inicio_c, int a, int l) {
    if (l <= 0 || a <= 0) {
        return NULL;
    }
    
    int cor_uniforme = uniforme(original_img, inicio_r, inicio_c, a, l);
    char char_codigo = '\0';
    
    // Caso uniforme, gera 'B' ou 'P'
    if (cor_uniforme == BRANCO) {
        char_codigo = 'B'; 
    } else if (cor_uniforme == PRETO) {
        char_codigo = 'P';
    } else {
        // Caso misto, gera 'X' e divide em quadrantes
        char_codigo = 'X';
    }
    
    // Escreve o caractere no buffer global
    if (indiceCodificacaoGlobal < TAMANHO_MAX - 2) {
        CodigoFinalGlobal[indiceCodificacaoGlobal++] = char_codigo;
    } else {
        printf("\nErro.\n");
        return NULL;
    }
    
    // Caso imagem seja uniforme, encerra recursão
    if (cor_uniforme == BRANCO || cor_uniforme == PRETO) {
        return CodigoFinalGlobal; 
    }

    // Calcula cortes (divide imagem ao meio conforme PDF)
    int a1 = (a + 1) / 2; // parte de cima maior se altura ímpar
    int l1 = (l + 1) / 2; // parte esquerda maior se largura ímpar
    int a2 = a - a1;
    int l2 = l - l1;

    // Chama recursivamente para os 4 quadrantes
    codifica(original_img, inicio_r, inicio_c, a1, l1);           // 1º quadrante
    codifica(original_img, inicio_r, inicio_c + l1, a1, l2);      // 2º quadrante
    codifica(original_img, inicio_r + a1, inicio_c, a2, l1);      // 3º quadrante
    codifica(original_img, inicio_r + a1, inicio_c + l1, a2, l2); // 4º quadrante

    return CodigoFinalGlobal;
}

// ----------------------------------------------------

// Wrapper da codificação — reinicia o índice global e inicia o processo
char* codificar_imagem(Imagem* img) {
    if (img == NULL) {
        return NULL;
    }
    
    indiceCodificacaoGlobal = 0;
    
    char *resultado = codifica(img, 0, 0, img->a, img->l);
    
    CodigoFinalGlobal[indiceCodificacaoGlobal] = '\0'; // finaliza string
    
    return resultado;
}

// ----------------------------------------------------

// Ignora comentários do PBM (#...) e espaços
void pularComentariosEspacos (FILE *file) {
    int c;

    while (1) {
        c = fgetc (file);

        if (c == EOF) return; 
        
        if (isspace(c)) { 
            continue; 
        }
        if (c == '#') {
            // ignora até o fim da linha
            while ((c = fgetc(file)) != '\n' && c != EOF) {} 
            continue;
        }
        ungetc (c, file);
        break;
    }
}

// ----------------------------------------------------

// Leitura de arquivo PBM (P1) conforme especificação do PDF
Imagem* ler_arquivo_pbm(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo); 
        return NULL; 
    }

    char linha[1024];
    int a = 0, l = 0;

    // Verifica o "magic number" P1
    if (fgets(linha, sizeof(linha), arquivo) == NULL || strncmp(linha, "P1", 2) != 0) {
        printf("Erro: Arquivo não é um PBM P1 válido.\n");
        fclose(arquivo); 
        return NULL;
    }
    
    pularComentariosEspacos(arquivo);
    
    // Lê largura e altura
    if (fscanf(arquivo, "%d %d", &a, &l) != 2) {
        printf("Erro: Dimensões não encontradas ou inválidas.\n");
        fclose(arquivo); 
        return NULL;
    }

    // Cria imagem no buffer global
    Imagem *img = criarImagem(l, a);
    if (img == NULL) { 
        fclose(arquivo); 
        return NULL; 
    }

    // Lê os dados dos pixels
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < l; j++) {
            pularComentariosEspacos(arquivo);
            int indice = i * img->l + j;
            if (fscanf(arquivo, "%d", &(img->dados[indice])) != 1) { 
                printf("Erro ao ler pixel em (%d, %d).\n", i, j); 
                fclose(arquivo); 
                return NULL;
            }
        }
    }

    fclose(arquivo);
    return img;
}

// ----------------------------------------------------

// Modo manual — usuário digita valores pelo teclado
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
    
    // Lê cada pixel informado manualmente
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < l; j++) {
            int pixel_lido;
            printf("Pixel [%d, %d]: ", i + 1, j + 1);
            if (scanf("%d", &pixel_lido) != 1) {
                printf("Erro: Entrada não é um número. Saindo.\n");
                return NULL;
            }
            if (pixel_lido != PRETO && pixel_lido != BRANCO) {
                printf("Erro: Pixel deve ser 0 (Branco) ou 1 (Preto). Saindo.\n");
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

// Exibe tela de ajuda como no PDF
void ajuda(const char *nome_programa) {
    printf("Uso: %s [-? | -m | -f ARQ]\n\n", nome_programa);
    printf("Argumentos:\n");
    printf("-?, --help  : apresenta essa orientação na tela.\n");
    printf("-m, --manual : ativa o modo de entrada manual.\n");
    printf("-f, --file  : considera o arquivo PBM fornecido.\n");
}

// ----------------------------------------------------

int main(int argc, char *argv[]) {
    int c;
    const char *nome_programa = argv[0];
    Imagem *img = NULL;
    int opcao = -1; 
    
    // Caso nenhum argumento seja informado
    if (argc < 2) {
        printf("Erro: Argumentos insuficientes.\n");
        ajuda(nome_programa);
        return 1;
    }
    
    // Verifica parâmetros da CLI (-?, -m, -f)
    if (strcmp(argv[1], "-?") == 0 || strcmp(argv[1], "--help") == 0) {
        ajuda(nome_programa);
        return 0;

    } else if (strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "--file") == 0) {

        // Lê arquivo PBM
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

        // Modo manual
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
    
    // Menu principal
    printf("\n--- Menu ---\n");
    printf("1. Codificar a imagem (XBP)\n");
    printf("2. Mostrar a imagem\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
        
    if (scanf("%d", &opcao) != 1) {
        printf("Opção inválida. Tente novamente.\n");
        opcao = -1; 
    }

    switch (opcao) {
        case 1:
            // Chama o algoritmo completo de codificação
            printf("\nCodificando imagem de %dx%d...\n\n", img->a, img->l);
            char *codigo_final = codificar_imagem(img); 

            if (codigo_final != NULL) {
                printf("|Código Final: %s|\n", codigo_final);
            } else {
                printf("Perdão! Houve um erro durante a codificação. :(\n");
            }
            break;

        case 2:
            // Exibe imagem com P/B
            printf("\n--- Visualização da Imagem (%dx%d) ---\n", img->a, img->l);
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
    
    return 0;
}