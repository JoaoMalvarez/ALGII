/* 
1. Leia um número inteiro positivo fornecido pelo usuário;
2. Utilize uma função recursiva para calcular a soma dos dígitos desse
número;
3. Exiba o resultado na tela, informando a soma calculada.
*/

#include <stdio.h>
#include <stdlib.h>

int somatoria(int n) {
    if (n == 0) {
        return 0;
    } else {
        return (n % 10) + somatoria(n / 10);
    }
}

int main() {
    printf("---Exercício 01---\n\n");
    int numero, resultado;
    printf("Digite um número inteiro positivo: ");
    scanf("%d", &numero);
    if (numero < 0) {
        printf("Por favor, digite um número positivo.\n");
        return 1;
    }
    resultado = somatoria(numero);
    printf("A soma dos dígitos de %d é: %d\n", numero, resultado);
    return 0;
}