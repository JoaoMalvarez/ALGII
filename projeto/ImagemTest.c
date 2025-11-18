#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definições de cores e constantes
#define PRETO 1
#define BRANCO 0

//----------------------------------------------------------------------
// ESTRUTURA DE DADOS
//----------------------------------------------------------------------

typedef struct {
    int altura;
    int largura;
    // int **data: Ponteiro para ponteiro para a matriz de pixels alocada dinamicamente
    int **data;
} Image;

//----------------------------------------------------------------------
// MÓDULO DE GERENCIAMENTO DE MEMÓRIA (Pessoa 1)
//----------------------------------------------------------------------

/**
 * Cria e aloca a memória para uma nova estrutura Image com as dimensões especificadas.
 */
Image* criarImagem(int largura, int altura) {
    // 1. Aloca a estrutura principal
    Image *img_ptr = (Image*)malloc(sizeof(Image));
    if (img_ptr == NULL) return NULL;
    
    // Configura dimensões (usando (*ptr).member)
    (*img_ptr).largura = largura;
    (*img_ptr).altura = altura;

    // Se a dimensão for 0, não aloca dados (caso de subimagem vazia)
    if (largura == 0 || altura == 0) {
        (*img_ptr).data = NULL;
        return img_ptr;
    }

    // 2. Aloca o array de ponteiros (as linhas)
    (*img_ptr).data = (int**)malloc(altura * sizeof(int*));
    if ((*img_ptr).data == NULL) {
        free(img_ptr);
        return NULL;
    }

    // 3. Aloca a memória para cada linha (as colunas)
    for (int i = 0; i < altura; i++) {
        (*img_ptr).data[i] = (int*)malloc(largura * sizeof(int));
        if ((*img_ptr).data[i] == NULL) {
            // Limpa alocações parciais em caso de falha
            for (int j = 0; j < i; j++) free((*img_ptr).data[j]);
            free((*img_ptr).data);
            free(img_ptr);
            return NULL;
        }
    }
    return img_ptr;
}

/**
 * Libera toda a memória alocada para a imagem, incluindo a matriz de pixels.
 */
void liberaImagem(Image* img_ptr) {
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

//----------------------------------------------------------------------
// MÓDULO DE UTILIDADES E ENTRADA/SAÍDA (Pessoa 2)
//----------------------------------------------------------------------

/**
 * Concatena duas strings, realocando s1 para caber s2.
 * Esta função é crucial para construir o código recursivamente em C.
 */
char* concat_string(char *s1, const char *s2) {
    size_t len1 = (s1 != NULL) ? strlen(s1) : 0;
    size_t len2 = strlen(s2);
    
    // Aloca espaço para ambas as strings + '\0'
    char *new_s = (char*)realloc(s1, len1 + len2 + 1); 
    if (new_s == NULL) return NULL;
    
    if (s1 == NULL) {
        strcpy(new_s, s2); // Se s1 for nulo, apenas copia s2
    } else {
        strcat(new_s, s2); // Concatena s2 ao final de s1
    }
    return new_s;
}

/**
 * Lê o arquivo PBM (Portable Bitmap P1) e carrega os dados para a estrutura Image.
 */
Image* read_pbm_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", filename);
        return NULL;
    }

    char linha[1024];
    int largura = 0, altura = 0;

    // 1. LER P1 (Magic Number)
    if (fgets(linha, sizeof(linha), file) == NULL || strncmp(linha, "P1", 2) != 0) {
        printf("Erro: Arquivo não é um PBM P1 válido (falta P1).\n");
        fclose(file);
        return NULL;
    }

    // 2. IGNORAR COMENTÁRIOS E LER DIMENSÕES
    while (fgets(linha, sizeof(linha), file) != NULL) {
        if (linha[0] == '#') {
            continue; // Ignora comentário
        }
        // Tenta ler largura e altura na primeira linha não-comentário
        if (sscanf(linha, "%d %d", &altura, &largura) == 2) {
            break; // Dimensões lidas
        }
    }
    
    if (altura <= 0 || largura <= 0) {
        printf("Erro: Dimensões não encontradas ou inválidas.\n");
        fclose(file);
        return NULL;
    }

    // 3. CRIA A ESTRUTURA
    Image *img = criarImagem(largura, altura);
    if (img == NULL) {
        fclose(file);
        return NULL;
    }

    // 4. LER E PREENCHER OS PIXELS (0s e 1s)
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            if (fscanf(file, "%d", &((*img).data[i][j])) != 1) {
                printf("Erro ao ler dados dos pixels em linha %d, coluna %d.\n", i, j);
                liberaImagem(img);
                fclose(file);
                return NULL;
            }
        }
    }

    fclose(file);
    return img;
}

//----------------------------------------------------------------------
// MÓDULO DE LÓGICA RECURSIVA (Pessoa 3)
//----------------------------------------------------------------------

/**
 * Verifica se a subimagem é uniforme (Regra 1).
 * Retorna PRETO ou BRANCO se uniforme, ou -1 se heterogênea.
 */
