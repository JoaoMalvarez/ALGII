#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Algoritmo_de_Euclides(int a, int b) {
    if (a < b) {
        return Algoritmo_de_Euclides(b, a);
    } else if (b == 0) {
        return a ;
    }
    return Algoritmo_de_Euclides (b, a % b);
}



int main() {
    int a;
    int b;
    printf("---Digite 2 números inteiros---");
    printf("\n");
    printf("\n1o número: ");
    scanf("%d", &a);
    printf("\n2o número: ");
    scanf("%d", &b);

    int res = Algoritmo_de_Euclides(a, b);
    printf("MDC: %d\n", res);
}