#include <stdio.h>

int busca_binaria_recursiva(int vetor[], int valor, int i, int f) {
    if (i > f)
        return -1;
    int meio = (1 + f) / 2;
    if (vetor[meio] == valor)
        return meio;
    if (vetor[meio] > valor)
        return busca_binaria_recursiva(vetor, valor, i, meio - 1);
    else 
        return busca_binaria_recursiva(vetor, valor, meio + 1, f);
}

int busca_binaria(int vetor[], int n, int valor) {
    return busca_binaria_recursiva(vetor, valor, 0, n - 1);
}

int main() {
    int v[6] = {10, 20, 30, 40, 50, 60};
    int p = busca_binaria(v, 6, 20);
    printf("--A sua busca deu:--\n");
    printf("%d\n", p);
    return 0;
}

/*    para busca binária SEM SER RECURSIVA 
int inicio = 0;
    int fim = n -1;
    int meio;
    while (inicio <= fim) / 2 {
        if (vetor[meio] == valor) {
            return meio;
        }
        if (vetor[meio] > valor) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    return -1;
    }*/