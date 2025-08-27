#include <stdio.h>

int potencia(int base, int expoente) {
    int resultado = 1;
    for (int cont = 1; cont <= expoente; cont++) {
    resultado *= base;
    }
    return resultado;
}

int main() {
    int base, expoente;
    printf("Base: ");
    scanf("%d", &base);
    printf("Expoente: ");
    scanf("%d", &expoente);

    int pot = potencia (base, expoente);
    printf("Potenccia: %d\n", pot);
    return 0;
}

//int contador = 1 {
//    while (contador <= 10) {             (poderia fazer dessa maneira, mas o for faz isso em menos espaço)
//    printf("%d\n", contador);
//    contador = contador + 1;

//    OU

//    for (int contador = 1; contador <= 10; contador++) {         - respectivamente fala sobre | 1x | V/F | Passo |
//        printf("%d\n", contador);
//}