#include <stdio.h>
#include <stdlib.h>
#define LINHAS (3)
#define COLUNAS (3)

void matrizVazia(int m[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            m[i][j] = 0;
        }
    }
}

void jogoVelha(int m[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (m[i][j] == "") {
                if (m[i][j] == "X") {
                    printf("X");
                }
                else {
                    printf("O");
                }
            }
        }
    }
}

int main() {
    int m[LINHAS][COLUNAS];
    printf("Digite onde quer jogar (linha e coluna), jogador 1 (X): ");
    scanf("%d %d", &i, &j);
    printf("")
    printf("%d", m[LINHAS][COLUNAS]);
    printf("Digite onde quer jogar (linha e coluna), jogador 2 (O): ");
    scanf("%d %d", &i, &j);
    printf("%d", m[LINHAS][COLUNAS]);
    jogo = matrizVelha(); 

}