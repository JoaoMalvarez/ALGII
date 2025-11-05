#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("Quantidade: %d\n", argc);
    for (int i = 1; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
    int numero = atoi(argv[3]);
    printf("%d\n", numero);
}