int is_uniform(Image* img) {
    if ((*img).largura <= 0 || (*img).altura <= 0) return -1;

    int primeira_cor = (*img).data[0][0];

    for (int i = 0; i < (*img).altura; i++) {
        for (int j = 0; j < (*img).largura; j++) {
            if ((*img).data[i][j] != primeira_cor) {
                return -1; // Heterogênea
            }
        }
    }
    return primeira_cor; // Homogênea
}

/**
 * Divide a imagem em 4 subimagens (Q1, Q2, Q3, Q4) aplicando a regra de
 * arredondamento para cima no ponto médio.
 * Retorna um array de 4 ponteiros para as novas imagens.
 */
Image** divide_image(Image* img) {
    Image **subimages = (Image**)malloc(4 * sizeof(Image*));
    if (subimages == NULL) return NULL;

    // Calcula dimensões (usando (X + 1) / 2 para arredondar para cima)
    int H1 = ((*img).altura + 1) / 2; // Altura Superior
    int H2 = (*img).altura - H1;      // Altura Inferior
    
    int W1 = ((*img).largura + 1) / 2; // Largura Esquerda
    int W2 = (*img).largura - W1;      // Largura Direita

    // Copia os pixels para as 4 subimagens:
    // Q1 (Superior Esquerdo): H1 x W1
    subimages[0] = criarImagem(W1, H1);
    for (int i = 0; i < H1; i++) {
        for (int j = 0; j < W1; j++) {
            (*subimages[0]).data[i][j] = (*img).data[i][j];
        }
    }

    // Q2 (Superior Direito): H1 x W2
    subimages[1] = criarImagem(W2, H1);
    for (int i = 0; i < H1; i++) {
        for (int j = 0; j < W2; j++) {
            (*subimages[1]).data[i][j] = (*img).data[i][j + W1]; // Offset de coluna
        }
    }

    // Q3 (Inferior Esquerdo): H2 x W1
    subimages[2] = criarImagem(W1, H2);
    for (int i = 0; i < H2; i++) {
        for (int j = 0; j < W1; j++) {
            (*subimages[2]).data[i][j] = (*img).data[i + H1][j]; // Offset de linha
        }
    }

    // Q4 (Inferior Direito): H2 x W2
    subimages[3] = criarImagem(W2, H2);
    for (int i = 0; i < H2; i++) {
        for (int j = 0; j < W2; j++) {
            (*subimages[3]).data[i][j] = (*img).data[i + H1][j + W1]; // Offset de linha e coluna
        }
    }

    return subimages;
}

/**
 * Função recursiva principal que codifica a imagem (ou subimagem) usando as regras P, B, X.
 */
char* encode_image(Image* img) {
    if ((*img).largura == 0 || (*img).altura == 0) {
        return strdup(""); // Retorna string vazia para subimagem nula
    }

    // 1. CASO BASE (Regra 1): Imagem Uniforme
    int uniform_color = is_uniform(img);
    if (uniform_color == BRANCO) {
        return strdup("B"); 
    } else if (uniform_color == PRETO) {
        return strdup("P"); 
    }
    
    // 2. PASSO RECURSIVO (Regra 2): Imagem Não-Uniforme
    // O código começa com 'X'
    char *code = strdup("X"); // strdup aloca memória para a string "X"

    // Divide a imagem em 4 subimagens
    Image **subimages = divide_image(img);
    if (subimages == NULL) {
        free(code);
        return NULL;
    }
    
    // Concatena os códigos recursivamente (Q1, Q2, Q3, Q4)
    for (int i = 0; i < 4; i++) {
        char *subcode = encode_image(subimages[i]); // Chamada recursiva
        
        char *temp = code;
        code = concat_string(code, subcode); // Concatena e realoca 'code'
        
        free(subcode); // Libera o código retornado pela sub-chamada
        liberaImagem(subimages[i]); // Libera a memória da subimagem
    }
    
    free(subimages); // Libera o array de ponteiros
    
    return code;
}

//----------------------------------------------------------------------
// FUNÇÃO PRINCIPAL
//----------------------------------------------------------------------

int main(int argc, char *argv[]) {
    // 1. TRATAMENTO DA INTERFACE DE LINHA DE COMANDO (CLI)
    if (argc != 2) {
        printf("Uso: %s <nome_do_arquivo.pbm>\n", argv[0]);
        printf("Exemplo: %s imagem.pbm\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    // 2. LEITURA DA IMAGEM
    Image *img = read_pbm_file(filename); 

    if (img == NULL) {
        printf("Não foi possível carregar a imagem.\n");
        return 1;
    }

    // 3. CODIFICAÇÃO
    printf("Codificando imagem de %dx%d...\n", (*img).largura, (*img).altura);
    char *codigo_final = encode_image(img);

    // 4. SAÍDA
    if (codigo_final != NULL) {
        printf("Código Final: %s\n", codigo_final);
        free(codigo_final); // Libera a memória do código gerado
    } else {
        printf("Erro durante a codificação.\n");
    }

    // 5. LIMPEZA DA MEMÓRIA
    liberaImagem(img); 

    return 0;
}