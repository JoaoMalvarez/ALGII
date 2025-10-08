#include <stdio.h>
#include <string.h>
#define TAM 5

typedef struct {
    char titulo[100];
    int capitulos;
    int paginas;
} Livro;

/*struct Capitulo {
    char nomeCap[100];
    int numeroCap;
    int paginasCap;
};                        Não criei no main pq é só como exemplo de outra forma que dá para fazer com
                          typedef struct ao inves de struct[nome]
 */

void pag(Livro v[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j].paginas < v[min_idx].paginas) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            Livro temp = v[min_idx];
            v[min_idx] = v[i];
            v[i] = temp;
        }
    }
}

int main () {
    Livro livros[TAM] = { //Quando não tem typedef se usa struct antes!!
        {"Pequeno Principe", 27, 136},
        {"IT, a coisa", 0, 1600},
        {"Harry Potter", 199, 3363},
        {"Crepusculo", 24, 416},
        {"Os dois morrem no final", 0, 416},
    };
    //nessa área se coloca funções usadas
    pag (livros, TAM);
    printf("Livros Mais fáceis de leitura\n");
    printf("=============================\n");
    for (int i = 0; i < 5; i++) {
        printf("\n\nEm %dº lugar:\n", i + 1);
        printf("Livro: %s\n", livros[i].titulo);
        printf("Quantidade de Páginas: %d\n", livros[i].paginas);
        printf("Quantidade de Capitulos: %d\n", livros[i].capitulos);
    }
    return 0;
}