/*
1. Leia um número inteiro positivo informado pelo usuário;
2. Utilize uma função recursiva para exibir na tela a representação binária
desse número;
*/

#include <stdio.h>


void tradutor(int n) {
    if (n > 1) {
        tradutor(n / 2);
    }
        printf("%d", n % 2);
}

int main () {
    int numero;
    printf("---Exercício 02---\n\n");
    printf("Digite um número inteiro positivo: ");
    scanf("%d", &numero);

    if (numero < 0) {
        printf("Por favor, digite um número positivo.\n");
        return 1;
    }

    printf("A representação binária de %d é: ", numero);
    if (numero == 0) {
        printf("0");
    } else {
        tradutor(numero);  
    }
    printf("\n");
}